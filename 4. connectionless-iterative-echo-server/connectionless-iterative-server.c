//connection less iterative server
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char * argv[ ])
{
    int s, t;
    struct sockaddr_in local, remote;
    char str[100];
    if ( argc != 2 )
    { perror("Usage: server <port>"); exit(0); }
    if ( (s = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
    { perror("socket"); exit(1); }
    bzero( (char *)&local, sizeof( local ) );
    local.sin_family = AF_INET;
    local.sin_port = htons( atoi( argv[1] ));
    local.sin_addr.s_addr = inet_addr("192.168.11.100");
    if ( bind(s, (struct sockaddr *)&local, sizeof(local)) == -1 )
    { perror("bind"); exit(1); }
    t = sizeof(remote);
    memset(str, 0, 100);
    for ( ; ; )
    {
        int n;
        while ( n = recvfrom(s, str, 100 , 0, (struct sockaddr *)&remote, &t) > 0)
        {
            printf("%s\n", str);
            if ( sendto(s, str, n, 0, (struct sockaddr *)&remote, sizeof(remote)) < 0 )
            { perror("sendto"); }
            memset(str, 0, 100);
        }
        if ( n < 0 )
        { perror("recvfrom"); exit(0); }
    }
    return 0;
}
