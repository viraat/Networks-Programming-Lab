//Program
#include <signal.h>
#include <fcntl.h>
#define BUFFSIZE 4096
int sigflag;
main()
{
  int n;
  char buff[BUFFSIZE];
  int sigio_func();
  signal(SIGIO,sigio_func);
  if(fcntl(0,F_SETOWN,getpid())<0)
  {
    perror("F_SETOWN");
    exit(0);
  }
  if(fcntl(0,F_SETFL,FASYNC)<0)
  {
    perror("F_SETFL FASYNC");
    exit(0);
  } 
  for(;;)
  {
    sigblock(sigmask(SIGIO));
    while(sigflag==0)
    sigpause(0);
    if((n=read(0,buff,BUFFSIZE))>0)
    {
      if(write(1,buff,n)!=n)
        perror("write");
    }
    else if(n<0)
      perror("read");
    else if(n==0)
      exit(0);
    sigflag=0;
    sigsetmask(0);
  }
}

int sigio_func()
{
  sigflag=1;
} 
