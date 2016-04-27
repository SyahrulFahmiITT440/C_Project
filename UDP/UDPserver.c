#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>

void error(char *msg)
{
 perror(msg);
 exit(0);
}

int main(int argc, char *argv[])
{
 int buffylen, sock, length, fromlen, n;
 struct sockaddr_in server;
 struct sockaddr_in from;
 char buf[1024], buffy[1024], name[10] = "Message: ";
 
 sock=socket(AF_INET, SOCK_DGRAM, 0);
 if(sock < 0)
 {
  error("Opening socket");
 }

 length = sizeof(server);
 bzero(&server,length);
 server.sin_family=AF_INET;
 /*I am using INADDR_ANY to set its IP to localhost*/
 server.sin_addr.s_addr=INADDR_ANY;
 server.sin_port=htons(1030);
 if (bind(sock,(struct sockaddr *)&server,length)<0)
 {
  error("binding");
 }
 fromlen = sizeof(struct sockaddr_in);
 
// while(1)
// {
  n = recvfrom(sock, buf, 1024, 0,(struct sockaddr 
*)&from,&fromlen);
  if(n<0)
  {
   error("recvfrom");
  }

  write(1,name, strlen(name));
  for(int i = 0; i < n; i++)
	buffy[i] = toupper(buf[i]);
  write(1,buf,n);
  write(1,"\n",1);
  n = sendto(sock,buffy,strlen(buffy),0,&from,fromlen);
  if(n<0)
  {
   error("sendto");
  }
// }
}
