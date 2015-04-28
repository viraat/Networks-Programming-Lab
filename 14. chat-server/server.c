/* Program: Chat server */
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
    if (connect(s, (struct sockaddr *)&remote, len) == -1)
    {
        perror("connect");
        exit(1);
    }
    printf("Connected.\n");
    while (printf("> "), fgets(str, 100, stdin), !feof(stdin))
    {
        if (send(s, str, strlen(str), 0) == -1)
        {
            perror("send");
            exit(1);
        }
        if ((t = recv(s, str, 100, 0)) > 0)
        {
            str[t] = '\0';
            printf("echo> %s", str);
        }
        else
        {
            if (t < 0)
                perror("recv");
            else
                printf("Server closed connection\n");
            exit(1);
        }
    }
    close(s);
    return 0;
}
