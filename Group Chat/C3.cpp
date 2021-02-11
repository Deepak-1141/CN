#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
using namespace std;


struct msg_buf{
	long msg_type;
	char msg[100];
};

int msg_id1=msgget(1000,0666|IPC_CREAT);
int msg_id3=msgget(1002,0666|IPC_CREAT);

void* W3(void* )
{
	msg_buf ms1,ms2;
	ms1.msg_type=1;
	while(true){
	
		char ms[100];
		cin.getline(ms,100);
		strcpy(ms1.msg,"P3\0");
		strcat(ms1.msg,ms);
		cout<<"Message delievered from C3:"<<ms1.msg<<endl;
		cout<<"Group1:a else b"<<endl;
		char ch;
		cin>>ch;
		if(ch=='a')
		{
		  msgsnd(msg_id1,&ms1,sizeof(ms1),0);
		}
		else
		{
		   msgsnd(msg_id3,&ms1,sizeof(ms1),0);
		}
		cin.ignore();
	}
}

void* R3(void* )
{
	while(true)
	{
		msg_buf ms2;
		msgrcv(msg_id1,&ms2,sizeof(ms2),5,0);
		cout<<"Message Received in C3"<<ms2.msg<<endl;
	}
}

void* G1(void* )
{
	while(true)
	{
		msg_buf ms2;
		msgrcv(msg_id3,&ms2,sizeof(ms2),5,0);
		cout<<"Message Received from Global"<<ms2.msg<<endl;
	}
}

int main()
{
	pthread_t t1,t2,t3;
	pthread_create(&t1,NULL,W3,NULL);
	pthread_create(&t2,NULL,R3,NULL);
	pthread_create(&t3,NULL,G1,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	return 0;
}
