#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#define MAX 80

int main(int argc, char *argv[])
{
    int s, s2, t, len, cp, i, j, n;
    char str[100];
    struct sockaddr_in local, rem;
    s = socket(AF_INET, SOCK_STREAM, 0);
    if ( s == -1 )
    { perror("socket"); exit(1); }
    bzero((char*)&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    if ( bind(s, (struct sockaddr*)&local, sizeof(local)) == -1)
    { perror("bind"); exit(1); }
    if ( listen(s, 5) == -1)
    { perror("listen"); exit(1); }
    for ( ; ; )
    {
        t = sizeof(rem);
        s2 = accept( s, (struct sockaddr *)&rem, &t );
        if ( s2 == -1 )
        { perror("accept"); exit(1); }
        cp = fork();
        if ( cp < 0 )
        { perror("fork error"); exit(1); }
        if ( cp == 0 )
        {
            close(s);
            printf("s=%d s2=%d t=%d\n", s, s2, t);
            for ( j = 0; j < 5; ++j)
            {
                n = recv(s2, str, 100, 0);
                str[n] = '\0';
                printf("client:%s\n>", str);
                write(1, "server>", 7);
                n = read(0, &str, MAX);
                send(s2, &str, n, 0);
            }
            close(s2);
        }
    }
    close(s);
    return 0;
}