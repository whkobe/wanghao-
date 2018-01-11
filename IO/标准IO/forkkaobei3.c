#include <stdio.h>  
#include <stdlib.h>  
#include <unistd.h>  
#include <fcntl.h>  
#include <sys/types.h>  
#include <sys/wait.h>  
  
#define  N  64  
  
int main(int argc, char *argv[])  
{  
    int fds, fdt, len, nbyte;  
    pid_t pid;  
    char buf[N];  
  
    if (argc < 3)  
    {  
        printf("Usage : %s <src_file> <dst_file>\n", argv[0]);  
        return -1;  
    }  
  
    if ((fds = open(argv[1], O_RDONLY)) < 0)  
    {  
        perror("fail to open");  
        exit(-1);  
    }  
  
    if ((fdt = open(argv[2], O_WRONLY|O_CREAT|O_TRUNC, 0666)) < 0)  
    {  
        perror("fail to open");  
        exit(-1);  
    }  
  
    len = lseek(fds, 0, SEEK_END);  
    len /= 2;  
  
    if ((pid = fork()) < 0)  
    {  
        perror("fail to fork");  
        exit(-1);  
    }  
    else if (pid == 0)  
    {  
      //  close(fds);  
       // close(fdt);  
      //  fds = open(argv[1], O_RDONLY);  
       // fdt = open(argv[2], O_WRONLY);  
        lseek(fds, len, SEEK_SET);  
        lseek(fdt, len, SEEK_SET);  
        while ((nbyte = read(fds, buf, N)) > 0)  
        {  
            write(fdt, buf, nbyte);  
        }  
        close(fds);  
        close(fdt);  
    }  
    else  
    {  
        lseek(fds, 0, SEEK_SET); 
		lseek(fdt, 0, SEEK_SET);		
        while (len > 0)  
        {  
            nbyte = read(fds, buf, N);  
            write(fdt, buf, nbyte);  
            len -= nbyte;  
        }  
        close(fds);  
        close(fdt);  
        wait(NULL);  
    }  
  
    return 0;  
}  
//使用父子进程来实现文件的拷贝，父进程拷贝上半部，子进程拷贝下半部。
//每次lseek之后都会改变文件指针的位置
//fork之后，文件对应的struct file是共享的，子进程注释部分就是关闭和父进程共享的file，重新打开file，但是我们的文件iNode都是同一个，都是同一个文件。