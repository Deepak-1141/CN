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
  
  key_t key;
  int msgid;
  key=ftok("pro1",65);
  msgid=msgget(key,0666|IPC_CREAT);
  msgrcv(msgid,&message,sizeof(message),1,0);
  cout<<"Received msg in Process 1"<<endl;
 cout<<message.text<<endl;
}
  
