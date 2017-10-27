#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
 #include <sys/ioctl.h>

#define FS4412_LED_MAGIC   'k'
#define  FS4412_LED_ON      _IOW (FS4412_LED_MAGIC,0,  int )
#define  FS4412_LED_OFF     _IOW (FS4412_LED_MAGIC,1,  int)

main()
{
	int fd;
	int i;
	int ledno;
	
	fd = open("/dev/hello",O_RDWR);//打开设备文件。
	if(fd<0)
	{
		printf("open fail\n");
		return;
	}
	for(i=0;i<1000;i++)
	{
		ledno = i%4+1;	
		ioctl(fd,FS4412_LED_ON,ledno);
		sleep(1);
		ioctl(fd,FS4412_LED_OFF,ledno);		
	}	
	close(fd);
}
