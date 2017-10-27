#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd;
	fd = open("/dev/hello",O_RDWR | O_NONBLOCK);
	if(fd<0)
	{
		perror("open fail\n");
		return;
	}
	write(fd,"12345678",strlen("12345678"));
	close(fd);
}
