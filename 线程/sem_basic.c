#include <pthread.h>
#include <semaphore.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>

int main(int argc,char *argv[])
{
	sem_t	sem;
	int	sval;
	
	printf("%d\n", SEM_VALUE_MAX);
	
	if (sem_init(&sem, 0, 0) < 0) {
		perror("sem_init failed");
		exit(EXIT_FAILURE);
	}
	
	

	while (1) {
		if (sem_post(&sem) < 0) {
			perror("sem_post failed");
			break;
		}
		if (sem_getvalue(&sem, &sval) < 0) {
			perror("sem_getvalue failed");
			exit(EXIT_FAILURE);
		}
		printf("max number of semaphores = %d\n", sval);
	}
	if (sem_getvalue(&sem, &sval) < 0) {
			perror("sem_getvalue failed");
			exit(EXIT_FAILURE);
	}
	printf("max number of semaphores = %d\n", sval);
	
	return 0;
}
 