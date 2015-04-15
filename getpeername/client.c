/* Program: implementing getpeername client */
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
int main(int argc,char *argv[])
{
  int s;
  struct sockaddr_in server,addr;
  socklen_t len;
  s = socket( AF_INET, SOCK_STREAM, 0 );
  if( s == -1 )
  { 
    perror("socket"); 
    exit(1); 
  }
  server.sin_family = AF_INET;
  inet_aton("192.168.11.100",&server.sin_addr);
  server.sin_port = htons( atoi(argv[1]) );
  if( connect(s,(struct sockaddr *)&server,sizeof(server)) < 0 )
  { 
    perror("connect"); 
    exit(0);
  }
  len = sizeof(addr);
  getpeername(s,(struct sockaddr *)&addr,&len);
  printf("peer IP address:%s\n",inet_ntoa(addr.sin_addr));
  printf("peer port:%d\n",ntohs(addr.sin_port));
  return 0;
} 
