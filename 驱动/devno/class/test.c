#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd;
	fd = open("/dev/mydev",O_RDWR);
	if(fd<0)
	{
		printf("open fail\n");
		return;
	}
	close(fd);
}
