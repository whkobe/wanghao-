#include "touwenjian.h"
void handler(int signo)
{
	printf("hello\n");
}
int main()
{
	int i;
	signal(SIGALRM,handler);
	alarm(5);
	for(i=0;i<7;i++)
	{
		printf("sleep %d...\n",i);
		sleep(1);
	}
}
sleep 0...
sleep 1...
sleep 2...
sleep 3...
sleep 4...
hello
sleep 5...
sleep 6...
