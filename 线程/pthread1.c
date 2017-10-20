#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdlib.h>
char message[32]="HelloWorld";
void *thread_function(void *arg);

int main()
{
	pthread_t a_thread;
	void *thread_result;
	printf("zzz%d\n",getpid());
	if(pthread_create(&a_thread,NULL,thread_function,(void*)message)<0)
	{
		perror("fail to pthread_create");
		exit(-1);
	}
	printf("waiting for thread to finish\n");
	if(pthread_join(a_thread,&thread_result)<0)
	{
		perror("faill to pthread_join");
		exit(-1);
	}
	printf("Message is now %s\n",message);
	printf("thread_result is %s\n",(char*)thread_result);
	return 0;
}
void *thread_function(void *arg)
{
	
	printf("xxx%d\n",getpid());
	printf("thread_function is running ,argument is %s\n",(char*)arg);
	strcpy(message,"marked by thread");
	pthread_exit("Thank you for the cpu time");
}
		
结果如下:
zzz2669
waiting for thread to finish
xxx2669
thread_function is running ,argument is HelloWorld
Message is now marked by thread
thread_result is Thank you for the cpu time
//可以看出，线程和进程共用一个pid号。
pthread_join函数可以接收pthread_exit的返回值
		