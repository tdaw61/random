/*************
Compile: g++ -o receiver receiver.c
run: ./receiver.c
 ************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <fcntl.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <vector>

using namespace std;

void error(const char *msg) {
    perror(msg);
    exit(0);
}

typedef struct yup {
    char * username;
    int points;
} user;

typedef struct myprotocol {
    char name[30];
    unsigned int action;
    //int timer;

    union {

        struct {
            bool yes_no;
        } vote;

        struct {
            int point;
            char targetName[30];
        } change;
    } u;
} packet;

vector<user> users;

int main(int argc, char **argv) {

    char *host;
    char *user_name;
    int port;
    int received;
    //int sock, packet_count;
    struct sockaddr_in echoserver;
    struct sockaddr_in echoclient;
    unsigned int echolen, serverlen;
    socklen_t * clientlen;

    packet buffer;

    bool votebool;
    user dummy;
    dummy.points = 0;
    dummy.username = "Taylor";
    users.push_back(dummy);
    dummy.points = 2;
    dummy.username = "Camille";
    users.push_back(dummy);

    if (argc != 2) {
        fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
        exit(1);
    }

    int sock, length, n;
    socklen_t fromlen;
    struct sockaddr_in server;
    struct sockaddr_in from;
    char buf[1024];

    if (argc < 2) {
        fprintf(stderr, "ERROR, no port provided\n");
        exit(0);
    }
    //SOCKET SETUP
    
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("Opening socket");
    length = sizeof (server);
    bzero(&server, length);
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(atoi(argv[1]));
    if (bind(sock, (struct sockaddr *) &server, length) < 0)
        error("binding");
    fromlen = sizeof (struct sockaddr_in);
    
    
    
    //LOOP SETUP
    struct timeval timeout;
    fd_set rfds;
    while (1) {
        FD_ZERO(&rfds);
        FD_SET(sock, &rfds);

        timeout.tv_sec = 1;
        timeout.tv_usec = 0;

        select(sock + 1, &rfds, NULL, NULL, &timeout);
        if (FD_ISSET(sock, &rfds)) {
            bzero(buffer.u.change.targetName, sizeof (buffer.u.change.targetName));
            n = recvfrom(sock, &buffer, sizeof (buffer), 0, (struct sockaddr *) &from, &fromlen);
            if (n < 0) error("recvfrom");
            //write(1,"Received a datagram: ",21);
            //write(1,buffer.u.change.point , sizeof(buffer.u.change.point));
            printf("points: %d \n", buffer.u.change.point);
            printf("target: %s \n", buffer.u.change.targetName);
            n = sendto(sock, "Got your message\n", 17,
                    0, (struct sockaddr *) &from, fromlen);
            if (n < 0) error("sendto");
        }
    }
    return 0;
}
