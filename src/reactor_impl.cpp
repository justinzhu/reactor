#include <map>

#include "event.h"
#include "event_handle.h"
#include "event_demultiplexer.h"

#ifdef _USE_EPOLL
    #include "epoll_demultiplexer.h"
#endif
#ifdef _USE_SELECT
    #include <sys/select.h>
    #include <list>
    #include "select_demultiplexer.h"
#endif

#include "reactor_impl.h"

ReactorImplementation::ReactorImplementation()
{
	#ifdef _USE_EPOLL
       demultiplexer = new EpollDemultiplexer();
	#endif
    #ifdef _USE_SELECT
        demultiplexer = new SelectDemultiplexer();
    #endif
}

ReactorImplementation::~ReactorImplementation()
{
    if ( demultiplexer )
        delete demultiplexer;
}

int ReactorImplementation::regist( EventHandler* handler, Event evt )
{
    return demultiplexer->regist( handler, evt ); 
}

void ReactorImplementation::remove( EventHandler* handler )
{
    int handle = handler->get_handle();
    demultiplexer->remove( handle );
}

void ReactorImplementation::event_loop( int timeout )
{
    demultiplexer->wait_event( handlers, timeout );
}

