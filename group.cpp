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

int pids[6];
int pid;

static void Parent(int sig)
{
    cout << "PARENT\n";
}

static void Child1(int sig)
{
    cout << "CHILD 1\n";
}

static void Child2(int sig)
{
    cout << "CHILD 2\n";
}

static void Child3(int sig)
{
    cout <<"CHILD 3\n";
}

static void Child4(int sig)
{
    cout << "CHILD 4\n";
}

static void Child5(int sig)
{
    cout << "CHILD 5\n";
}

int main()
{

    pid = fork();
    if (pid == 0)
    {
        signal(SIGUSR1, Child1);
        cout << "CHILD 1 is Running"<<endl;
    }
    else
    {
        pids[0] = getpid();
        pids[1] = pid;
        pid = fork();
        if (pid == 0)
        {
            signal(SIGUSR1, Child2);
            cout << "CHILD 2 is Running"<<endl;
        }
        else
        {
            pids[2] = pid;
            pid = fork();
            if (pid == 0)
            {
                signal(SIGUSR1, Child3);
                cout << "CHILD 3 is Running"<<endl;
            }
            else
            {
                pids[3] = pid;
                pid = fork();
                if (pid == 0)
                {
                    signal(SIGUSR1, Child4);
                    cout << "CHILD 4 is Running"<<endl;
                }
                else
                {
                    pids[4] = pid;
                    pid = fork();
                    if (pid == 0)
                    {
                        signal(SIGUSR1, Child5);
                        cout << "CHILD 5 is Running"<<endl;
                    }
                    else
                    {
                        sleep(2);
                        signal(SIGUSR1, Parent);
                        pids[5] = pid;
                        setpgid(pids[5], pids[5]);
                        setpgid(pids[4], pids[5]);
                        setpgid(pids[3], pids[5]);
                        setpgid(pids[2], pids[5]);
                        setpgid(pids[1], pids[5]);
                        
                        kill(getpid(),SIGUSR1);

                        killpg(getpgid(pids[5]), SIGUSR1);

                        for (int i = 0; i < 6; i++)
                        {
                            cout << "Group Id of Process " << i << " : " << getpgid(pids[i])<<endl;
                        }
                    }
                }
            }
        }
    }
}
