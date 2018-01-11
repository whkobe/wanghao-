#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
 
 void func(int num)
 {
         printf("0\n");
 }
 
 int main(void)
 {
         int i;
         sigset_t set;
         sigset_t empty;
 
         sigemptyset(&set);
         sigemptyset(&empty);
         sigaddset(&set, SIGINT);
         signal(SIGINT, func);
 
         while(1)
         {
                 sigprocmask(SIG_BLOCK, &set, NULL);
                 for(i = 0; i < 5 ; i++)
                 {
                         write(1, "* ", strlen("* "));
                         sleep(1);
                 }
                 printf("\n");

                 sigsuspend(&empty);

                 sigprocmask(SIG_UNBLOCK, &set, NULL);
                // pause();

         }
 
         return 0;
 }

//sigsuspend设置新的屏蔽信号，保存旧的屏蔽信号，而且当sigsuspend返回的时候，恢复旧的屏蔽信号。
