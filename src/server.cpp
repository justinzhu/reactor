#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <map>

#include "event_handle.h"
#include "reactor.h"
#include "listen_handle.h"
#include "sock_handle.h"

int main(int argc, char **argv)
{
    int listenfd = -1;

    if( 0 > (listenfd = socket( AF_INET, SOCK_STREAM, 0 ) ) )
    {
        printf("socket error:%s\n", strerror(errno) );
        exit(-1);
    }

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons( 9876 );
    seraddr.sin_addr.s_addr = htonl( INADDR_ANY );

    if ( 0 >  bind( listenfd, (struct sockaddr*)&seraddr, sizeof(seraddr) ) )
    {
        printf("bind error:%s\n", strerror(errno) );
        exit(-2);
    }

    if ( 0 > listen( listenfd, 5 ) )
    {
        printf("listen error:%s\n", strerror( errno ) );
        exit(-3);
    }

    Reactor& actor = Reactor::get_instance();
    EventHandler* handle = new ListenHandle( listenfd );
    actor.regist( handle, ReadEvent );

    while( true )
    {
        actor.event_loop( -1 ); 
        printf("one loop\n");
    }

    return 0;
}

