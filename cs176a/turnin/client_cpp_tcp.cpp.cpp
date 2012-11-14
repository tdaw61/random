#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

 struct protocol{
    int print;
    char ret[25];
};

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    char input[100];
    char buffer[256];
    protocol stuff;
    
    //get server name
    printf("Enter server name or IP address: ");
    cin.getline(input, 100);
    server = gethostbyname(input);
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

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
        error("ERROR opening socket");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    //setting up server settings
    bcopy((char *)server->h_addr,(char *)&serv_addr.sin_addr.s_addr, server->h_length);
    ///converting port number;
    serv_addr.sin_port = htons(portno);
    //connecting to server
    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) 
        error("ERROR connecting");
    //printf("Please enter the message: ");
    n = write(sockfd,buffer,strlen(buffer));
    if (n < 0) 
         error("ERROR writing to socket");
    bzero(buffer,256);
    int ans;
    n = read(sockfd,&ans,sizeof(ans));
    if (n < 0) 
         error("ERROR reading from socket");
    printf("%d\n",ans);
    stuff.print = 1;
    while(stuff.print == 1)
    {
        n = read(sockfd, &stuff, sizeof(stuff));
        if (n < 0) 
         error("ERROR reading from socket");
        printf("Socket Programming \n");
        if(stuff.print == 0)
            break;
    }
    
    
    close(sockfd);
    return 0;
}

