#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>   
#include <stdio.h>
#include <stdlib.h>

#define BUFSZ 512
#define TYPE  100

struct protocolX {
	int	field1;
	char	field2;
	float	field3;
	char	field4[BUFSZ];
}; 

struct msgbuf{
	long			type;
	struct protocolX	data;
};

int main()
{
	int		qid, len;
	key_t		key;
	struct	msgbuf	msg;
	
	if ((key = ftok(".", 100)) == -1){
		perror("ftok error");
		exit(-1);
	}
	
	if ((qid = msgget(key, IPC_CREAT|0666)) == -1){
		perror("msgget error");
		exit(-1);
	}

	printf("opened queue %d\n", qid);
	msg.type = TYPE;
	msg.data.field1 = 100;
	msg.data.field2 = 'X';
	msg.data.field3 = 9.9;
	puts("Please enter the message to queue:");
	if ((fgets(msg.data.field4, BUFSZ, stdin)) == NULL){
		puts("no message");
		exit(-1);
	}
	len = sizeof(msg) - sizeof(long);//消息正文的字节数（不包括消息类型指针变量）
	/* send msg to queue */
	if (msgsnd(qid, &msg, len, 0) < 0){
		perror("msgsnd error");
		exit(-1);
	}

	/* recv msg from the queue */
	if (msgrcv(qid, &msg, len, 0, 0) < 0){
		perror("msgrcv error");
		exit(-1);
	}
	printf( "message.type = %ld\n"
		"message.data.field1 = %d\n"
		"message.data.field2 = %c\n"
		"message.data.field3 = %f\n"
		"message.data.filed4 = %s\n",
		msg.type,
		msg.data.field1,
		msg.data.field2,
		msg.data.field3,
		msg.data.field4);
	
	/* remove msg queue from system */
	if (msgctl(qid, IPC_RMID, NULL) < 0){
		perror("msgctl error");
		exit(-1);
	}
	return 0;
}
