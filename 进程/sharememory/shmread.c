#include "touwenjian.h"
#define MAX 512
int main()
{
	int running=1;
	void *shm=NULL;
	struct shared_use_st *shared=NULL;
	char buffer[MAX+1];
	int shmid;
	if((shmid=shmget((key_t)1234,sizeof(struct shared_use_st),0666|IPC_CREAT))==-1)
	{
		perror("shmget error");
		exit(1);
	}
	
	if((shm=shmat(shmid,(void *)0,0))==(void *)-1)
	{
		perror("shmat error");
		exit(1);
	}
	
	printf("Memoryattached at %p\n",shm);
	
	shared=(struct shared_use_st *)shm;
	while(running)
	{
		if(shared->written!=0)
		{
			printf("you wrote:%s",shared->text);
			sleep(1);
			shared->written=0;
			if(strncmp(shared->text,"end",3)==0)
				running=0;
		}
		else
			sleep(1);
	}
	if(shmdt(shm)==-1)
	{
		perror("shmdt error");
		exit(1);
	}
	if(shmctl(shmid,IPC_RMID,0)==-1)
	{
		perror("delete error");
		exit(1);
	}
	exit(1);
}
