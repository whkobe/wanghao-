#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
pthread_mutex_t lock;
void *thread_fun()
{
	
	int i;
	while(1)
	{
		pthread_mutex_lock(&lock);
		for(i=0;i<3;i++)
		{
			sleep(1);
			printf("aaa\n");
		}
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}
main()
{

	int i;
	pthread_t pid;
	if(pthread_mutex_init(&lock,NULL)<0)
		printf("error");
	else
		printf("okk\n");
	if(pthread_create(&pid,NULL,thread_fun,NULL)!=0)//我写成了thread_fun()，找了一晚上原因
		printf("error\n");
	else
		printf("OK\n");
	while(1)
	{
		pthread_mutex_lock(&lock);
		for(i=0;i<2;i++)
			{
				sleep(1);
				printf("bbb\n");
			}
		
		pthread_mutex_unlock(&lock);
		sleep(1);
	}
}

//sleep会睡眠，当所已经解开时sleep，就会调度其他线程，获得锁。