#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <unistd.h>

/* worker routine of thread 1.
 * thread 1 demo:
 * 	- terninates by returning from the worker routine.
 */
void *pthread_function1(void *arg)
{
	printf("thread 1: is running!\n");
	/* do sth ... */
	printf("thread 1: is leaving!\n");
	return NULL; /* return 0; or exit w/o return */
}

/* worker routine of thread 2.
 * thread 2 demo:
 * 	- terminates by calling pthread_exit, specifying an exit 
 *	status value that is available to another thread in the
 *	same process that calls pthread_join.
 */
void *pthread_function2(void *arg)
{
	printf("thread 2: is running!\n");
	/* do sth ... */
	printf("thread 2: is exiting by self!\n");
	pthread_exit(NULL);
}

/* worker routine of thread 3.
 * thread 3 demo:
 * 	- terminated by cancelled by other thread
 */
void *pthread_function3(void *arg)
{
	printf("thread 3: is running!\n");
	while(1) {
		sleep(1); /* waiting to be cancelled by others */
	}
	printf("thread 3: is leaving!\n");
}

int main()
{
	pthread_t	tid1, tid2, tid3;
	void		*retval;

	/* create thread 1 */
	if (pthread_create(&tid1, NULL, pthread_function1, NULL) != 0) {
		perror("main: pthread_create thread1 failed ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("main: pthread_create thread1[%lu] succeed!\n", tid1);
	}

	/* create thread 2 */
	if (pthread_create(&tid2, NULL, pthread_function2, NULL) != 0) {
		perror("main: pthread_create thread2 failed ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("main: pthread_create thread2[%lu] succeed!\n", tid2);
	}

	/* create thread 3 */
	if (pthread_create(&tid3, NULL, pthread_function3, NULL) != 0) {
		perror("main: pthread_create thread3 failed ");
		exit(EXIT_FAILURE);
	}
	else {
		printf("main: pthread_create thread3[%lu] succeed!\n", tid3);
	}
	
	/* wait and join thread 1 */
	if (pthread_join(tid1, &retval) != 0) {
		perror("main: pthread_join thread1 failed");
		exit(EXIT_FAILURE);
	}
	printf("main: pthread_join thread1[%lu] succeed.\n", tid1);
	
	/* wait and join thread 2 */
	if (pthread_join(tid2, &retval) != 0) {
		perror("main: pthread_join thread2 failed");
		exit(EXIT_FAILURE);
	}
	printf("main: pthread_join thread2[%lu] succeed.\n", tid2);

	/* cancel thread 3
	 * Note the return status of pthread_cancel() merely informs 
	 * whether the cancellation request was successfully queued.
	 * Joining with the cancelled thread is the only way to know
	 * that cancellation has actually completed.
	 */
	if((pthread_cancel(tid3)) != 0) {
		perror("main: pthread_cancel thread3 failed");
		exit(EXIT_FAILURE);
	}
	printf("main: pthread_cancel thread3[%lu] succeed.\n", tid3);
	
	/* wait and join thread 3, till now we know the thread 3 was terminated. */
	if (pthread_join(tid3, &retval) != 0) {
		perror("main: pthread_join thread3 failed");
		exit(EXIT_FAILURE);
	}
	if (PTHREAD_CANCELED == retval)
		printf("main: pthread_join thread3[%lu] succeed, thread3 was cancelled.\n", tid3);
	else
        	printf("main: thread3 wasn't canceled (shouldn't happen!)\n");

	return 0;
}
