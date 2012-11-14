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

#define QUEUE_LENGTH		10
#define PACKET_DATA_LENGTH	1448

#define TRANSMISSION_TIME	0.00001448	//1448 byte packet at 100 Mbs

typedef struct {
    char data[PACKET_DATA_LENGTH];
    double deadline;
    double read_time;
    double rto_time;
    int sequence;
    int data_size;
} packet;

double delay = 0;
double loss = 0;
double jitter = 0;
double inter_packet_delay = 0;
double rto = 0.1;
FILE *pFile;
double deadline_time = 0;
int current_sequence_number = 0;


double get_deadline();
void get_packet(packet* my_packet, double now_time);

using namespace std;

int main(int argc, char **argv) {
    int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;
    unsigned int serverlen;

    char buffer[PACKET_DATA_LENGTH];
    char *file;
    char *host;
    int port;
    queue<packet> q;


    list<packet> rtx_queue;
    list<packet>::iterator p = rtx_queue.begin();


    /**********Command line args *******************/
    int c;
    opterr = 0;

    while ((c = getopt(argc, argv, "d:j:l:p:h:f:i:r:")) != -1)
        switch (c) {
            case 'd':
                delay = atof(optarg);
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
                rto = atof(optarg);
                break;
            default:
                abort();
        }


    //	printf("inter_packet_delay: %f\tjitter: %f\n", inter_packet_delay, jitter);
    assert(inter_packet_delay >= jitter);
    assert(inter_packet_delay >= TRANSMISSION_TIME);

    pFile = fopen(file, "rb");
    //	pFile = fopen ( "core.bin" , "rb" );

    /*************Fill Queue************/
    struct timeval now;
    double now_time;

    packet *my_packet;
    my_packet = (packet*) malloc(sizeof (packet));

    gettimeofday(&now, NULL);
    deadline_time = now.tv_sec + (now.tv_usec / 1000000.0);
    deadline_time = deadline_time + delay;

    memset(my_packet, 0, sizeof (*my_packet));
    get_packet(my_packet, deadline_time);
    if (my_packet->deadline != 0)
        q.push(*my_packet);


    for (int i = 0; i < QUEUE_LENGTH - 1; i++) {
        memset(my_packet, 0, sizeof (*my_packet));
        get_packet(my_packet, get_deadline());
        if (my_packet->deadline != 0)
            q.push(*my_packet);
    }

    /***************
    Print the Queue
     ****************
            char tmp[1449];
            while( !q.empty() )
            {
                    memset(my_packet, 0, sizeof(*my_packet));
     *my_packet = q.front();
                    q.pop();
                    bzero((char *) &tmp, sizeof(tmp));
                    strncpy(tmp, my_packet->data, 1448);
                    tmp[1449] = '\0';

                    printf("seq: %d\t %d bytes.\n", my_packet->sequence, my_packet->data_size);
                    printf("data: %s\n\n", tmp);
            }
    return 0;
     */

    /*************Set up socket******************/
    sockfd = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) perror("ERROR opening socket");
    server = gethostbyname(host);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof (serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(port);

    fd_set rfds;
    fd_set wfds;

    int received = 0;
    int num = 0;
    char seq[6];

    struct timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;
    int retval = 0;

    /************Write to socket*****************/
    while (1) {
        gettimeofday(&now, NULL);
        printf("%f\n %d\n", now.tv_sec + (now.tv_usec / 1000000.0), rtx_queue.size());
        FD_ZERO(&rfds);
        FD_SET(sockfd, &rfds);
        FD_ZERO(&wfds);
        FD_SET(sockfd, &wfds);
        retval = select(sockfd + 1, &rfds, &wfds, NULL, &timeout);
        if (retval == -1)
            perror("select()");
        p = rtx_queue.begin();
        
        if ((q.empty()) && (p->sequence == 0) && (rtx_queue.size() == 1)) {
            printf("done here\n");
            break;
        }

        if (FD_ISSET(sockfd, &rfds)) {

            /************* Receive ACK and get sequence number **********************/
            bzero(buffer, sizeof (buffer));
            received = recvfrom(sockfd, buffer, 5, 0, (struct sockaddr *) &serv_addr, &serverlen);
            //printf("received: %d \n", received);
            //printf("buffer: %s \n", buffer);
            strncpy(seq, buffer, 6);
            num = atoi(seq);
            //printf("seq: %d \n", num);

            p = rtx_queue.begin();
            p++;
            while (p != rtx_queue.end()) {
                //printf("p->sequence: %d sequence: %d \n", p->sequence, num);
                if (p->sequence == num) {
                    rtx_queue.erase(p);
                    break; // erase() mutates the list, so the iterator is now invalid
                }
                p++;
            }

        }
        /************* If rtx queue is not empty ************************/
        //if (FD_ISSET(sockfd, &wfds)) {
        if (!rtx_queue.empty()) {
            p = rtx_queue.begin();
            p++;
            while (p != rtx_queue.end()) {
                gettimeofday(&now, NULL);
                //printf("p rto: %f \n now time %f \n", p->rto_time, (now.tv_sec + (now.tv_usec / 1000000.0)));
                if (p->rto_time > (now.tv_sec + (now.tv_usec / 1000000.0))) {
                    my_packet->rto_time = p->rto_time;
                    my_packet->sequence = p->sequence;
                    my_packet->deadline = p->deadline;
                    goto fast_path;
                }
                p++;

                /****** Find the first packet in the rtx_queue that has RTO'd *************/
                /****** If you find one jump out of here to fast_path *********************/
                /****** You can do this any way you want, but, I used a goto ;^) **********/

            }
        }
        if (!q.empty()) {
            //if (FD_ISSET(sockfd, &wfds)) {

                memset(my_packet, 0, sizeof (*my_packet));
                *my_packet = q.front();
                q.pop();
                //printf("got here \n");
                fast_path:

                gettimeofday(&now, NULL);
                now_time = now.tv_sec + (now.tv_usec / 1000000.0);

                while (now_time < my_packet->deadline) {
                    gettimeofday(&now, NULL);
                    now_time = now.tv_sec + (now.tv_usec / 1000000.0);
                }
                my_packet->rto_time = now_time + rto;
                //printf("rto_time %f \n", my_packet->rto_time);
                bzero(buffer, 1448);
                sprintf(buffer, "%.5d %s", my_packet->sequence, my_packet->data);
                if ((double) rand() / RAND_MAX > loss) {
                    n = sendto(sockfd, buffer, PACKET_DATA_LENGTH, 0, (struct sockaddr *) &serv_addr, sizeof (serv_addr));
                    if (n < 0) perror("ERROR writing to socket");
                                    rtx_queue.push_back(*my_packet);

                }
                memset(my_packet, 0, sizeof (*my_packet));
                get_packet(my_packet, get_deadline());
                if (my_packet->deadline != 0)
                    q.push(*my_packet);
            }
        //}
    }
    fclose(pFile);
    close(sockfd);
}

double get_deadline() {
deadline_time += inter_packet_delay;	//Advance current time pointer
	return deadline_time + ( ( ( (double) rand()/RAND_MAX) * 2 * jitter) - jitter );
}

void get_packet(packet* my_packet, double deadline) {
    size_t result = fread(&my_packet->data, 1, PACKET_DATA_LENGTH, pFile);
    if (result) {
        my_packet->deadline = deadline;
        //		my_packet->read_time		= now_time;
        my_packet->sequence = current_sequence_number;
        //		my_packet->data_size		= result;
    }
    current_sequence_number++;
}
