#include <iostream>
#include <pthread.h>
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

const char *C1="C1";

void* writer(void* args)
{
  while(1)
  {
  
      struct iovec iov[1];
        ssize_t nr;
  
     string st;
     string s;
     cin>>s;
     st+=string(C1);
     st+=":";
     st+=s;
     int n=st.size();
     char char_array[100];
    strcpy(char_array, s.c_str());
     iov[0].iov_base=char_array;
     iov[0].iov_len=strlen(char_array)+1;
     
     int wfd = open("maine",O_WRONLY);
     write(wfd,iov,1);
     cout << "Message Delievered from Client 1:: " << char_array<<endl;
     close(wfd);
  }
}

int main()
{
	cout<<"Client started!!"<<endl;;
	mkfifo(C1,0666);



	pthread_t write_th,read_th;
	pthread_create(&write_th,NULL,writer,NULL);

	pthread_join(write_th,NULL);
}
