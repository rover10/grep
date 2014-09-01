#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>

#define MAXLENGTH 128
#define KEY 7777



typedef struct msgbuf
{
	long mtype;
	char msg[MAXLENGTH];
}messageBuffer;

int main(void)
{
	
	int msgqid, size;
	int msgflag = 0666 | IPC_CREAT;
	messageBuffer m;
	msgqid = msgget(KEY, msgflag);
	if (msgqid == -1)
	{
		printf("ERROR !!!\n");
		return 0;
	}
	
	FILE *fp;

	fp = fopen("input.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open input.txt file\n");
		msgctl(msgqid, IPC_RMID, 0);
		return 0;
	}
	
	char ch;
	int i;
	
	while(1)
	{
		i = 0;
		memset(m.msg, 0, MAXLENGTH);
		ch = fgetc(fp);
		if (ch == EOF)
			break;
		while(ch != '\n')
		{
			m.msg[i++] = ch;
			ch = fgetc(fp);			
		}
		m.msg[i] = ch;
		m.mtype = 1;
		size = strlen(m.msg) + 1;
		msgsnd(msgqid, &m, size, 0);		
	}
	memset(m.msg, 0, MAXLENGTH);
	m.msg[0] = EOF;
	m.mtype = 1;
	size = strlen(m.msg) + 1;
	msgsnd(msgqid, &m, size, 0);	

	return 0;
}
