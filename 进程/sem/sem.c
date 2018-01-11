#include "touwenjian.h"
int init_sem(int sem_id,int init_value)
{
	union semun	sem_union;//这个联合体系统中没有给出 ，在头文件中自己定义
    sem_union.val=init_value;//信号量的初始值
    if(semctl(sem_id,0,SETVAL,sem_union)==-1)
    {
        perror("initialize error");
        return -1;
    }
    return 0;
}

int del_sem(int sem_id)
{
    union semun sem_union;
    if(semctl(sem_id,0,IPC_RMID,sem_union)==-1)
    {
        perror("delete error");
        return -1;
    }
}

int sem_p(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num=0;
    sem_b.sem_op=-1;//-1表示p操作
    sem_b.sem_flg=SEM_UNDO;//如果进程没有释放信号量而退出，系统自动释放该进程中未释放的信号量
    if(semop(sem_id,&sem_b,1)==-1)
    {
        perror("p error");
        return -1;
    }
    return 0;
}

int sem_v(int sem_id)
{
    struct sembuf sem_b;
    sem_b.sem_num=0;
    sem_b.sem_op=1;//1表示v操作
    sem_b.sem_flg=SEM_UNDO;
    if(semop(sem_id,&sem_b,1)==-1)
    {
        perror("v error");
        return -1;
    }
    return 0;
}

