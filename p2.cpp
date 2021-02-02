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


int *shmX;
int *shmY;
key_t X,Y;
int shmidX;
int shmidY;
int p2id;

inline void received2(int sig_no)
{
    cout<<"Process 2 got the signal"<<endl;
    int ge=*shmX;
    cout<<"Process 2 read the id"<<ge<<endl;
    *shmY=p2id;
    cout<<"Process 2 wrote"<<endl;
    sleep(2);
    kill(ge,SIGUSR2);


}

int main()
{
    cout<<"Action::Process2"<<endl;
    signal(SIGUSR1,received2);
    X=ftok("fileX",100);
    shmidX=shmget(X,sizeof(int),0666);
    shmX=(int *)shmat(shmidX,NULL,0); // attaching with shared memory

    Y=ftok("fileX",200);
    shmidY=shmget(Y,sizeof(int),0666);
    shmY=(int *)shmat(shmidY,NULL,0);
    int id=*shmX;
    cout<<"Process 2 read id"<<id<<endl;
    
    p2id=getpid();
    *shmY=p2id;
    cout<<"Process 2 writes now"<<endl;
    kill(id,SIGUSR2);
    for(;;)
    {
      cout<<"Waiting for signal::P2"<<endl;
      sleep(2);
    }
}
