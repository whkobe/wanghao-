通过之前的open()/close()/read()/write()/lseek()函数已经可以实现文件的打开、关闭、读写等基本操作，但是这些基本操作是不够的。对于文件的操作而言，“锁定”操作是对文件（尤其是对共享文件）的一种高级的文件操作。当某进程在更新文件内数据时，期望某种机制能防止多个进程同时更新文件从而导致数据丢失，或者防止文件内容在未更新完毕时被读取并引发后续问题，这种机制就是“文件锁”。
对于共享文件而言，不同的进程对同一个文件进行同时读写操作将极有可能出现读写错误、数据乱码等情况。在Linux系统中，通常采用“文件锁”的方式，当某个进程独占资源的时候，该资源被锁定，其他进程无法访问，这样就解决了共享资源的竞争问题。
文件锁包括建议性锁（又名“协同锁”）和强制性锁两种。建议性锁要求每个相关进程访问文件的时候检查是否已经有锁存在并尊重当前的锁。一般情况下不建议使用建议性锁，因为无法保证每个进程都能自动检测是否有锁，Linux内核与系统总体上都坚持不使用建议性锁。而强制性锁是由内核指定的锁，当一个文件被加强制性锁的过程中，直至该所被释放之前，内核将阻止其他任何进程对该文件进行读或写操作，每次读或写操作都得检测锁是否存在。当然，采用强制性锁对内核的性能影响较大，每次内核在操作文件的时候都需要检查是否有强制性锁。
在Linux内核提供的系统调用中，实现文件上锁的函数有lockf()和fcntl()，其中lockf()用于对文件加建议性锁，这里不再讲解。fcntl()函数既可以加建议性锁，也可以加强制性锁。同时，fcntl()还能对文件某部分上记录锁。所谓记录锁，其实就是字节范围锁，它能锁定文件内某个特定区域，当然也可锁定整个文件。
记录锁又分为读锁和写锁两种。其中读锁又称为共享锁，它用来防止进程读取的文件记录被更改。记录内可设置多个读锁，但当有一个读锁存在的时候就不能在该记录区域设置写锁。写锁又称为排斥锁，在任何时刻只能有一个程序对文件的记录加写锁，它用来保证文件记录被某一进程更新数据的时候不被其他进程干扰，确保文件数据的正确性，同时也避免其他进程“弄脏”数据。文件记录一旦被设置写锁，就不能再设置任何锁直至该写锁解锁。
本节只简单讲述fcntl()对文件施加读锁和写锁并查看两种锁的效果，有关函数fcntl()的更详细用法请查阅fcntl()手册（man fcntl）。
函数fcntl()
需要头文件：#include<unistd.h>
            #include<sys/types.h>
			#include<fcntl.h>
函数原型：int fcntl(int fd,int cmd,struct flock *lock_set);
函数参数：fd：文件描述符
          cmd：检测锁或设置锁
		  lock_set：结构体类型指针，结构体struct flock需要事先设置，与第二个参数连用
函数返回值：成功：0
            失败：-1
第二个参数cmd表示该操作对文件的命令，若该命令是对文件检测锁或施加锁，则需要第三个参数：
	F_GETLK：检测文件锁状态，检测结果存放在第三个参数的结构体的l_type内
	F_SETLK：对文件进行锁操作，锁操作类型存放在第三个参数的结构体的l_type内
	F_SETLKW：同F_SETLK，不过使用该参数时若不能对文件进行锁操作则会阻塞直至可以进行锁操作为止（W即wait，等待）
	（更多参数请参阅fcntl()函数的使用手册）
第三个参数是对文件施加锁操作的相关参数设置的结构体
注意：必须定义struct flock类型结构体并初始化结构体内的数据，然后使用地址传递的方式传递参数，不允许直接定义struct flock*类型指针直接传参
关于struct flock的成员如下：
struct flock
{
	short l_type;
	short l_whence;
	off_t l_start;
	off_t l_len;
	pid_t l_pid;
}
结构体成员说明：
	l_type：有三个参数
			F_RDLCK：读锁（共享锁）
			F_WRLCK：写锁（排斥锁）
			F_UNLCK：无锁/解锁
	l_whence：相对于偏移量的起点，参数等同于fseek()与lseek()中的whence参数
			SEEK_SET：位置为文件开头位置
			SEEK_CUR：位置为文件当前读写位置
			SEEK_END：位置为文件结尾位置
	l_start：加锁区域在文件中的相对位移量，与l_whence的值共同决定加锁区域的起始位置
	l_len：加锁区域的长度，若为0则表示直至文件结尾EOF
	l_pid：具有阻塞当前进程的锁，其持有的进程号会存放在l_pid中，仅由F_GETLK返回
思考：如何设置该结构体内的成员使得加锁的范围为整个文件？
答案：设置l_whence为SEEK_SET，l_start为0，l_len为0即可。
示例：使用fcntl()函数对文件进行锁操作。首先初始化结构体flock中的值，然后调用两次fcntl()函数。第一次参数设定为F_GETLK判断是否可以执行flock内所描述的锁操作；第二次参数设定为F_SETLK或F_SETLKW对该文件进行锁操作。
注意：需要至少两个终端运行该程序才能看到效果
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/types.h>
int lock_set(int fd,int type)
{
	struct flock lock;
	lock.l_whence = SEEK_END;
	lock.l_start = 0;
	lock.l_len = 0;//三个参数设置锁的范围是全文件
	lock.l_type = type;//type的参数由主调函数传参而来
	lock.l_pid = -1;
	
	//第一次操作，判断该文件是否可以上锁
	fcntl(fd,F_GETLK,&lock);
	if(lock.l_type!=F_UNLCK)//如果l_type得到的返回值不是F_UNLCK则证明不能加锁，需判断原因
	{
		if(lock.l_type==F_RDLCK)
		{
			printf("This is a ReadLock set by %d\n",lock.l_pid);
		}
		else if(lock.l_type==F_WRLCK)
		{
			printf("This is a WriteLock set by %d\n",lock.l_pid);
		}
	}
	
	//第二次操作，对文件进行相应锁操作
	lock.l_type = type;
	if((fcntl(fd,F_SETLKW,&lock))<0)
	{
		printf("Lock Failed:type = %d\n",lock.l_type);
		return -1;
	}
	switch(lock.l_type)
	{
		case F_RDLCK:
			printf("ReadLock set by %d\n",getpid());break;
		case F_WRLCK:
			printf("WriteLock set by %d\n",getpid());break;
		case F_UNLCK:
			printf("ReleaseLock by %d\n",getpid());
			return 1;
			break;
	}
	return 0;
}
int main(int argc, const char *argv[])
{
	int fd;
	if((fd=open("hello.txt",O_RDWR))<0)
	{
		perror("fail to open hello.txt");
		exit(0);
	}
	printf("This pid_no is %d\n",getpid());
	//给文件上锁
	lock_set(fd,F_WRLCK);
	printf("Press ENTER to continue...\n");
	getchar();
	//给文件解锁
	lock_set(fd,F_UNLCK);
	printf("Press ENTER to continue...\n");
	getchar();
	close(fd);
	return 0;
}