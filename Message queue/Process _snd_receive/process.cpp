#include<iostream>
#include<sys/ipc.h>
#include<sys/msg.h>
using namespace std;

struct msg{
  int type;
  string text;
}message;

int main()
{
  
  key_t key;
  int msgid;
  key=ftok("aa",65);
  msgid=msgget(key,0666|IPC_CREAT);
  message.type=1;
  cout<<"Enter the msg to be send"<<endl;
  cin>>message.text;
  msgsnd(msgid,&message,sizeof(message),0);
  cout<<"Msg received is::"<<endl;
  cout<<message.text<<endl;
}
  
