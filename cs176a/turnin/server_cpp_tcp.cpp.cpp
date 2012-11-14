
/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>

 struct protocol{
    int print;
    char ret[25];
} ;

void error(const char *msg)
{
    perror(msg);
    exit(0);
}


int sockfd, newsockfd, portno;
socklen_t clilen;
struct sockaddr_in serv_addr, cli_addr;
int n;
int width;
pthread_t keyboard; 
int m;
int k;
protocol buffer;
char equation[256];


int main(int argc, char *argv[]) {
          
     if (argc < 2) {
         fprintf(stderr,"ERROR, no port provided\n");
         exit(1);
         }
      	 sockfd = socket(AF_INET, SOCK_STREAM, 0);//set up a stream socket
    	 if (sockfd < 0)
     	   error("ERROR opening socket");
    	 bzero((char *) &serv_addr, sizeof(serv_addr));//set server address to 0
     	 portno = atoi(argv[1]);//get port number from stdin
    	 serv_addr.sin_family = AF_INET;
    	 serv_addr.sin_addr.s_addr = INADDR_ANY;
    	 serv_addr.sin_port = htons(portno);//host to network for port number
    	 if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)//bind call
              error("ERROR on binding");
	

         while(1)
         {
              listen(sockfd,5);//listen on socket
              clilen = sizeof(cli_addr);
              newsockfd = accept(sockfd,(struct sockaddr *) &cli_addr, &clilen);//accept call
              if (newsockfd < 0)
                    error("ERROR on accept");
              bzero(equation, 256);
              n = read(newsockfd, &equation, 256);//read in from socket
              bzero(equation, 256);
              strcpy(equation, "66");
              int ans = 5;
              k = write(newsockfd, &ans, sizeof(ans));
              for(int i = 1; i<=ans;i++)//loop that returns the absolute value to write.
              {
                  strcpy(buffer.ret, "Socket Programming");
                  if(i!=ans)
                        buffer.print = 1;
                  else
                      buffer.print = 0;
                  k = write(newsockfd, &buffer, sizeof(buffer));//writes back the socket programming line
                  if (k < 0)
                  {
                        error("ERROR writing to socket");
                        break;
                  }
              }
              close(newsockfd);//close client connection
          }          
        close(sockfd);//close socket
        return 0;
}





