/* Connection oriented iterative time of day service server */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <time.h>
int main(int argc, char *argv[])
{
    int ls, cs;
    struct sockaddr_in servaddr;
    char buffer[1024];
    time_t ct;
    if (argc != 2)
    {
        printf("\n usage:server<port>");
        exit(0);
    }
    if ((ls = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("socket");
        exit(0);
    }
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons((short)atoi(argv[1]));
    if (bind(ls, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0)
    {
        perror("bind");
        exit(0);
    }
    if (listen(ls, 5) < 0)
    {
        perror("listen");
        exit(0);
    }
    while (1)
    {
        if ((cs = accept(ls, NULL, NULL)) < 0)
        {
            perror("accept");
            exit(0);
        }
        ct = time(NULL);
        sprintf(buffer, "%s\n", ctime(&ct));
        write(cs, buffer, strlen(buffer));
        close(cs);
    }
    return 0;
}
