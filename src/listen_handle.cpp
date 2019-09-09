#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "stdio.h"
#include <fcntl.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <errno.h>
#include <unistd.h>


#include <map>

#include "event_handle.h"
#include "sock_handle.h"
#include "reactor.h"
#include "listen_handle.h"

ListenHandle::ListenHandle( )
:listenfd(-1)
{
    
}

ListenHandle::~ListenHandle()
{
	if ( listenfd != -1 )
		close( listenfd );
}

void ListenHandle::handle_read()
{
    int fd = accept( listenfd, NULL, NULL );
	printf("new connect\n");

    SockHandle *h = new SockHandle( fd );
	setNonBlocking(h->get_handle());

    Reactor& r = Reactor::get_instance();
    r.regist( h, ReadEvent );
}

void ListenHandle::handle_error()
{
    
}

bool ListenHandle::listenOn( int port ){
    if( 0 > (listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ) )
    {
        printf("socket error:%s\n", strerror(errno) );
		return false;
    }

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons( port );
    seraddr.sin_addr.s_addr = htonl( INADDR_ANY );

    if ( 0 >  bind( listenfd, (struct sockaddr*)&seraddr, sizeof(seraddr) ) )
    {
        printf("bind error:%s\n", strerror(errno) );
		return false;
    }
	
	int sockoptval = 1;
	if ( 0 > setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &sockoptval, sizeof(sockoptval)) ){
        printf("setsockopt error:%s\n", strerror( errno ) );
		return false;
	}

	setNonBlocking( listenfd );

    if ( 0 > listen( listenfd, 5 ) )
    {
        printf("listen error:%s\n", strerror( errno ) );
		return false;
    }


	return true;
}


void ListenHandle::setNonBlocking( int fd){
	int option = fcntl( fd, F_GETFL );
	option |= O_NONBLOCK;
	fcntl( fd, option );
}
