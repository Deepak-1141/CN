#include <iostream>
#include <string>
#include <sstream>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <errno.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
using namespace std;

pthread_t tid;

int *shmX;
int *shmY;
key_t X,Y;
int shmidX;
int shmidY;

void p2_handler(int sig_no)
{
  int ge=*shmY;
   cout<<"P1 received the signal"<<endl;
   *shmX=tid;
   sleep(2);
   pthread_kill(ge,SIGUSR1);
   
}

void *created(void *arg)
{
  return NULL;
}

int main()
{
  signal(SIGUSR2,p2_handler);
  pthread_create(&tid, NULL, created, NULL); 
  
  X=ftok("aa",100);
    shmidX=shmget(X,sizeof(int),IPC_CREAT|0666);
    shmX=(int *)shmat(shmidX,NULL,0); // attaching with shared memory
    *shmX=0;

    Y=ftok("aa",200);
    shmidY=shmget(Y,sizeof(int),IPC_CREAT|0666);
    shmY=(int *)shmat(shmidY,NULL,0);
    *shmY=0;
    
    sleep(2);
  
  cout<<"P1 is sending a signal"<<endl;
  *shmX=tid;
  execl("./b","./b",NULL);
  while(1);
}
