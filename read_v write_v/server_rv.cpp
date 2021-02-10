#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <string.h>
using namespace std;

void* execute(void*)
{
       mkfifo("maine",0666);
	while(1)
	{
	struct iovec iov[1];
        ssize_t nr;
        char foo[100];
	  int fd = open("maine",O_RDONLY);
	  cout<<"Server is in Action"<<endl;
	  iov[0].iov_base=foo;
	  iov[0].iov_len=sizeof(foo);
	  nr=read(fd,iov,1);
	  if (nr == -1) {
                perror ("readv");
        }
	  cout<<"Read from Client by Serever "<<(char *)iov[0].iov_base<<endl;
	close(fd);
     }
}

int main()
{
  pthread_t t1;
  pthread_create(&t1,NULL,execute,NULL);
  pthread_join(t1,NULL);
  return 0;
}
