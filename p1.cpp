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
int p1id;

inline void received1(int sig_no)
{
    cout<<"Process 1 got the signal"<<endl;
    int ge=*shmY;
    cout<<"Process 1 read the id"<<ge<<endl;
    *shmX=p1id;
    cout<<"Process 1 wrote"<<endl;
    sleep(2);
    kill(ge,SIGUSR1);


}

int main()
{
    signal(SIGUSR2,received1);
    X=ftok("fileX",100);
    shmidX=shmget(X,sizeof(int),IPC_CREAT|0666);
    shmX=(int *)shmat(shmidX,NULL,0); // attaching with shared memory
    *shmX=0;

    Y=ftok("fileX",200);
    shmidY=shmget(Y,sizeof(int),IPC_CREAT|0666);
    shmY=(int *)shmat(shmidY,NULL,0);
    *shmY=0;

    // forking the process
    pid_t pid=fork();
     
     if(pid==0)
     {
         cout<<"Child will execute P2"<<endl;
         execl("./b.out","./b.out",NULL);
     }
     else
     {
         int processid=getpid();
         p1id=processid;
         cout<<"ID of Process 1:: "<<processid<<endl;
         *shmX=processid;
         for(;;)
         {
             cout<<"Process 1 is waiting"<<endl;
             sleep(2);
         }
     }
}
