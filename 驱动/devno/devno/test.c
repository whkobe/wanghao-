#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

main()
{
	int fd;
	fd = open("/dev/hello",O_RDWR);
	if(fd<0)
	{
		printf("open fail\n");
		return;
	}
	close(fd);
}

//需要 mknod /dev/hello c 250 0 因为我们么有创建设备节点