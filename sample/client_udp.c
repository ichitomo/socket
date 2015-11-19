/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>//sockaddr, msghdr, linger 
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[256];
   
   //
   if (argc != 3) { printf("Usage: server port\n");
                    exit(1);
   }
   //Create socket
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");//secketが作れていない

   server.sin_family = AF_INET;
   hp = gethostbyname(argv[1]);//ホスト名を取得
   if (hp==0) error("Unknown host");//ホスト名を取得できていないとき

   //バイト文字列をコピー
   bcopy((char *)hp->h_addr, //addresのhost名
        (char *)&server.sin_addr,//serverのアドレス
         hp->h_length);//ホスト名の長さ
   server.sin_port = htons(atoi(argv[2]));
   length=sizeof(struct sockaddr_in);
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   n=sendto(sock,buffer,
            strlen(buffer),0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");
   n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
   if (n < 0) error("recvfrom");
   write(1,"Got an ack: ",12);
   write(1,buffer,n);
   n = read(sock,buffer,255);
   write(1,buffer,n);
   close(sock);
   return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}
