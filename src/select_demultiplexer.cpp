#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

#include <map>
#include <list>
#include <algorithm>

#include "event.h"
#include "event_handle.h"
#include "event_demultiplexer.h"
#include "select_demultiplexer.h"

SelectDemultiplexer::SelectDemultiplexer()
{
    FD_ZERO( &read_set );
    FD_ZERO( &write_set );
    FD_ZERO( &err_set );
}

SelectDemultiplexer::~SelectDemultiplexer()
{

}

int SelectDemultiplexer::regist( Handle handle, Event evt )
{
    if ( evt | ReadEvent )
        FD_SET( handle, &read_set );
    if ( evt | WriteEvent )
        FD_SET ( handle, &write_set );

    FD_SET ( handle, &err_set );

    return 0;
}

int SelectDemultiplexer::remove(Handle handle)
{
    FD_CLR( handle, &read_set );
    FD_CLR( handle, &write_set );
    FD_CLR( handle, &err_set );

    return 0;
}

int SelectDemultiplexer::wait_event( std::map<Handle, EventHandler *>&  handlers, int timeout )
{
    struct timeval* ptv;

    struct timeval tv;

    if ( timeout > 0 )
    {
        tv.tv_sec = timeout / 1000;
        tv.tv_usec = timeout % 1000 * 1000;
        ptv = &tv;
    }
    else
        ptv = NULL;


    int max_fd = handlers.rbegin()->first + 1;
    int num = select( max_fd, &read_set, &write_set, &err_set, ptv );

    if ( num < 0 )
    {
        printf("select error %s\n", strerror(errno) ); 
        return -1;
    }
    else if ( num == 0 )
        return num;

    std::map<Handle, EventHandler *>::iterator it = handlers.begin();
    while ( it != handlers.end() )
    {
    /*
        if ( FD_ISSET( it->first, &err_set ) )
        {
            printf("%d error event\n", it->first);
            handlers[ it->first ]->handle_error();
            FD_CLR( it->first, &read_set );
            FD_CLR( it->first, &write_set );
        }
        else
        */
        {
            if ( FD_ISSET( it->first, &read_set ) )
            {
                printf("%d read event\n",it->first);
                handlers[ it->first ]->handle_read(); 
                FD_CLR( it->first, &write_set );
                FD_CLR( it->first, &err_set );
            }
            if ( FD_ISSET( it->first, &write_set ) )
            {
                printf("%d write event\n", it->first);
                handlers[ it->first ]->handle_write(); 
                FD_CLR( it->first, &err_set );
                FD_CLR( it->first, &read_set );
            }
            ++it;
        }
    }
        
    return num;
}

