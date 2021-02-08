#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
using namespace std;

struct msg{
  long type;
  char text[100];
}message;



void* execute(void*)
{
       key_t key_main,key1,key2;
        int msgid_main,msgid1,msgid2;
         key_main=ftok("man",65);
	  msgid_main=msgget(key_main,0666|IPC_CREAT);
	  
	   key2=ftok("proc2",65);
          msgid2=msgget(key2,0666|IPC_CREAT);
          
           key1=ftok("proc1",65);
          msgid1=msgget(key1,0666|IPC_CREAT);
	while(1)
	{
	  msgrcv(msgid_main,&message,sizeof(message),1,0);
	  cout<<"Server is in Action"<<endl;
	  cout<<"Read from Client by Serever "<<message.text<<endl;

       int no = message.text[1]-'0';
        if(no==1) // msg is send by Client 1
        {
          msgsnd(msgid2,&message,sizeof(message),0);
        }
        else
        {
          msgsnd(msgid1,&message,sizeof(message),0);
        }
     }
}

int main()
{
  pthread_t t1;
  pthread_create(&t1,NULL,execute,NULL);
  pthread_join(t1,NULL);
  return 0;
}
