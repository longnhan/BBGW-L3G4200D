#ifndef __MAIN_H__
#define __MAIN_H__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <pthread.h>
#include <mqueue.h>
#include <signal.h>
#include <semaphore.h>
#include <linux/limits.h>

#define MQ_NAME             "/myQueue"
#define SEM_MQ_NAME         "/semaphore_Msg_Queue"
#define SEM_NUMBER          1
#define MQ_QUEUE_SIZE       10
#define MQ_MSG_SIZE         1024

#define AUTO_START_PROCESS

void *systemInit(void *ptr);
void *readSensorData(void *ptr);
void *logProcessCall(void *ptr);
void signalHandler(int sig);

static int semaphore_Init(char *sem_Name, sem_t **sem_d);
static void semaphore_Close(const char *sem_Name, sem_t *sem_d);

void messageQueue_Init(mqd_t *mqd_ptr, struct mq_attr *attr_ptr);
void messageQueue_Close(const char *mq_Name, mqd_t mq_d);

static int dataToBuffer(char *ptr, int16_t x, int16_t y, int16_t z, int16_t temp);
static int getSensorData(int16_t *x, int16_t *y, int16_t *z, int8_t *temp, uint8_t *name);
static void waitToStart(void);
static void curWorkingPath(char *fileNamePath);

#endif /*__MAIN_H__*/