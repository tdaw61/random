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

#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <queue>
#include <assert.h>
#include <list>

#include <vector>


#define QUEUE_LENGTH		10
#define PACKET_DATA_LENGTH	1448
#define PACKET_HEADER_LENGTH	22

#define PACKET_LENGTH		1486


#define TRANSMISSION_TIME	0.00001448	//1448 byte packet at 100 Mbs

typedef struct
{
	char data[PACKET_DATA_LENGTH];
	double deadline;
	double send_time;
	double rto_time;
	int sequence;
	int data_size;
} packet;

double	delay			= 0;
double	loss			= 0;
double	jitter			= 0;
double	inter_packet_delay	= 0;
FILE	*pFile;
double deadline_time		= 0;
int current_sequence_number	= 0;
double	rto			= 0.1;

double get_deadline();
void get_packet(packet* my_packet, double now_time);

using namespace std;
int main (int argc, char **argv)
{
	int	sockfd, n;	// Delete this
	struct	sockaddr_in serv_addr;
	struct	hostent *server;

	char	buffer[PACKET_DATA_LENGTH+PACKET_HEADER_LENGTH];
	char	tmp[PACKET_DATA_LENGTH+PACKET_HEADER_LENGTH + 1];
	char	*file;
	char	*host;
	int	port;
	queue<packet> q;

	list<packet> rtx_queue;
	list<packet>::iterator p = rtx_queue.begin();


/**********Command line args *******************/
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "h:p:d:j:l:i:r:f:")) != -1)
		switch (c)
		{
			case 'd':
				delay = atof (optarg);
				break;
			case 'j':
				jitter = atof(optarg);
				break;
			case 'l':
				loss = atof(optarg);
				break;
			case 'p':
				port = atoi(optarg);
				break;
			case 'h':
				host = optarg;
				break;
			case 'f':
				file = optarg;
				break;
			case 'i':
				inter_packet_delay = atof(optarg);
				break;
			case 'r':
                                rto = 0;
				break;
           		default:
				abort ();
		}

	assert(inter_packet_delay >= jitter);
	assert(inter_packet_delay >= TRANSMISSION_TIME);

	pFile = fopen ( file , "rb" );

	/*************Fill Queue************/
	struct timeval now;
	double now_time;
        double start_time;

	packet *my_packet;
	my_packet = (packet*) malloc (sizeof(packet) );

	gettimeofday(&now, NULL);
	deadline_time = now.tv_sec + (now.tv_usec / 1000000.0);
	deadline_time = deadline_time + delay;

	memset(my_packet, 0, sizeof(*my_packet));
	get_packet	(my_packet, 
			deadline_time);
	if (my_packet->deadline != 0) q.push(*my_packet);

	for(int i = 0; i < QUEUE_LENGTH - 1; i++)
	{
		memset(my_packet, 0, sizeof(*my_packet));
		get_packet	(my_packet, get_deadline());
		if (my_packet->deadline != 0) q.push(*my_packet);
	}


