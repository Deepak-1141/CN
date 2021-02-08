#include<iostream>
#include<sys/ipc.h>
#include<sys/msg.h>
using namespace std;

struct msg{
  long type;
  char text[100];
}message;


int main()
{
  
  key_t key1,key2;
  int msgid;
  key1=ftok("pro1",65);
  msgid=msgget(key1,0666|IPC_CREAT);
  message.type=1;
  cout<<"Enter the msg to be send to process 1"<<endl;
  fgets(message.text,50,stdin); 
  msgsnd(msgid,&message,sizeof(message),0);
  cout<<"Send::"<<message.text<<endl;
  key2=ftok("pro2",65);
  msgid=msgget(key2,0666|IPC_CREAT);
  message.type=1;
  cout<<"Enter the msg to be send to process 2"<<endl;
  fgets(message.text,50,stdin); 
  msgsnd(msgid,&message,sizeof(message),0);
  
}
  
