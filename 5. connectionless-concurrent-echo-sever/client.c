/*connectionless concurrent echo client*/

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char *argv[])
{
    int s, t;
    struct sockaddr_in rem, local;
    char str[100];
    if (argc != 3)
    {
        perror("usage:server<port>");
        exit(0);
    }
    s = socket(AF_INET, SOCK_DGRAM, 0);
    if (s == -1)
    {
        perror("socket");
        exit(1);
    }
    bzero((char *)&local, sizeof(local));
    local.sin_family = AF_INET;

    local.sin_port = htons(6677);
    local.sin_addr.s_addr = inet_addr(argv[1]);
    if (bind(s, (struct sockaddr*)&local, sizeof(local)) == -1)
    {
        perror("bind");
        exit(1);
    }
    bzero((char *)&rem, sizeof(rem));
    rem.sin_family = AF_INET;
    rem.sin_port = htons((short)atoi(argv[2]));
    rem.sin_addr.s_addr = inet_addr(argv[1]);
    t = sizeof(rem);
    while (printf(">"), fgets(str, 100, stdin), !feof(stdin))
    {
        int n;
        if (sendto(s, str, strlen(str), 0, (struct sockaddr*)&rem, sizeof(rem)) < 0)
        {
            perror("send");
            exit(1);
        }
        if ((n = recvfrom(s, str, 100, 0, (struct sockaddr*)&rem, &t)) > 0)
        {
            str[n] = '\0';
            printf("echo>%s", str);
        }
        else
        {
            if (n < 0)
                perror("recv");
            else
                printf("server closed connection\n");
            exit(1);
        }
        memset(str, 0, 100);
    }
    return 0;
}
