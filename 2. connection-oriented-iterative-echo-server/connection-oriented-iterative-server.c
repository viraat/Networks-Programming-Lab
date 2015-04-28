//Connection oriented iterative echo server
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>

int main(int argc, char *argv[])
{
    int s, s2, t, len;
    struct sockaddr_in local, rem;
    char str[100];
    s = socket(AF_INET, SOCK_STREAM, 0);
    if (s == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero((char *)&local, sizeof(local));
    local.sin_family = AF_INET;
    local.sin_port = htons(atoi(argv[1]));
    local.sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(s, (struct sockaddr *)&local, sizeof(local)) == -1)
    {
        perror("bind is not done");
        exit(1);
    }
    if (listen(s, 5) == -1)
    {
        perror("listen");
        exit(1);
    }
    for (;;)
    {
        int done, n;
        printf("waiting for a connection..\n");
        t = sizeof(rem);
        s2 = accept(s, (struct sockaddr *)&rem, &t);
        if (s2 == -1)
        {
            perror("accept");
            exit(1);
        }
        printf("connected\n");
        done = 0;
        do
        {
            n = recv(s2, str, 100, 0);
            printf("%s", str);
            if (n <= 0)
            {
                if (n < 0)
                    perror("recv");
                done = 1;
            }
            if (!done)
                if (send(s2, str, n, 0) < 0)
                {
                    perror("send");
                    done = 1;
                }
        } while (!done);
        close(s2);
    }
    return 0;
}

