#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#define MAX 1024
int main(int argc, char *argv[])
{
    int sockfd, addrlen, new, n;
    char buff1[MAX];
    struct sockaddr_in serv_addr, peer;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if ( sockfd == -1)
    {
        perror("Error in Server");
        exit(1);
    }
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(atoi(argv[1]));
    serv_addr.sin_addr.s_addr = inet_addr("192.168.11.100");
    if ( bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0 )
    {
        perror("Error in Server "); exit(1);
    }
    if ( listen(sockfd, 5) < 0 )
    {
        perror("Error in Server "); exit(1);
    }
    for ( ; ; )
    {
        if ( (new = accept(sockfd, (struct sockaddr *)&peer, &addrlen)) < 0 )
        {
            perror("Error in Server"); exit(1);
        }
        if (fork() == 0)
        {
            for ( ; ; )
            {
                if ( (n = read(new, buff1, MAX)) < 0 )
                {
                    perror("Error in Server  read"); exit(1);
                }
                if ( n == 0 )
                    break;

                buff1[n] = '\0'; // fflush(stdout);
                if ( !strcmp("exit", buff1) )
                {
                    printf("\a\a server is exiting"); exit(1);
                }
                close(1);
                if (dup(new) < 0)
                    printf("\nserver: dup system call failure");
                fflush(stdout);
                system(buff1);
                if ((write(new, "\n", 1)) < 0)
                    perror("write error");
            }
        }
        close(new);
    }
}
