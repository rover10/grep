#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>

#define MAXLENGTH 128
#define KEY 7777

typedef struct msgbuf
{
	long mtype;
	char msg[MAXLENGTH];
}messageBuffer;

int main(void)
{
	//printf("hi\n");
	int msgqid;
	int msgflag = 0666 | IPC_CREAT;
	messageBuffer m;
	msgqid = msgget(KEY, msgflag);
	
	if (msgqid == -1)
	{
		printf("ERRROR !!!\n");
		return 0;
	}
	
	while(1)
	{
		msgrcv(msgqid, &m, MAXLENGTH, 0, 0);
		if (*m.msg  == EOF)
			break;
		printf("%s", m.msg);
	}	
	msgctl(msgqid, IPC_RMID, 0);
	
	return 0;
}
