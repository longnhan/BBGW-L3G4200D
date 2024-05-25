#ifndef __LOGFILE_H__
#define __LOGFILE_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <pthread.h>
#include <mqueue.h>
#include <signal.h>
#include <time.h>

#define MQ_NAME         "/myQueue"
#define MQ_QUEUE_SIZE        10
#define MQ_MSG_SIZE         1024

#define LOGFILE_NAME    "data_output.csv"

/*Function declaration*/
void *createFile(void *ptr);
void *logData(void *ptr);
void signalHandler(int sig);
static int bufferToData(char *ptr, int16_t *x, int16_t *y, int16_t *z, int8_t *temp);
static void printDateTime(FILE *file);

#endif /*__LOGFILE_H__*/