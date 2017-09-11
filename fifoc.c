#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

void main()
{
	char fname[50],buffer[1024];
	int req,res,n;
	req = open("req.fifo",O_WRONLY);
	res = open("res.fifo",O_RDONLY);
	printf("Enter filename to request\n");
	scanf("%s",fname);
	write(req,fname,sizeof(fname));
	printf("Received response\n");
	while((n=read(res,buffer,sizeof(buffer)))>0)
	{
		write(1,buffer,n);
	}
	close(req);
	close(res);
}