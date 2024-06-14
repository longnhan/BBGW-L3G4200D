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
#include <linux/limits.h>

#define MQ_NAME         "/myQueue"
#define MQ_QUEUE_SIZE        10
#define MQ_MSG_SIZE         1024


/*Function declaration*/
void processSetup(void);
void *createFile(void *ptr);
void *logData(void *ptr);
void signalHandler(int sig);

void messageQueue_Init(mqd_t *mqd_ptr, struct mq_attr *attr_ptr);
void messageQueue_Register_Notify(mqd_t mqd, struct sigevent *sig_ptr);

static int bufferToData(char *ptr, int16_t *x, int16_t *y, int16_t *z, int8_t *temp);
static void printDateTime(FILE *file);
static void curWorkingPath(char *fileNamePath);
#endif /*__LOGFILE_H__*/