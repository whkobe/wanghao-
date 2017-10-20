#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

pthread_mutex_t  mutex;

void* thread1_func(void *arg)
{
	static int retval_1 = 0;
	int	n;	
	
	pthread_mutex_lock(&mutex);
	
	for (n = 0; n < 3; n++) {
		sleep(1);
		printf("AAAAAAAAAA\n");
	}

	pthread_mutex_unlock(&mutex);
	
	return ((void *)&retval_1);
}

void* thread2_func(void *arg)
{
	static int retval_2 = 0;
	int n;

	pthread_mutex_lock(&mutex);
	for (n = 0; n < 3; n++) {
		sleep(1);
		printf("BBBBBBBBBB\n");
	}

	pthread_mutex_unlock(&mutex);
	
	return ((void *)&retval_2);
}

int main(int argc,char *argv[])
{
	pthread_t tid1, tid2;
	
	if (pthread_mutex_init(&mutex, NULL) < 0) {
	    perror("pthread_mutex_init error");
	    exit(-1);
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
 //对两个线程使用锁，当一个线程执行，获得锁，打印。虽然有sleep函数进行睡眠，但是该线程没有释放锁，
 //所以其他线程没发获得锁。若线程对一个已经被上锁的互斥锁加锁时，该线程会睡眠。
main: pthread_create thread1[3076500288] succeed!
main: pthread_create thread2[3068107584] succeed!
AAAAAAAAAA
AAAAAAAAAA
AAAAAAAAAA
BBBBBBBBBB
BBBBBBBBBB
BBBBBBBBBB
main is exiting.
