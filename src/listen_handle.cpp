#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "stdio.h"

#include <map>

#include "event_handle.h"
#include "sock_handle.h"
#include "reactor.h"
#include "listen_handle.h"

ListenHandle::ListenHandle( int fd )
:listen_fd(fd)
{
    
}

ListenHandle::~ListenHandle()
{
    close( listen_fd );
}

void ListenHandle::handle_read()
{
    int fd = accept( listen_fd, NULL, NULL );

    EventHandler *h = new SockHandle( fd );

    Reactor& r = Reactor::get_instance();
    r.regist( h, ReadEvent );
}

void ListenHandle::handle_error()
{
    
}
