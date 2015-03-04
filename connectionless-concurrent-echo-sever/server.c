 /*connectionless concurrent echo server*/

#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc,char *argv[])
{
        int s,t,n,cp;
        struct sockaddr_in local,rem;
        char str[100];
        if(argc!=2)
        {
                perror("usage:server<port>");
                exit(0);
        }
        s=socket(AF_INET,SOCK_DGRAM,0);
        if(s==-1)
        {
                perror("socket");
                exit(1);
        }
        bzero((char *)&local,sizeof(local));
        local.sin_family=AF_INET;
        local.sin_port=htons(atoi(argv[1]));
        local.sin_addr.s_addr=htonl(INADDR_ANY);
        if(bind(s,(struct sockaddr*)&local,sizeof(local))==-1)
        {
                perror("bind");
                exit(1);
        }
        t=sizeof(rem);
         memset(str,0,100);
        for(;;)
        {
                if((n=recvfrom(s,str,100,0,(struct sockaddr*)&rem,&t))<0)
                {
                        perror("recvfrom");
                        break;
                }
                printf("%s\n",str);
                if((cp=fork())==0)
                {
                        while(1)
                        {
                                if(sendto(s,str,n,0,(struct sockaddr *)&rem,sizeof(rem))<0)
                                {
                                        perror("send to");
                                        break;
                                }
                                memset(str,0,100);
                                if((n=recvfrom(s,str,100,0,(struct sockaddr *)&rem,&t))<0)
                                {
                                        perror("receive from");
                                       break;
                                }
                               printf("%s\n",str);
                        }
                }
                else if(cp<0)
                {
                        perror("fork error");
                        exit(0);
                }
        }
        close(s);
        return 0;
}
