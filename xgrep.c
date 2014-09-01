#include <sys/ipc.h>
#include <sys/msg.h>
#include <stdio.h>
#include <string.h>
#include<stdlib.h>
//---------------------------------
#define MAXLENGTH 128
#define KEY 7777

typedef struct msgbuf{ //Message received here
	long mtype;
	char msg[MAXLENGTH];
}messageBuffer;

//--------------------------------

//Intermediate line will be stored in the form of linked list buffer

struct msgNode{
	char buffer[128];
	struct msgNode *next;
};

int main(int argn, char **argc ){

int totalFiles=0;
struct msgNode *msgHead=NULL;


//-------------receiving message code here------------------------------//
int msgqid;
	int msgflag = 0666|IPC_CREAT;
	messageBuffer m;
	msgqid = msgget(KEY, msgflag);
	
	if (msgqid == -1)
	{
		printf("ERRROR !!!\n");
		return 0;
	}
	
//--------------------Receive the first message to find the number of files data sent to grep(NOT NEED BECAUSE MAIN PROGRAM WILL TAKE CARE OF THAT ISSUE & WILL SENT THEM ALL TO GREP AS A SINGLE FILE OUTPUT)

//--------------------

	int nodecount=0; 

struct msgNode *tail=NULL;
	while(1){
		msgrcv(msgqid, &m, MAXLENGTH, 0, 0);
		

//
for(int i=0;i<128;i++)
  printf("%c",m.msg[i]);
//
		if (*m.msg== EOF)
			break;

			if(msgHead==NULL){
				msgHead=(struct msgNode*) malloc(sizeof(struct msgNode));
				msgHead->next=NULL;
				tail=msgHead;
			       	 }
           			//}
			else{
				tail=tail->next;
				tail=(struct msgNode*) malloc(sizeof(struct msgNode));
				
				tail->next=NULL;
				}
	
			for(int j=0;j<MAXLENGTH;j++) // copying msg buffer data to node buffer
					{tail->buffer[j]=m.msg[j]; printf("..%c ", m.msg[j]);}

                nodecount++;	
		printf("%s", m.msg);
	}

	
	char *para=(char*) malloc(nodecount*MAXLENGTH + 1);

	para[nodecount*MAXLENGTH]='\0'; //ending the line for extra safety we can put EOF also there !
	int i=0;

	struct msgNode *temp=msgHead;
	while(i<nodecount){      
	                        //Making a big sentence of whole input;
                for(int j=i*MAXLENGTH; j<(i+1)*MAXLENGTH;j++){
			printf("j= : %d\n", j);
			 
			para[j]=temp->buffer[j % MAXLENGTH];
			printf("para j= : %c\n", para[j]);
			}
		printf("Fucking shit i: %d\n", i); 
				    
	    i++;
		if(temp==NULL)
			break;
	    temp=temp->next;
          }
	printf("Fucking shit 2\n");
	msgctl(msgqid, IPC_RMID, 0);	
// freeing the memory acquired by malloc//
  temp=msgHead;
  struct msgNode *temp2=msgHead;

  while(temp!=NULL){
	temp2=temp;
	temp=temp->next;
	free(temp2);
       }

//---------------------------------------------------------------------//

		//---------------------------//
	char sub[128]; // For storing the substring
	FILE *fd; 
	printf("Opening pattern.txt\n");
	fd=fopen("pattern.txt","r");
	char ch; 
	i=0;
	while((ch=fgetc(fd))!=EOF)
		sub[i++]=ch;

//search the string
	char *trav=para;
	while(trav!=NULL){
	     trav=strpbrk(sub,trav); //trav is the search string 
		if(trav!=NULL){
        		while(*trav !='\n' && trav!=para)  //travesing back for '\n' or start of 'para'
				--trav;
			while(*trav!='\n')
				printf("%c",*trav);
			printf("\n");
		        trav++; //skiping new line & seraching subtring in new
                    } 
             }

///Freeing the character array
   free(para);
		/* if true , we got a match ! Now  travesere back until a new line '\n' is found
		 & print that until a new line '\n' is found  by travesing forward...then  tempara=(address value just after '\n' in foward direction ) */
            

//---------------------------------------------------------------------//
//Algorithm ----------------------------------------------
/*for(int i=0;i<argn;i++)
	printf("%s",*(argc+i));
*/

/* The first message contains the << number of files >>  from the << head/tail/cat >> command so that the receiver waits for that number of
	EOF before it exist...In this way we can implement GREP capable of   

*/

/* fetch data into buffer until \n or \0 is found*/
	//keep the data into a linked list of msg buffer
/* If endline  is encountered then  */
       // make a char array of size=(no of nodes("maintain a count of node in the liked list") * 128)
       //  now scan the char arry just created above and then serach form the specified pattern using any string matching algorithm.
		// If pattern matched then print the line else discard it and rebulid the linked list by freeing(Memory) int the linked list;
			//Continue this process until a end of lie is encountered 
					 
return 0;
}
