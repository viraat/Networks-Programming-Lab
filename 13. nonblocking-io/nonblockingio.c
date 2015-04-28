//Program
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#define BUFFSIZE 100
main()
{
    int n;
    char buff[BUFFSIZE];
    if (fcntl(0, F_SETFL, FNDELAY) < 0)
    {
        perror("Nonblocking failed");
        exit(0);
    }
    while (1)
    {
        while ((n = read(0, buff, BUFFSIZE)) < 0)
        {
            if (errno != EWOULDBLOCK)
                break;
        }
        fflush(stdout);
        if (write(1, buff, n) < 0)
        {
            perror("write");
            break;
        }
    }
}
