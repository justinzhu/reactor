#include <map>
#include <vector>

#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/epoll.h>
#include "stdio.h"

#include "event.h"
#include "event_handle.h"
#include "event_demultiplexer.h"
#include "epoll_demultiplexer.h"

const int EpollDemultiplexer::max_event = 1024;
EpollDemultiplexer::EpollDemultiplexer()
:epoll_fd(-1)
{
    epoll_fd = epoll_create( max_event );
	evs.resize( max_event );
}

EpollDemultiplexer::~EpollDemultiplexer()
{
	if( epoll_fd != -1 )
		close( epoll_fd );
}

int EpollDemultiplexer::wait_event(  std::map<Handle, EventHandler *>&  handlers,
                                int timeout )
{

    int num = epoll_wait( epoll_fd, &evs[0], max_event, timeout );

	for ( int i = 0; i < num; ++i )
	{
		EventHandler* handler = (EventHandler*)evs[i].data.ptr;

		if ( (EPOLLIN) & evs[i].events )
		{
				handler->handle_read();
		}

		if ( EPOLLOUT & evs[i].events )
		{
				handler->handle_write();
		}
		if ( (EPOLLRDHUP | EPOLLHUP | EPOLLERR) & evs[i].events )
		{
			handler->handle_error();
		}
	}

    return num;
}

int EpollDemultiplexer::regist(EventHandler* handler, Event evt)
{
    struct epoll_event ev;

	ev.data.ptr = (void*)handler;

    if ( evt & ReadEvent )
    {
        ev.events |= EPOLLIN;
		ev.events |= EPOLLET;
    }
    if ( evt & WriteEvent )
    {
        ev.events |= EPOLLOUT;    
    }

    if ( 0 != epoll_ctl( epoll_fd, EPOLL_CTL_ADD, handler->get_handle(), &ev ) )
    {
        if ( errno == ENOENT ) 
        {
            if ( 0 != epoll_ctl( epoll_fd, EPOLL_CTL_ADD, handler->get_handle(), &ev ) )
            {
                printf("epoll_ctrl add error : %s\n", strerror(errno));
                return -errno;
            }
        }
    }

    return 0;
}

int EpollDemultiplexer::remove(Handle handle)
{
    struct epoll_event ev;

    if ( 0 != epoll_ctl( epoll_fd, EPOLL_CTL_DEL, handle, &ev ) )
    {
        printf("epoll_ctrl del error : %s\n", strerror(errno));
        return -errno;
    }

    return 0;
}