/*************Setup the UDP send socket******************/
	sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
	if (sockfd < 0) perror("ERROR opening socket");
	server = gethostbyname(host);
	if (server == NULL) exit(0);

	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy( (char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);


	struct timeval timeout;
	fd_set rfds;
	fd_set wfds;
	int retval;
	unsigned int clientlen;

char tbuffer[PACKET_LENGTH];
char D[25];
char S[25];

	/************Write to socket*****************/
int count = 10;
gettimeofday(&now, NULL);
start_time = now.tv_sec;
	while(1)
	{
            count--;
printf("Round %d\tqueue: %d\trtx_queue:%d\n", current_sequence_number, q.size(), rtx_queue.size());

	
		FD_ZERO(&rfds);
		FD_ZERO(&wfds);
		FD_SET(sockfd, &rfds);
		FD_SET(sockfd, &wfds);
		timeout.tv_sec = 5;
		timeout.tv_usec = 0;
		retval = 0;
		retval = select(sockfd + 1, &rfds, &wfds, NULL, &timeout);
		if(retval == 0) break;
		if ( q.empty() && rtx_queue.empty() )
                {
                    printf("queues empty, exiting");
                    exit(0);
                }

		if( FD_ISSET(sockfd, &rfds) )
			{
printf("Recieving socket ready.\n");

				bzero(tbuffer, sizeof(tbuffer));
				memset(my_packet, 0, sizeof(*my_packet));

				clientlen = sizeof(serv_addr);
				n = 0;
				n = recvfrom(sockfd, tbuffer, sizeof(tbuffer), 0, (struct sockaddr *) &serv_addr, &clientlen);

				bzero((char *) &D, sizeof(D));
				bzero((char *) &S, sizeof(S));
				
				strncpy(D, tbuffer, 5); 
				D[5] = '\0';
				strncpy(S, &tbuffer[5], 15); 
				printf("Received packet: %d at %f\n", atoi(D),  atof(S));
                                //if(rtx_queue.size() > 0)
                                //{
                                    p = rtx_queue.begin();
                                    //p++;
                                //}
				/******** Remove packet from rtx_queue ***********/
				//p = rtx_queue.begin();
				while(p != rtx_queue.end())
				{
					if ( p->sequence == atoi(D) - 1)
					{
printf("Removed packet: %d from rtx_queue.\n", p->sequence);
//if(p->sequence == 11)
	//NULL;
						rtx_queue.erase( p );
						break;
					}
					p++;
				}
			}

		if( !rtx_queue.empty() )
			{
                    
	/********* Are there any RTO'd packets? ***************/
				memset(my_packet, 0, sizeof(*my_packet));
				gettimeofday(&now, NULL);
				now_time = now.tv_sec + (now.tv_usec / 1000000.0);

				p = rtx_queue.begin();
				while(p != rtx_queue.end())
				{
					if ( p->rto_time < now_time )
					{
						*my_packet = *p;
//						q.push(*my_packet);
						rtx_queue.erase(p);
printf("Took packet %d RTO'd packet out of the rtx_queue.\n", p->sequence);
						goto fast_path;
					}
					p++;
				}
			}
	if (!q.empty() )
		{	
			if (q.empty() ) continue;
			*my_packet = q.front();
			q.pop();

			fast_path:			
			gettimeofday(&now, NULL);
			now_time = now.tv_sec + (now.tv_usec / 1000000.0);



			while(now_time<my_packet->deadline)
			{
				gettimeofday(&now, NULL);
				now_time = now.tv_sec + (now.tv_usec / 1000000.0);
			}
			my_packet->rto_time = now_time + rto;
			if ( (double) rand()/RAND_MAX > loss)
			{
				my_packet->send_time = now_time;
				
				n=sprintf (tbuffer, "%5d%11.6f%s", my_packet->sequence, my_packet->send_time, my_packet->data);
				n = sendto(sockfd, tbuffer, sizeof(tbuffer), 0, (struct sockaddr *) &serv_addr, sizeof(serv_addr) );

				strncpy(D, tbuffer, 5); 
				D[5] = '\0';
				strncpy(S, &tbuffer[5], 15); 
				printf("Sent packet: %d at %f\n", atoi(D),  atof(S));
			}
			else
				printf("lost packet: %d\n", my_packet->sequence);

			rtx_queue.push_back(*my_packet);
printf("pushed packet: %d onto rtx_queue.\n", my_packet->sequence);
gettimeofday(&now,NULL);
if(now.tv_sec - start_time <= 10)
{
			memset(my_packet, 0, sizeof(*my_packet));
			get_packet	(my_packet, get_deadline());
			if (my_packet->deadline != 0) 
			{
				q.push(*my_packet);
printf("pushed packet: %d onto queue.\n", my_packet->sequence);
			}
		}
        }



/****** Print rtx_queue (debugging) ************/
printf("Contents of rtx_queue:\t");
p = rtx_queue.begin();
while(p != rtx_queue.end())
{
	printf("packet: %d\t", p->sequence);
	p++;
}
printf("\n\n");




	}

	fclose (pFile);
	close(sockfd);
}

double get_deadline()
{
	deadline_time += inter_packet_delay + TRANSMISSION_TIME;	//Advance current time pointer
	double jit = ( ( ( (double) rand()/RAND_MAX) * 2 * jitter) - jitter );
//	printf("jit: %f\n", jit);
	return deadline_time + jit;
}

void get_packet(packet* my_packet, double deadline)
{
	//size_t result = fread (&my_packet->data, 1, PACKET_DATA_LENGTH, pFile);
    memset(&my_packet->data, 'x', 1448);
	//if (result) 
	//{
		my_packet->deadline		= deadline;
//		my_packet->read_time		= now_time;
		my_packet->send_time		= deadline;
		my_packet->sequence		= current_sequence_number;
//		my_packet->data_size		= result;
	//}
	current_sequence_number++;
}

