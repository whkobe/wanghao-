#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
int main()
{
	
	int fd;
	char buf[]="kobe";
	//fd=open("/dev/hello",O_RDWR | O_NONBLOCK);
	fd=open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		perror("open fail\n");
		return;
	
	}
	printf("open ok\n");
	write(fd,buf,strlen(buf));
	close(fd);
	return 0;
	
}