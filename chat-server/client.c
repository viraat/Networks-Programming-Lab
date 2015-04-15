#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#define max 80
int main(int argc,char *argv[])
{ 
  int s,t,len,a,i,n;
  struct sockaddr_in rem;
  char str[100];
  if( argc != 2 )
  { 
    printf("\n invalid server address"); 
    exit(0); 
  }
  s = socket(AF_INET,SOCK_STREAM,0);
  if( s == -1)
  {
    perror("socket"); 
    exit(1); 
  }
  rem.sin_family=AF_INET;
  rem.sin_port=htons(atoi(argv[1]));
  rem.sin_addr.s_addr=inet_addr("172.16.99.99");
  a = connect(s,(struct sockaddr *)&rem,sizeof(rem));
  if( a == -1)
  { 
    perror("not connect"); 
    exit(1); 
  }
  printf("connected\n");
  for( i=0; i<5; ++i)
  { 
    write(1,"client>",7);
    n = read(0,&str,max);
    send(s,str,n,0);
    write(1,"server:",7);
    n = recv(s,str,100,0);
    write(1,&str,n);
  }
  close(s);
  return 0;
}
