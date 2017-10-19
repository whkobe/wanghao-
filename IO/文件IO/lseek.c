函数lseek()
需要头文件：#include<unistd.h>
            #include<sys/types.h>
函数原型：off_t lseek(int fd,off_t offset,int whence);
函数参数：fd：文件描述符
          offset：相对于基准点whence的偏移量，正数表示向前移动，负数表示向后移动，0表示不移动
		  whence：基准点（取值同标准I/O内fseek()函数第三个参数）
函数返回值：成功：当前读写位置
            失败：-1
其中第三个参数whence的取值如下：
	SEEK_SET：代表文件起始位置，数字表示为0
	SEEK_CUR：代表文件当前的读写位置，数字表示为1
	SEEK_END：代表文件结束位置，数字表示为2
lseek()仅将文件的偏移量记录在内核内而不进行任何I/O操作。
注意：lseek()函数仅能操作常规文件，一些特殊的文件（例如socket文件、管道文件等）无法使用lseek()函数。

若将lseek()函数的基准点设置为SEEK_END但是偏移量是正数（即从文件末尾再向后偏移），则会产生“文件空洞”的情况。
文件的偏移量是从文件开始位置开始计算的，若文件的偏移量大于了文件的实际数据长度，则会延长该文件，形成空洞。
示例：创建一个有空洞的文件。故意在文件结尾偏移好多个字节，然后再写入数据
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char *argv[])
{
	int fd;
	int n;
	char buf1[]="LiLaoShiZhenShuai!";
	char buf2[]="ABCDEFG";
	if(argc<2)
	{
		printf("arguments are too few\n");
		exit(0);
	}
	if((fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,0666))<0)
	{
		perror("cannot open file");
		exit(0);
	}
	write(fd,buf1,strlen(buf1));//首先写入某些数据
	n=lseek(fd,0,SEEK_END);//返回文件末尾位置求出文件大小
	printf("原先的文件大小是%d\n",n);
	n=lseek(fd,987654321,SEEK_END);//在文件末尾向后偏移很多字节
	printf("此时偏移量是%d\n",n);
	write(fd,buf2,strlen(buf2));//写入buf内数据
	n=lseek(fd,0,SEEK_END);
	printf("空洞后文件大小是%d\n",n);
	close(fd);
	return 0;
}
程序执行后，使用vim查看该文件，会发现在两段数据之间有一段乱码数据，并且使用ls -l指令查看，文件的大小也变大了。
在UNIX/Linux文件操作中，文件位移量可以大于文件的当前长度，在这种情况下，对该文件的下一次写将延长该文件，并在文件中构成一个空洞，这一点是允许的。位于文件中但没有写过的字节都被设为0，用read读取空洞部分读出的数据是0。
空洞文件作用很大，例如迅雷下载文件，在未下载完成时就已经占据了全部文件大小的空间，这时候就是空洞文件。下载时如果没有空洞文件，多线程下载时文件就都只能从一个地方写入，这就不是多线程了。如果有了空洞文件，可以从不同的地址写入，就完成了多线程的优势任务。
/*******************文件空洞end***************/