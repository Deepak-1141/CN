#include <iostream>
#include <pthread.h>
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

const char *C1="C2";

struct msg{
  long type;
  char text[100];
}message;


void* reader(void* args)
{
   while(1)
   {
   	 key_t key;
        int msgid;
        key=ftok("proc2",65);
        msgid=msgget(key,0666|IPC_CREAT);
        msgrcv(msgid,&message,sizeof(message),1,0);
        cout<<"Received msg in Process 2"<<endl;
        cout<<message.text<<endl;
    //    msgctl(msgid, IPC_RMID, NULL); 
   }
}

void* writer(void* args)
{
  while(1)
  {
     string st;
     string s;
     cin>>s;
     st+=string(C1);
     st+=":";
     st+=s;
     key_t key1,key2;
     int msgid;
     key1=ftok("man",65);
     msgid=msgget(key1,0666|IPC_CREAT);
     message.type=1;
     strcpy(message.text,st.c_str());
     msgsnd(msgid,&message,sizeof(message),0);
     cout << "Message Delievered from Client 2 :: " <<message.text<<endl;
  }
}

int main()
{
	cout<<"Client2 started!!"<<endl;;
	pthread_t write_th,read_th;
	pthread_create(&write_th,NULL,writer,NULL);
	pthread_create(&read_th,NULL,reader,NULL);

	pthread_join(write_th,NULL);
	pthread_join(read_th,NULL);
}
