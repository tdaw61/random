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
#include <iostream>
#include <fstream>

#define READ_IN 1000

using namespace std;

typedef struct {
    unsigned char buffer[READ_IN];
    unsigned char last[READ_IN];
    int data_size;
    int loss;
    bool eof;
} packet;

FILE *pFile;
FILE *writeFile;
packet * my_packet;
int threshold;
char header[28];

void read_sample() {
    for(int i = 0; i < READ_IN;i++)
    {
        my_packet->last[i] = my_packet->buffer[i];
    }
    size_t result = fread(&my_packet->buffer, 1, READ_IN, pFile);
    
    if (!result)
        my_packet->eof = true;
}

void store_sample() {
    size_t result = fwrite(&my_packet->last, 1, READ_IN, writeFile);    
}

void write_empty()
{
    for(int i = 0; i < READ_IN; i++)
    {
        my_packet->buffer[i] = 0x30;
    }
    size_t result = fwrite(&my_packet->last, 1, READ_IN, writeFile);   
}

int calculate_loss_probability() {
    int value = rand() % 1000 ;
    return value;
}

int main() {

    my_packet = (packet*) malloc(sizeof (packet));
    my_packet->eof = false;
    pFile = fopen("doors.au", "rb");
    writeFile = fopen("changed.au", "w+");
    threshold = 400;
    size_t result = fread(header, 1, 28, pFile);
    result = fwrite(header, 1, 28, pFile);

    while (!(my_packet->eof)) {
        read_sample(); /* Read audio sample from a file */
        my_packet->loss = calculate_loss_probability();
        if (my_packet->loss < threshold) {
            store_sample(); /* Store the received sample */
        }
        else if(my_packet->loss >= threshold)
            write_empty();
    }
    return 0;
}
