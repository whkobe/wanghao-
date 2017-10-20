#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* thread1_func(void *arg)
{
	int	n;	
	
	for (n = 0; n < 3; n++) {
		sleep(1);
		printf("AAAAAAAAAA\n");
	}

	pthread_exit(NULL);
	//return 0;
}

void* thread2_func(void *arg)
{
	int n;

	for (n = 0; n < 3; n++) {
		sleep(1);
		printf("BBBBBBBBBB\n");
	}

	return 0;
}

int main(int argc,char *argv[])
{
	pthread_t tid1, tid2;
	
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
 //两个线程打印。每个线程的运行和结束是无序的，独立并行的。