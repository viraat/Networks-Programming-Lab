#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <netinet/in.h>
#define MAX 1024
int main(int argc,char *argv[])
{
	int sockfd,addr_len,n;
	char buff1[MAX],buff2[MAX];
	struct sockaddr_in serv_addr;
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	if(sockfd==-1)
	{
		perror("Error in Client:"); exit(1);
	}
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_port=htons(atoi(argv[1]));
	serv_addr.sin_addr.s_addr=inet_addr("49.204.40.9");
	if((connect(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr)))<0)
	{
		perror("Error in Client: "); exit(1);
	}
	fflush(stdout);
	for( ; ; )
	{
		printf("\nEnter the command string: ");
		fflush(stdout);
		if( (n=read(0,buff1,MAX+1)) < 0 )
		{
			perror("Error in Client: "); exit(1);
		}
		buff1[n]='\0';
		if( (n=write(sockfd,buff1,n+1)) < 0 )
			perror("Error in Client: ");
		if( (bcmp("exit",buff1,4)) == 0 )
		{ 
			printf("\a\a Client is exiting...\n"); 
			exit(1);
		}
		sleep(1);
		if((n=read(sockfd,buff2,MAX))<0)
		{
			perror("Error in Client: "); exit(1);
		}
		buff2[n]='\0';
		if(write(1,buff2,n+1)<0)
			perror("Client:Write by client ot the screen");
	}
	return 0;
}