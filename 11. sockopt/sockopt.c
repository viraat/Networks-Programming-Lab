/* Program: Implementing setsockopt() & getsockopt() */
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
int main()
{
    int sockfd, maxseg, sendbuff, optlen;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( sockfd < 0 )
    {
        perror("socket");
        exit(0);
    }
    optlen = sizeof(maxseg);
    if ( getsockopt(sockfd, IPPROTO_TCP, TCP_MAXSEG, (char *)&maxseg, &optlen) < 0 )
    {
        perror("getsockopt1");
        exit(0);
    }
    printf("\n TCP maxseg=%d", maxseg);
    sendbuff = 12324;
    if (setsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *)&sendbuff, sizeof(sendbuff)) < 0)
    {
        perror("setsockopt");
        exit(0);
    }
    optlen = sizeof(sendbuff);
    if (getsockopt(sockfd, SOL_SOCKET, SO_SNDBUF, (char *)&sendbuff, &optlen) < 0)
    {
        perror("getsockopt2");
        exit(0);
    }
    printf("\n Send Buffer size=%d", sendbuff);
    return 0;
}
