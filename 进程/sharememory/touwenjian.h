#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/msg.h>
#include <signal.h>
#include <sys/shm.h>

#ifndef _SHMDATA_H_HEADER
#define _SHMDATA_H_HEADER
#define TEXT_SZ 2048
struct shared_use_st
{
	int written//0表示可写，1表示可读
	char text[TEXT_SZ];
};
#endif
