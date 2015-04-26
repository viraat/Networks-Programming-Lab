/*connectionless iterative time of day service server*/

#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<string.h>
#include<netinet/in.h>
#include<errno.h>
#include<time.h>
int main(int argc,char *argv[])
{
        int s,t;
        struct sockaddr_in servaddr,cliaddr;
        char buffer[1024];
        time_t ct;
        if(argc!=2)
        {
                printf("\n usage:client<server-adr><port>");
                exit(0);
        }
        if((s=socket(AF_INET,SOCK_DGRAM,0))<0)
        {
                perror("socket");
                exit(0);
        }
        bzero((char*)&servaddr,sizeof(servaddr));
        servaddr.sin_family=AF_INET;
        servaddr.sin_port=htons((short)atoi(argv[1]));
        servaddr.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(s,(struct sockaddr*)&servaddr,sizeof(servaddr))<0)
        {
                perror("bind");
                exit(0);
        }
          t=sizeof(servaddr);
        while(1)
        {
                if(recvfrom(s,buffer,1024,0,(struct sockaddr*)&cliaddr,&t)<0)
                {
                        perror("recvfrom");
                        exit(0);
                }
                ct=time(NULL);
                sprintf(buffer,"%s",ctime(&ct));
                if(sendto(s,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr))<0)
                {
                        perror("send to");
                        exit(0);
                }
        }
                close(s);
                return 0;
}
