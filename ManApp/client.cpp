/*************
Compile: g++ -o sender sender.c
run: ./sender -h localhost -p 1234 -f sender.c -d .1 -l .01 -j 10
 ************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <queue>
#include <assert.h>
#include <list>

#include <vector>

using namespace std;

typedef struct yup {
    char * username;
    int points;
} user;

void error(const char *msg) {
    perror(msg);
    exit(0);
}

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
    int points;
    char * tempname;

    bool votebool;
    user dummy;
    dummy.points = 0;
    dummy.username = "Taylor";
    users.push_back(dummy);
    dummy.points = 2;
    dummy.username = "Camille";
    users.push_back(dummy);

    /**********Command line args *******************/
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "h:p:u:")) != -1)
        switch (c) {
            case 'p':
                port = atoi(optarg);
                break;
            case 'h':
                host = optarg;
                break;
            case 'u':
                user_name = optarg;
                break;
            default:
                printf("wrong stuff");
                abort();
        }

    int sock, n;
    unsigned int length;
    struct sockaddr_in server, from;
    struct hostent *hp;
    char buffer[256];

    //set up socket
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) error("socket");

    server.sin_family = AF_INET;
    hp = gethostbyname(host);
    if (hp == 0) error("Unknown host");

    bcopy((char *) hp->h_addr, (char *) &server.sin_addr, hp->h_length);
    server.sin_port = htons(port);
    length = sizeof (struct sockaddr_in);

    struct timeval timeout;
    fd_set rfds;
    fd_set wfds;
    int retval;
    unsigned int clientlen;
    packet sending;
    string in;


    /************Write to socket*****************/
    while (1) {

        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_SET(sock, &rfds);
        FD_SET(sock, &wfds);
        timeout.tv_sec = 5;
        timeout.tv_usec = 0;
        retval = 0;
        retval = select(sock + 1, &rfds, &wfds, NULL, &timeout);
        if (retval == 0) break;


        if (FD_ISSET(sock, &rfds))
        {
        //receiving 
        bzero(buffer, 256);
        n = recvfrom(sock, buffer, 256, 0, (struct sockaddr *) &from, &length);
        if (n < 0) error("recvfrom");
        }
        strcpy(sending.name, "taylor");
        //packet buffer;
        printf("Who is the target?");
        //cin >> tempname;
        //gets(tempname);
        //getline(cin, in);
        //scanf("%s", tempname);
        bzero(sending.u.change.targetName, sizeof (sending.u.change.targetName));
        //memcpy(sending.u.change.targetName, in, sizeof(in));
        strcpy(sending.u.change.targetName, tempname);
        cout << sending.u.change.targetName;
        cout << "how many points to change: " << endl;
        cin >> points;
        //getline(cin,in);
        //scanf("%d", points);
        //points = atoi(in);
        //points = 1;
        sending.u.change.point = points;
        //sending
        n = sendto(sock, &sending, sizeof (packet), 0, (const struct sockaddr *) &server, length);
        if (n < 0) error("Sendto");
    }
        close(sock);
        return 0;

}


/*  strcpy(user_name, sending.name);

  //sending loop
  while (1) {


      //get packet in
      //n = recvfrom(sockfd, &buffer, sizeof (buffer), 0, (struct sockaddr *) &serv_addr, clientlen);


      printf("Who is the target?");
      //cin >> sending.u->change->targetName;
      cin >> tempname;
      bzero(sending.u.change.targetName, sizeof (sending.u.change.targetName));
      strcpy(sending.u.change.targetName, tempname);
      cout << sending.u.change.targetName;
      cout << "how many points to change: " << endl;
      cin >> sending.u.change.point;
      //votebool = true;

      //if i got a packet that wants to change the points, then set the bool to true and send out a vote request.
      if (votebool) {
          //send vote out
          cout << "should this user get points (y/n) " << sending.u.change.targetName;
      }
      n = sendto(sockfd, &sending, sizeof (sending), 0, (struct sockaddr *) &serv_addr, sizeof (serv_addr));

  }*/
//}




