/* 
 * File:   keyboard.h
 * Author: Taylor
 *
 * Created on October 10, 2011, 8:15 PM
 */

typedef struct myprotocol{
	unsigned int deviceID;
	unsigned int eventID;
	int timer;
	union {
		struct {
			int xchange;
			int ychange;
			} coord;
		struct {
			int len;
			char string[8000];
			} search;
		struct {
			char log[30];
			char pass[30];
			} user;
		} u;
	}protocol;


typedef struct thing {
        char result[100];
        int priority;
        struct node * next;
} node;

void strip_newline();
void append();
void error(const char *);
void *runscreen();
void *packetloop();


