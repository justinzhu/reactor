#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main( int argc, char **argv )
{
    int sockfd = -1;

    if ( 0 > ( sockfd = socket( AF_INET, SOCK_STREAM, 0) ) )
    {
        printf("socket error:%s\n", strerror(errno) );
        exit(-1);
    }

    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons( 9876 );
    seraddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
    if ( 0 > connect( sockfd, (struct sockaddr*)&seraddr, sizeof(seraddr) ) )
    {
        printf("connect error:%s\n", strerror(errno) );
        exit(-2);
    }else{
		printf("connect ok\n");
	}

    char wbuf[64] = {0};
    strcpy( wbuf, "hello world");
    int n = write( sockfd, wbuf, strlen(wbuf) );

    char rbuf[64] = {0};
    memset( rbuf, 0, sizeof(rbuf) );
    n = read( sockfd, rbuf, sizeof(rbuf) );
    printf("send [ %s ]; reply [ %s ] \n", wbuf, rbuf );

    if ( n < 0 )
    {
        printf("read error:%s\n", strerror(errno) );
        exit(-3);
    }

    close(sockfd);

    return 0;
}

