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

#define MQ_NAME         "/myQueue"
#define MQ_QUEUE_SIZE        10
#define MQ_MSG_SIZE         1024

void *systemInit(void *ptr);
void *readSensorData(void *ptr);
void *logProcessCall(void *ptr);
void signalHandler(int sig);
static int dataToBuffer(char *ptr, int16_t x, int16_t y, int16_t z, int16_t temp);
static int getSensorData(int16_t *x, int16_t *y, int16_t *z, int8_t *temp, uint8_t *name);
static void waitToStart(void);

#endif /*__MAIN_H__*/