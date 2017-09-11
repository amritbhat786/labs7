#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>

void main()
{
	char fname[60],buffer[1<<20];
	int s,n;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(6980);
	addr.sin_addr.s_addr = INADDR_ANY;
	if((s=socket(AF_INET,SOCK_STREAM,0))<0)
	{
		perror("Socket\n");
		connect(s,(struct sockaddr*)&addr,sizeof(addr));
	}

	printf("Enter file name:\n");
	scanf("%s",fname);
	printf("\nSending request..\n");
	send(s,fname,sizeof(fname),0);

	printf("Received response\n");
	while((n=recv(s,buffer,sizeof(buffer),0))>0)
	{
		write(1,buffer,n);
		printf("\nSuc");
	}
}