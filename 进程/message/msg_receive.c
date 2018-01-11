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
	if((msgid=msgget((key_t)1234,IPC_CREAT|0666))==-1)//强制类型转换（key_t）
	{
		perror("msgget error");
		exit(1);
	}
	printf("open queue %d\n",msgid);
	while(1)
	{
		memset(data.text,0,MAX);
		if(msgrcv(msgid,(void *)&data,MAX,0,0)==-1)//第一个0表示接受消息队列中第一个消息，不管它的msgtyp是多少
		{
			perror("recive error");
			exit(1);
		}
		printf("receive is %s\n",data.text);
		if(strncmp(data.text,"quit",4)==0)
		{
			break;
		}
		
	}
	if((msgctl(msgid,IPC_RMID,NULL))==-1)
	{
		perror("delete error");
		exit(1);
	}
	exit(0);
}