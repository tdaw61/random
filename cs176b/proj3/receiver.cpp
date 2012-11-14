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

#include <vector>

#define BUFFSIZE	1448
#define HEADER_LENGTH	22


using namespace std;
int main(int argc, char *argv[]) 
{
	int sock, packet_count;
	struct sockaddr_in echoserver;
	struct sockaddr_in echoclient;
	char buffer[BUFFSIZE + HEADER_LENGTH];
	unsigned int echolen, clientlen, serverlen;
	int received = 0;

	struct timeval now;
	double now_time;
	double last_time;
	double begin_time;
	double end_time;

	vector<int> packet_num;
        vector<bool> seqs;
        bool wad = true;

	if (argc != 2) 
	{
		fprintf(stderr, "USAGE: %s <port>\n", argv[0]);
		exit(1);
	}

	/*************Setup the UDP receive socket */
	if ((sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) exit(1);
	memset(&echoserver, 0, sizeof(echoserver));       /* Clear struct */
	echoserver.sin_family = AF_INET;                  /* Internet/IP */
	echoserver.sin_addr.s_addr = htonl(INADDR_ANY);   /* Any IP address */
	echoserver.sin_port = htons(atoi(argv[1]));       /* server port */
	serverlen = sizeof(echoserver);
	if (bind(sock, (struct sockaddr *) &echoserver, serverlen) < 0) exit(1);	/* Bind the socket */



	/*************Setup the UDP send socket******************/
	int sock_ack = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sock_ack < 0) perror("ERROR opening socket");
	struct	hostent *server;
	server = gethostbyname("localhost");
	if (server == NULL) exit(0);

	struct	sockaddr_in serv_addr;
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(atoi(argv[1])+1);

	fd_set rfds, wfds;
	struct timeval timeout;
	int retval;

	gettimeofday(&now, NULL);
	last_time = now.tv_sec + (now.tv_usec / 1000000.0);

typedef struct
{
	char data[1448];
	double deadline;
	double send_time;
	int sequence;
	int data_size;
} packet;

char tmp[1471];
char D[25];
char S[25];
char ack[HEADER_LENGTH];
char test[22];

int sent;
int ack_num;
	packet *my_packet;
	my_packet = (packet*) malloc (sizeof(packet) );
	memset(my_packet, 0, sizeof(*my_packet));

printf("x=[\n");
	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(sock, &rfds);

		timeout.tv_sec = 10;
		timeout.tv_usec = 0;

		select(sock + 1, &rfds, NULL, NULL, &timeout);
		if( FD_ISSET(sock, &rfds) )
		{
			bzero(buffer, sizeof(buffer));
			received = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *) &echoclient, &clientlen);
			strncpy(ack, buffer, HEADER_LENGTH); 	
	
			
			strncpy(D, buffer, 5); 
			D[5] = '\0';
			strncpy(S, &buffer[5], 15); 
			packet_num.push_back(atoi(D));
			printf("%f\n",  atof(S));

                        while(seqs.size() <= atoi(D))
                        {
                            printf("yup: %d %d \n", seqs.size(), atoi(D));
                            seqs.push_back(false);
                            if((seqs.size() - 1)== atoi(D))
                            {
                                seqs.at(atoi(D)) = true;
                                printf("pushing: %d %d", atoi(D), seqs.at(atoi(D)));
                            }
                        }
                        for(int i = 0; i < seqs.size(); i++)
                        {
                            if(seqs.at(i) == false)
                            {
                                wad = false;
                                ack_num = i;
                                break;
                            }
                            
                        }
                        int n;
                        if(wad)
                            ack_num = seqs.size();
                        printf("ack_num %d \n", ack_num);
                        //ack_num = 1;
                        bzero(ack,sizeof(ack));
          		n = sprintf (ack, "%5d%11.6f", ack_num, now_time);
			

//			bzero((char *) &tmp, sizeof(tmp));
//			strncpy(tmp, buffer, sizeof(buffer));
//			printf("%s\n", tmp);
			
			gettimeofday(&now, NULL);
			now_time = now.tv_sec + (now.tv_usec / 1000000.0);
//			printf("%f\n", now_time-last_time);
			last_time = now_time;
			packet_count++;

			/**** Return an ACK *********/
			sent = sendto(sock, ack, sizeof(ack), 0, (struct sockaddr *) &echoclient, sizeof(echoclient) );
//			printf("sent ACK: %s\n", ack );
		}
		else break;
	}

	printf("];\ny=[\n");
	for (int i=0; i<packet_num.size(); i++)
		printf("%d\n", packet_num[i]);
	printf("]\nplot(x, y);\n");

	gettimeofday(&now, NULL);
	double total_time = now.tv_sec + (now.tv_usec / 1000000.0) - begin_time;
	printf("\n\nbandwidth = %f\n", (packet_count * 1448)/total_time);

	close(sock);
	return 0; 
}
