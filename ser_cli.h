#include <sqlite3.h>
#include <time.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <arpa/inet.h>

#define CLI_REQUEST    (unsigned short)0x0001 /*客户端发起的用户注册请求*/
#define SER_REQUEST    (unsigned short)0x8001 /*服务器对用户注册请求的响应*/

#define CLI_LOGIN       (unsigned short)0x0002 /*客户端发起的用户登陆请求*/
#define SER_LOGIN       (unsigned short)0x8002 /*服务器对用户登陆请求的响应*/

#define CLI_QUERYWORD   (unsigned short)0x0003 /*客户端发起的单词查询请求*/
#define SER_QUERYWORD   (unsigned short)0x8003 /*服务器对单词查询请求的响应*/

#define CLI_HISTORY     (unsigned short)0x0004 /*客户端发起的历史记录查询请求*/
#define SER_HISTORY     (unsigned short)0x8004 /*服务器对历史查询请求的响应*/

#define CLI_EXIT        (unsigned short)0x0005 /*客户端发起的退出登陆请求*/

/*返回状态说明*/
#define FAIL			(unsigned short)0x0023 /*失败*/
#define SUCCES      	(unsigned short)0x0010 /*成功*/
#define USEREXIST   	(unsigned short)0x0011 /*用户已存在*/
#define NUSEREXIST  	(unsigned short)0x0012 /*用户不存在*/
#define INSERTERR   	(unsigned short)0x0013 /*插入用户失败*/
#define WRONGPASSWD		(unsigned short)0x0014 /*用户密码错误*/
#define RIGHTPASSWD 	(unsigned short)0x0015 /*用户密码正确*/
#define USERONLINE  	(unsigned short)0x0016 /*用户已在线*/
#define USEROFFLINE 	(unsigned short)0x0017 /*用户不在线*/
#define NOFINDWORD  	(unsigned short)0x0018 /*未找到单词*/
#define NOHISTORY  		(unsigned short)0x0019 /*查找用户历史失败*/
#define FINEERR       	(unsigned short)0x0020 /*查找数据库查询出错*/
#define SENDUNSUCCES    (unsigned short)0x0021 /*正在发送查找*/
#define SENDSUCCES      (unsigned short)0x0022 /*历史记录发送完毕*/
#define  state_t unsigned short
#define SA struct sockaddr 
#define SIZE 1024
typedef struct para
{
	int cmd;
	state_t state;
	char account[30];
	char pwd[30];
	char data[SIZE];
}para_a;


//服务器子函数

//客户端子函数
