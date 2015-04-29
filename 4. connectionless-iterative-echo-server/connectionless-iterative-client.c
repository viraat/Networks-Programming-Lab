#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
int main(int argc, char * argv[])
{
	int s, t, n;
	struct sockaddr_in remote;
	char str[100];
	if ( argc != 2 )
	{ perror("Usage: client <server address> <port>"); exit(0); }
	if ( (s = socket(AF_INET, SOCK_DGRAM, 0)) == -1 )
	{ perror("socket"); exit(1); }
	bzero( (char *)&remote, sizeof(remote) );
	remote.sin_family = AF_INET;
	remote.sin_port = htons( (short)atoi( argv[1] ) );
	remote.sin_addr.s_addr = inet_addr("127.0.0.0");
	t = sizeof(remote);
	while ( printf(">"), fgets(str, 100, stdin), !feof(stdin) )
	{
		if ( sendto(s, str, strlen(str), 0, (struct sockaddr*)&remote, sizeof(remote)) < 0 )
		{ perror("sendto"); exit(1); }
		if ( (n = recvfrom(s, str, 100, 0, (struct sockaddr *)&remote, &t)) > 0 )
		{ printf("echo> %s\n", str); }
		else
		{
			if ( n < 0 ) perror("recvfrom");
			else printf("server closed connection\n");
		}
		memset( str, 0, 100 );
	}
	return 0;
}
