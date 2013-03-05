#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <ctype.h>

char buffReader();
void execComm(char comm[]);
void displayText(char line[]);
void bufferWriter(char data[]);



void *controller(void * args);
void *devDriver(void * args);
