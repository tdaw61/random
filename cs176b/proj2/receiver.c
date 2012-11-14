/*************
Compile: g++ -o receiver receiver.c
run: ./receiver.c
************/
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/time.h>

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <queue>
#include <assert.h>
#include <list>
#include <vector>


#define BUFFSIZE 1448

using namespace std;

int main(int argc, char *argv[]) 
{
	int sock;
        int packet_count = 0;
	struct sockaddr_in echoserver;
	struct sockaddr_in echoclient;
	char buffer[BUFFSIZE];
	unsigned int echolen, clientlen, serverlen;
	int received = 0;
        int seq = 0;
        int n = 0;
        char sbuff[5];

	struct timeval now;
	double now_time;
	double last_time;
	double begin_time;
	double end_time;
        //vector<int> seqs;
        //vector<int>::iterator p = seqs.begin();
        //list<double> times;
        //list<double>::iterator p = times.begin();


	if (argc != 2) 
	{
		fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
		exit(1);
	}

	/* Create the UDP socket */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) exit(1);
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
	echoserver.sin_family = AF_INET;                  /* Internet/IP */
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address */
	echoserver.sin_port = htons(atoi(argv[1]));       /* server port */

	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) exit(1);	/* Bind the socket */

	fd_set rfds;
        fd_set wfds;
	struct timeval timeout;
	int retval;

	gettimeofday(&now, NULL);
	last_time = now.tv_sec + (now.tv_usec / 1000000.0);
//	begin_time = last_time;

while(1)
{
	FD_ZERO(&rfds);
	FD_SET(sock, &rfds);
        //FD_ZERO(&wfds);
        //FD_SET(sock, &wfds);
	timeout.tv_sec = 5;
	timeout.tv_usec = 0;

	retval = 0;
	retval = select(sock + 1, &rfds, NULL, NULL, &timeout);
	if (retval == -1)
		perror("select()");
        if( FD_ISSET(sock, &rfds) )
	{

		bzero(buffer, 1448);
		received = recvfrom(sock, buffer, BUFFSIZE, 0, (struct sockaddr *) &echoclient, &clientlen);
                //printf("buffer: %s \n", buffer);
		gettimeofday(&now, NULL);
		now_time = now.tv_sec + (now.tv_usec / 1000000.0);
		printf(" %f\n", now_time);
                
                strncpy(sbuff, buffer, 5);
                //sbuff[5] = '\0';
                seq = atoi(sbuff);
                printf(" %d \n", seq);
                //seqs.pntush_back(seq);
		last_time = now_time;
		packet_count++;
        }		
	else
	{
            //p = seqs.begin();
            //int i = 0;
            /*while(p!=seqs.end())
            {
                printf("%d\n", seqs.at(i));
                p++;
                i++;
            }*/
		printf("timeout.\n");
                printf("packet count: %d \n", packet_count);
		break;
	}
        n = sendto(sock, sbuff, 6, 0, (struct sockaddr *) &echoclient, clientlen);
                        

}


	//printf("];\nplot(y);\n");
	gettimeofday(&now, NULL);
	double total_time = now.tv_sec + (now.tv_usec / 1000000.0) - begin_time;
	//printf("\n\nbandwidth = %f\n", (packet_count * 1448)/total_time);

	close(sock);
	return 0; 
}
