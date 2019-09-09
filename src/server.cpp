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
    ListenHandle* handle = new ListenHandle( );
	handle->listenOn(9876);
    Reactor& actor = Reactor::get_instance();
    actor.regist( handle, ReadEvent );

    while( true )
    {
        actor.event_loop( -1 ); 
        printf("one loop\n");
    }

    return 0;
}

