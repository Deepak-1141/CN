#include<bits/stdc++.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<stdio.h>
#include<pthread.h>
using namespace std;


struct msg_buf{
	long msg_type;
	char msg[100];
};

//     G1,G2,Global

int msg_id1=msgget(1000,0666|IPC_CREAT);
int msg_id2=msgget(1001,0666|IPC_CREAT);
int msg_id3=msgget(1002,0666|IPC_CREAT);


void* G1(void* )
{
	msg_buf ms1,ms2,ms3,ms4;
	
	while(true)
	{
		msgrcv(msg_id1,&ms1,sizeof(ms1),1,0);
		cout<<"Message Received:: "<<ms1.msg<<endl;
		int x=ms1.msg[1]-'0';
		strcpy(ms2.msg,"\0");
		strcpy(ms3.msg,"\0");
		strcpy(ms4.msg,"\0");
		strcpy(ms2.msg,ms1.msg);
		strcpy(ms3.msg,ms1.msg);
		strcpy(ms4.msg,ms1.msg);
		ms2.msg_type=3;//for writing in c1
		ms3.msg_type=4;//for writing in c2
		ms4.msg_type=5;//for writing in c3
		//cout<<x<<endl;
		if(x==1){//message recieved from c1
			msgsnd(msg_id1,&ms3,sizeof(ms3),0);//to c2
			msgsnd(msg_id1,&ms4,sizeof(ms4),0);//to c3
		}
		else if(x==2){//message recieved from c2
			msgsnd(msg_id1,&ms2,sizeof(ms2),0);//to c1
			msgsnd(msg_id1,&ms4,sizeof(ms4),0);//to c3
		}
		else{//message recieved from c3
			msgsnd(msg_id1,&ms2,sizeof(ms2),0);//to c1
			msgsnd(msg_id1,&ms3,sizeof(ms3),0);//to c2
		}
	}
}
void* G2(void* )
{
	msg_buf ms1,ms2,ms3,ms4;
	
	while(true)
	{
		msgrcv(msg_id2,&ms1,sizeof(ms1),1,0);
		cout<<"Message Received:: "<<ms1.msg<<endl;
		int x=ms1.msg[1]-'0';
		strcpy(ms2.msg,"\0");
		strcpy(ms3.msg,"\0");
		strcpy(ms4.msg,"\0");
		strcpy(ms2.msg,ms1.msg);
		strcpy(ms3.msg,ms1.msg);
		strcpy(ms4.msg,ms1.msg);
		ms2.msg_type=3;//for writing in c4
		ms3.msg_type=4;//for writing in c5
		ms4.msg_type=5;//for writing in c6
		//cout<<x<<endl;
		if(x==1){//message recieved from c4
			msgsnd(msg_id2,&ms3,sizeof(ms3),0);//to c5
			msgsnd(msg_id2,&ms4,sizeof(ms4),0);//to c6
		}
		else if(x==2){//message recieved from c5
			msgsnd(msg_id2,&ms2,sizeof(ms2),0);//to c4
			msgsnd(msg_id2,&ms4,sizeof(ms4),0);//to c6
		}
		else{//message recieved from c6
			msgsnd(msg_id2,&ms2,sizeof(ms2),0);//to c4
			msgsnd(msg_id2,&ms3,sizeof(ms3),0);//to c5
		}
	}
}
void* Global(void* )
{
	msg_buf ms1,ms2,ms3,ms4,ms5,ms6,ms7;
	
	while(true)
	{
		msgrcv(msg_id3,&ms1,sizeof(ms1),1,0);
		cout<<"Message Received"<<ms1.msg<<endl;
		int x=ms1.msg[1]-'0';
		char y=ms1.msg[0];
		strcpy(ms2.msg,"\0");
		strcpy(ms3.msg,"\0");
		strcpy(ms4.msg,"\0");
		strcpy(ms5.msg,"\0");
		strcpy(ms6.msg,"\0");
		strcpy(ms7.msg,"\0");
		strcpy(ms2.msg,ms1.msg);
		strcpy(ms3.msg,ms1.msg);
		strcpy(ms4.msg,ms1.msg);
		strcpy(ms5.msg,ms1.msg);
		strcpy(ms6.msg,ms1.msg);
		strcpy(ms7.msg,ms1.msg);
		ms2.msg_type=3;//for writing in C1
		ms3.msg_type=4;//for writing in C2
		ms4.msg_type=5;//for writing in C3
		ms5.msg_type=6;//for writing in C4
		ms6.msg_type=7;//for writing in C5
		ms7.msg_type=8;//for writing in C6
		if(x==1)
		{
			if(y=='P')
			{
			
			// Send to C2,C3,C4,C5,C6
				msgsnd(msg_id3,&ms3,sizeof(ms3),0);
				msgsnd(msg_id3,&ms4,sizeof(ms4),0);
				msgsnd(msg_id3,&ms5,sizeof(ms5),0);
				msgsnd(msg_id3,&ms6,sizeof(ms6),0);
				msgsnd(msg_id3,&ms7,sizeof(ms7),0);
			}
			else
			{	
			// Send to C1,C3,C2,C5,C6
				msgsnd(msg_id3,&ms3,sizeof(ms3),0);
				msgsnd(msg_id3,&ms4,sizeof(ms4),0);
				msgsnd(msg_id3,&ms2,sizeof(ms2),0);
				msgsnd(msg_id3,&ms6,sizeof(ms6),0);
				msgsnd(msg_id3,&ms7,sizeof(ms7),0);
			}
		}
		else if(x==2)
		{
			if(y=='P')
			{
			
			  // Send to C1,C4,C3,C5,C6
				msgsnd(msg_id3,&ms2,sizeof(ms2),0);
				msgsnd(msg_id3,&ms4,sizeof(ms4),0);
				msgsnd(msg_id3,&ms5,sizeof(ms5),0);
				msgsnd(msg_id3,&ms6,sizeof(ms6),0);
				msgsnd(msg_id3,&ms7,sizeof(ms7),0);
			}
			else
			{
			
			// Send to C1,C2,C3,C4,C6
				msgsnd(msg_id3,&ms3,sizeof(ms3),0);
				msgsnd(msg_id3,&ms4,sizeof(ms4),0);
				msgsnd(msg_id3,&ms5,sizeof(ms5),0);
				msgsnd(msg_id3,&ms2,sizeof(ms2),0);
				msgsnd(msg_id3,&ms7,sizeof(ms7),0);
			}
			
		}
		else
		{
			if(y=='P')
			{
			
			  // Send to C1,C2,C4,C5,C6
				msgsnd(msg_id3,&ms3,sizeof(ms3),0);
				msgsnd(msg_id3,&ms4,sizeof(ms4),0);
				msgsnd(msg_id3,&ms2,sizeof(ms2),0);
				msgsnd(msg_id3,&ms6,sizeof(ms6),0);
				msgsnd(msg_id3,&ms7,sizeof(ms7),0);
			}
			else{
			
			// Send to C1,C2,C3,C5,C4
				msgsnd(msg_id3,&ms3,sizeof(ms3),0);
				msgsnd(msg_id3,&ms4,sizeof(ms4),0);
				msgsnd(msg_id3,&ms5,sizeof(ms5),0);
				msgsnd(msg_id3,&ms6,sizeof(ms6),0);
				msgsnd(msg_id3,&ms2,sizeof(ms2),0);
			}
		}
	}
}
int main()
{
	pthread_t t1,t2,t3;
	pthread_create(&t1,NULL,G1,NULL);
	pthread_create(&t2,NULL,G2,NULL);
	pthread_create(&t3,NULL,Global,NULL);
	pthread_join(t1,NULL);
	pthread_join(t2,NULL);
	pthread_join(t3,NULL);
	return 0;
}
