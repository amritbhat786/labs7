#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

void main()
{
	char fname[60],buffer[1<<20];
	int s,n,source,file;
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(5000);
	addr.sin_addr.s_addr = INADDR_ANY;

	printf("Waiting for request...\n");
	s= socket(AF_INET,SOCK_STREAM,0);
	bind(s,(struct sockaddr*)&addr,sizeof(addr));
	listen(s,3);

	source = accept(s,(struct sockaddr*)NULL,NULL);
	printf("%d",source);
	

	recv(source,fname,sizeof(fname),0);

	printf("request for file %s\n",fname);
	file = open(fname,O_RDONLY);

	if(file<0)
		send(source,"file not found\n",20,0);
	else
	{
		while((n=read(file,buffer,sizeof(buffer)))>0)
		{
			send(source,buffer,n,0);
		}
	}
	printf("Request sent\n");
	close(file);
}
