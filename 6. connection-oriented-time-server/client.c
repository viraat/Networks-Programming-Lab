/*connection oriented iterative time of day service client*/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<time.h>
int main(int argc,char *argv[])
{
        int n,cs;
        struct sockaddr_in servaddr;
        char buffer[1024];
        time_t ct;
        if(argc!=3)
        {
                printf("\n usage:server<port>");
                exit(0);
        }
        if((cs=socket(AF_INET,SOCK_STREAM,0))<0)
        {
                perror("socket");
                exit(0);
        }
        bzero(&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=inet_addr(argv[1]);
        servaddr.sin_port=htons((short)atoi(argv[2]));
        if(connect(cs,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        {
                perror("connect");
                exit(0);
           }
        printf("the current time is:");
        while((n=read(cs,buffer,1024))>0)
        {
                buffer[n]='\0';
                fputs(buffer,stdout);
        }
        if(n<0)
        {
                perror("read");
                exit(0);
        }
        return 0;
}
