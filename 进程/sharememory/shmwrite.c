#include "touwenjian.h"
#define MAX 512
int main()
{
	int running=1;
	void *shm=NULL;
	struct shared_use_st *shared=NULL;
	char buffer[MAX+1];
	int shmid;
	if((shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT))==-1)//创建共享内存
	{
		perror("shmget error");
		exit(1);
	}
	
	if((shm=shmat(shmid,(void *)0,0))==(void *)-1)//映射
	{
		perror("shmat error");
		exit(1);
	}
	
	printf("Memoryattached at %p\n",shm);
	
	shared=(struct shared_use_st *)shm;
	while(running)
	{
		while(shared->written==1)
		{
			sleep(1);
			printf("waiting read...\n");
		}
		printf("enter some text:");
		fgets(buffer,MAX,stdin);
		strncpy(shared->text,buffer,TEXT_SE);
		shared->written=1;
		if(strncmp(buffer,"end",3)==0)
			running=0;
	}
	if(shmdt(shm)==-1)//把共享内存从当前进程中分离
	{
		perror("shmdt error");
		exit(1);
	}
	sleep(2);

	exit(0);
}