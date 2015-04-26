#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/time.h>
int main(int argc, char *argv[])
{
  static struct timeval timeout;
  if(argc!=3)
  {
    printf("\n Usage : %s <seconds> <microseconds>",argv[0]);
    exit(0);
  }
  timeout.tv_sec=atol(argv[1]);
  timeout.tv_usec=atol(argv[2]);
  if(select(0,(fd_set *) 0,(fd_set *) 0,(fd_set *) 0,&timeout)<0)
  { 
    perror("select"); exit(0);
  }
  return 0;
}
