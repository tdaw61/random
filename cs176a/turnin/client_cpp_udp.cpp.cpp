/* UDP client in the internet domain */
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <iostream>
#include <string>
#include <sstream>

void error(const char *);
int main(int argc, char *argv[])
{
   int sock, n, portno;
   unsigned int length;
   struct sockaddr_in server, from;
   struct hostent *hp;
   char buffer[256];
   char input[100];
   
    printf("Enter server name or IP address: ");
    fgets(input, 100,stdin);
    hp = gethostbyname(input);
    bzero(input, 100);
    //get port number to connect to.
    printf("\nEnter port: ");
    scanf("%d", &portno);
    if((portno < 0) || (portno > 65535))
        printf("Invalid port number. Terminating. \n");
    
    //get equation for stuff
    printf("\nEnter expression: ");
    bzero(buffer,256);
    fgets(buffer,255,stdin);
   sock= socket(AF_INET, SOCK_DGRAM, 0);
   if (sock < 0) error("socket");

   server.sin_family = AF_INET;
   if (hp==0) error("Unknown host");

   bcopy((char *)hp->h_addr, 
        (char *)&server.sin_addr,
         hp->h_length);
   server.sin_port = htons(portno);
   length=sizeof(struct sockaddr_in);
   printf("Please enter the message: ");
   bzero(buffer,256);
   fgets(buffer,255,stdin);
   buffer.length();
   n=sendto(sock,buffer,
            strlen(buffer),0,(const struct sockaddr *)&server,length);
   if (n < 0) error("Sendto");
   n = recvfrom(sock,buffer,256,0,(struct sockaddr *)&from, &length);
   if (n < 0) error("recvfrom");
   write(1,"Got an ack: ",12);
   write(1,buffer,n);
   close(sock);
   return 0;
}

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

