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
#include <time.h>
#include <ctime>
#include <sys/time.h>
#include <fcntl.h>


#define BUFFSIZE 1448

int main(int argc, char *argv[]) 
{
	int sock, packet_count;
	struct sockaddr_in echoserver;
	struct sockaddr_in echoclient;
	char buffer[BUFFSIZE];
	unsigned int echolen, clientlen, serverlen;
	int received = 0;

	socklen_t clientserverlength;

	struct timeval now;
	double now_time;
	double last_time;
	double begin_time;
	double end_time;


        typedef struct
        {
	char data[BUFFSIZE];
	double deadline;
        } packet;
        
        packet* p = (packet*) malloc(sizeof(packet));
        memset(p, 0, sizeof(packet));
        
	/* Create the UDP socket */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) exit(1);
	/* Construct the server sockaddr_in structure */
	memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
	echoserver.sin_family = AF_INET;                  /* Internet/IP */
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address */
	echoserver.sin_port = htons(atoi(argv[1]));       /* server port */

	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) exit(1);	/* Bind the socket */
	clientserverlength = sizeof(struct sockaddr_in);


	fd_set rfds;
	struct timeval timeout;
	int retval;
                
        FD_ZERO(&rfds);
        FD_SET(sock, &rfds);    // adds socket descriptor sock to rfds .
        timeout.tv_usec = 0;
        timeout.tv_sec = 10;    // set timeout

	/*************Read from the socket here*****************/

        //get first packet
        recvfrom(sock, p, sizeof(packet), 0, (struct sockaddr *) &echoclient,&clientserverlength);
	gettimeofday(&now, NULL);
	last_time = now.tv_sec + (now.tv_usec / 1000000.0);
	begin_time = last_time;
        now_time = last_time;

        while(1)
        {
            if ( select(sock + 1, &rfds, NULL, NULL, &timeout) )
            {
                recvfrom(sock, p, sizeof(packet), 0, (struct sockaddr *) &echoclient,&clientserverlength);
                gettimeofday(&now, NULL);
                last_time = now_time;
                now_time = now.tv_sec + (now.tv_usec / 1000000.0);
                printf("\n%f", (now_time - last_time));
                packet_count++;
            }       
            else
            {
                printf("No data within timeout.\n");
                break;
            }
        }       
        gettimeofday(&now, NULL);
        double total_time = now.tv_sec + (now.tv_usec / 1000000.0) - begin_time;
        //printf("\n begin time = %f\n", begin_time);
        //printf("\n total_time = %f\n", total_time);
        //printf("\n now time = %f ", now.tv_sec + (now.tv_usec/ 1000000.0));
        //printf("\n packet count = %f", packet_count);
        printf("\n\nbandwidth = %f\n", (packet_count * 1448) / (total_time - 1));

	close(sock);
	return 0; 
}

