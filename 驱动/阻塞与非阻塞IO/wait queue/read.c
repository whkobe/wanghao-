#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd,len;
	char buf[]={0};
	//fd=open("/dev/hello",O_RDWR | O_NONBLOCK);//非阻塞
	fd=open("/dev/hello",O_RDWR);//阻塞
	if(fd<0)
	{
		perror("open fail\n");
	
	}
	printf("open ok\n");
	
	len=read(fd,buf,64);
	buf[len]='\0';
	printf("buf=%s",buf);
	close(fd);
	return 0;
}