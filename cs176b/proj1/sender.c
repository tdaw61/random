/*************
 * Compile: g++ -o sender sender.c
 * run: ./sender -h localhost -p 1234 -f sender.c -d .1 -l .01 -j 10
 * ************/
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

#define QUEUE_LENGTH		10
#define PACKET_DATA_LENGTH	1448

#define TRANSMISSION_TIME	0.00001448	//1448 byte packet at 100 Mbs

typedef struct
{
	char data[PACKET_DATA_LENGTH];
	double deadline;
} packet;

double	delay			= 0;
double	loss			= 0;
double	jitter			= 0;
double	inter_packet_delay	= 0;
FILE	*pFile;
double deadline_time		= 0;
struct timeval now;
double jit			= 0;
double now_time;
double deadtime;

void get_packet(packet* my_packet, double now_time);
double get_deadline();

using namespace std;
int main (int argc, char **argv)
{
	int sock, n;
        unsigned int length;
        struct sockaddr_in server, from;
        struct hostent *hp;
   

	char	buffer[PACKET_DATA_LENGTH];
	char	*file			;
	char	*host;
	int	port;
	queue<packet> q;

/**********Command line args *******************/
	int c;
	opterr = 0;

	while ((c = getopt (argc, argv, "d:j:l:p:h:f:i:")) != -1)
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
           		default:
				abort ();
		}

	assert(inter_packet_delay >= jitter);
	pFile = fopen ( file , "rb" );

	/*************First Packet******/
        packet* p = (packet*) malloc(sizeof(packet));
        memset(p, 0, sizeof(packet));
        gettimeofday(&now, NULL);
        deadline_time = now.tv_sec + (now.tv_usec / 1000000.0);
	deadline_time += delay + TRANSMISSION_TIME;
        get_packet(p, deadline_time);
        q.push(*p);
         
  	/*************Fill Queue************/
        for(int i = 0; i < QUEUE_LENGTH - 1; i++)
        {
            memset(p, 0, sizeof(packet));
            get_packet(p, get_deadline());
            if(p->deadline != 0)
                q.push(*p);
                    
        }
	/*************Set up socket******************/
       sock = socket(AF_INET, SOCK_DGRAM, 0);
       if (sock < 0) 
           printf("socket failure");

       server.sin_family = AF_INET;
       hp = gethostbyname(host);
       if (hp==0) 
           printf("Unknown host");
       bcopy((char *)hp->h_addr,(char *)&server.sin_addr,hp->h_length);
       server.sin_port = htons(port);
       length = sizeof(struct sockaddr_in); 
	/************Write to socket*****************/
   
	/*while(!(q.empty()))
	{
	  *p = q.front();
          printf("%d",q.size());
          gettimeofday(&now,NULL);
	  //if(p->deadline < (now.tv_sec + (now.tv_usec / 1000000.0))  && (!q.empty()))
	  {
	     n = sendto(sock, p, sizeof(packet), 0, (const struct sockaddr *) &server, length);
       	     if (n < 0)
               printf("ERROR writing to socket");
             q.pop();
             	  printf("deadline : %d \n",p->deadline);
	  gettimeofday(&now, NULL);
	  printf("time of day: %d \n",now.tv_sec + (now.tv_usec / 1000000.0));
 	     deadline_time = get_deadline();
	     get_packet(p,deadline_time);
	     if(p->deadline != 0)
		q.push(*p);
	  }      	   
	*/
       while(!(q.empty()))
       {
                memset(p, 0, sizeof(*p)); 
                *p = q.front();
                q.pop();
                gettimeofday(&now, NULL); 
                now_time = now.tv_sec + (now.tv_usec / 1000000.0);

                while(now_time < p->deadline)
                {
                    //printf("deadline : %d \n",p->deadline);
                    gettimeofday(&now, NULL);
                    now_time = now.tv_sec + (now.tv_usec / 1000000.0);
                    //printf("time of day: %d \n",now.tv_sec + (now.tv_usec / 1000000.0));

                }
                n = sendto(sock, p, sizeof(packet), 0, (const struct sockaddr *) &server, length);
                if (n < 0)
                        printf("ERROR writing to socket");
                get_packet(p, get_deadline());
                if(p->deadline != 0)
                    q.push(*p);
       }

        fclose (pFile);
        close(sock);
}

void get_packet(packet* my_packet, double deadline)
{
	size_t result = fread (&my_packet->data, 1, PACKET_DATA_LENGTH, pFile);
	if (result) 
		my_packet->deadline = deadline;
        else
            my_packet->deadline = 0;
}

double get_deadline()
{
	///jit = (rand() * 2 * jitter) - jitter;
        deadline_time = deadline_time + inter_packet_delay;
	//return deadline_time + jit;   
        return deadline_time + ( ( ( (double) rand()/RAND_MAX) * 2 * jitter) - jitter );

}
