#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<netinet/ip_icmp.h>
#include<netinet/udp.h>	
#include<netinet/tcp.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

char datagram[5000];


int main (void)
{
 int n;
  int s = socket (PF_INET, SOCK_RAW, IPPROTO_UDP);	
  struct ethhdr *eth = (struct ethhdr *) datagram;
  

  struct sockaddr_in sin,sin2; 
  socklen_t len = sizeof(sin2) ;
  memset(&sin,0,sizeof(sin)) ;
  sin.sin_family = AF_INET;
  inet_pton(AF_INET, "127.0.0.1", &sin.sin_addr);

  bind(s,(struct sockaddr *) &sin,sizeof(sin)) ;
  while(1)
  {
    n = recvfrom(s,datagram,4096,MSG_WAITALL,(struct sockaddr *) &sin,&len);
    printf("\nThe incoming ip address is = %s\n", inet_ntoa(sin.sin_addr));
	printf("\n\nEthernet header: ");
    printf("\n");
	printf("Ethernet Header\n");
	printf("   |-Destination Address : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_dest[0] , eth->h_dest[1] , eth->h_dest[2] , eth->h_dest[3] , eth->h_dest[4] , eth->h_dest[5] );
	printf("   |-Source Address      : %.2X-%.2X-%.2X-%.2X-%.2X-%.2X \n", eth->h_source[0] , eth->h_source[1] , eth->h_source[2] , eth->h_source[3] , eth->h_source[4] , eth->h_source[5] );
	printf("   |-Protocol            : %u \n",(unsigned short)eth->h_proto);
   
  }

}
