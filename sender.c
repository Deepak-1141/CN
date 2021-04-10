#include<netinet/in.h>
#include<errno.h>
#include<netdb.h>
#include<stdio.h>
#include<stdlib.h>	
#include<string.h>	
#include<netinet/ip_icmp.h>	
#include<netinet/udp.h>	
#include<netinet/tcp.h>	
#include<netinet/ip.h>	
#include<netinet/if_ether.h>	
#include<net/ethernet.h>	//For ether_header
#include<sys/socket.h>
#include<arpa/inet.h>
#include<sys/ioctl.h>
#include<sys/time.h>
#include<sys/types.h>
#include<unistd.h>

int main (int argc, char* argv[]){

    int s = socket (AF_INET, SOCK_RAW, IPPROTO_UDP);
    char datagram[4096];	

    struct ethhdr *eth = (struct ethhdr *) datagram;
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr ("127.0.0.2");
    memset(&datagram,0,4096);
     sendto(s, datagram, 4096,MSG_CONFIRM,(struct sockaddr *) &sin,	sizeof (sin)); 

    return 0;
}
