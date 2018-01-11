#include "touwenjian.h"
#define T 3
int main()
{
    pid_t result;
    int sem_id;
    sem_id=semget(ftok(".",1),1,0666|IPC_CREAT);//此时创建一个信号量
    init_sem(sem_id,0);//传入的数据为0，将信号量的初始值设为0，说明此时申请不到信号，必须先释放
    
    result = fork();
    if(result==-1)
    {
        perror("fork error");
    }
    else if(result==0)
    {
        printf("child process will wait \n");
        sleep(T);
        printf("the return value is %d int child process(pid=%d)\n",result,getpid());
        sem_v(sem_id);
    }
    else
    {
        sem_p(sem_id);//因为初始化的信号量为0，所以此时没有可用信号，必须等子进程释放一个信号才可以
        printf("the return value is %d int father process(pid=%d)\n",result,getpid());
        sem_v(sem_id);
        del_sem(sem_id);
    }
    exit(0);
}
