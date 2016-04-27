#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>

void error(char *msg)
{
 perror(msg);
 exit(0); 
}

int main(int argc, char *argv[])
{
 int sock, length, n;
 struct sockaddr_in server, from;
 struct hostent *hp;
 char buffer[1024];
 
 
 sock = socket(AF_INET, SOCK_DGRAM, 0);
 
 if(sock<0)
 {
  error("socket");
 }
 
 server.sin_family = AF_INET;
 
 hp = gethostbyname("localhost");

 if(hp==0)
 {
  error("Unknown Host");
 }

 bcopy((char *)hp->h_addr,(char *)&server.sin_addr,hp->h_length);
 
 
 server.sin_port = htons(1030);
 length = sizeof(struct sockaddr_in);
 
 printf("Please enter the message: ");
 
 bzero(buffer,1024);
 fgets(buffer,1023,stdin);
 n = sendto(sock,buffer,strlen(buffer), 0, &server, length);
 if(n<0)
 {
  error("Sendto");
 }
 
 n = recvfrom(sock,buffer,1024,0,&from,&length);
 if(n<0)
 {
  error("recvfrom");
 }
 write(1,"\nConverted: ",16);
 write(1,buffer,n);
}
