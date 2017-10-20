#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* defined two sem to control the sequence of occurance of thread1
 * and thread2.
 * due to the the semaphore is shared between the threads of a process,
 * it should be located at some address that is visible to all threads.
 * here we use a global variable.
 */
sem_t	sem_1st, sem_2nd;

void* thread1_func(void *arg)
{
	static int retval_1 = 0;
	int n;
	
	if (sem_wait(&sem_1st) < 0) {
		perror("sem_wait failed");
		retval_1 = -1;
		goto _end_thread1;
	} 
	
	/* do sth in critical section */
	for (n = 0; n < 3; n++) {
		sleep(1);
		printf("AAAAAAAAAA\n");
	}

	if (sem_post(&sem_2nd) < 0) {//这里释放2信号，唤醒等待的线程2.
		perror("sem_post failed");
		retval_1 = -1;
	}
//我们在2里面释放1信号，这样就可以保证两个线程顺序执行。
_end_thread1:	
	return ((void *)&retval_1);
}

void* thread2_func(void *arg)
{
	static int retval_2 = 0;
	int n;
	
	if (sem_wait(&sem_2nd) < 0) {
		perror("sem_wait failed");
		retval_2 = -1;
		goto _end_thread2;
	} 
	
	/* do sth in critical section */
	for (n = 0; n < 3; n++) {
		sleep(1);
		printf("BBBBBBBBBB\n");
	}
	
	if (sem_post(&sem_1st) < 0) {
		perror("sem_post failed");
		retval_2 = -1;
	}
	
_end_thread2:
	return ((void *)&retval_2);
}

int main(int argc,char *argv[])
{
	pthread_t tid1, tid2;
	
	/* the first argument returns the unnamed semaphore initialized by sem_init.
	 * the second argument indicates whether this semaphore is to be shared
	 * between the threads of a process (0), or between processes (!0).
	 * the third argument specifies the intial value of the semaphore.
	 */
	if (sem_init(&sem_1st, 0, 1) < 0) { /* 1st is initialized as free */
		perror("sem_init 1st failed");
		exit(EXIT_FAILURE);
	}
	if (sem_init(&sem_2nd, 0, 0) < 0) { /* 2nd is initialized as busy */
		perror("sem_init 2nd failed");
		exit(EXIT_FAILURE);
	}
	/* create thread 1 */
	if (pthread_create(&tid1, NULL, thread1_func, NULL) != 0) {
		perror("main: pthread_create thread1 failed ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("main: pthread_create thread1[%lu] succeed!\n", tid1);
	}

	/* create thread 2 */
	if (pthread_create(&tid2, NULL, thread2_func, NULL) != 0) {
		perror("main: pthread_create thread2 failed ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("main: pthread_create thread2[%lu] succeed!\n", tid2);
	}
	
	if (pthread_join(tid1, NULL) != 0) {
		perror("main: pthread_join thread1 failed");
		exit(EXIT_FAILURE);
	}
	if (pthread_join(tid2, NULL) != 0) {
		perror("main: pthread_join thread2 failed");
		exit(EXIT_FAILURE);
	}
	
	printf("main is exiting.\n");
	
	return 0;
}
 