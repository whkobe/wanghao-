#include "touwenjian.h"
#define MAX 512
struct message
{
	long msg_type;
	char text[MAX];
};
int main()
{
	int msgid;
	struct message data;
	if((msgid=msgget((key_t)1234,IPC_CREAT|0666))==-1)
	{
		perror("msgget error");
		exit(1);
	}
	while(1)
	{
		printf("please enter message to the queue\n");
		if((fgets(data.text,MAX,stdin))==NULL)
		{
			perror("no message");
			exit(1);
		}
		data.msg_type=1;//消息的类型
		if((msgsnd(msgid,(void *)&data,strlen(data.text),0))==-1)//0表示调用阻塞直到发送成功为止
		{
			perror("send error");
			exit(1);
		}
		if(strncmp(data.text,"quit",4)==0)
		{
			break;
		}
	}
	exit(0);
}