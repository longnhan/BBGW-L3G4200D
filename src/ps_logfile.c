#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <pthread.h>
#include <mqueue.h>
#include <signal.h>

#define MQ_NAME         "/myQueue"
#define MQ_QUEUE_SIZE        10
#define MQ_MSG_SIZE         1024

/*message queue*/
mqd_t mq_gyro;
/*message queue notification*/
struct sigevent mqSignal;
/*mesage queue attributes*/
struct mq_attr mq_gyro_attr;

/*pointer log file*/
FILE *fp;
/*sensor raw data*/
int16_t xAxis = 0;
int16_t yAxis = 0; 
int16_t zAxis = 0;
/*sensor device name*/
uint8_t device_name = 0;
/*sensor temperature*/
int8_t temp=0;
/*data sensor to send queue*/
char mqSensorBuffer[MQ_MSG_SIZE]={0};

/*Function declaration*/
void *createFile(void *ptr);
void *logData(void *ptr);
void signalHandler(int sig);

int main()
{
    /*msg queue attributes*/
    mq_gyro_attr.mq_flags = 0;
    mq_gyro_attr.mq_maxmsg = MQ_QUEUE_SIZE;
    mq_gyro_attr.mq_msgsize = MQ_MSG_SIZE;
    mq_gyro_attr.mq_curmsgs = 0;

    /*message queue creating*/
    mq_gyro = mq_open(MQ_NAME, O_RDONLY, 0644, &mq_gyro_attr);
    if(mq_gyro == -1)
    {
        printf("msg queue create fail\n");
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("queue opened successfully\n");
    }

    /*setup message queue notification*/
    mqSignal.sigev_notify = SIGEV_SIGNAL;
    mqSignal.sigev_signo = SIGUSR1;

    if(mq_notify(mq_gyro, &mqSignal) == -1)
    {
        printf("msg queue notify SIGUSR1 create fail\n");
        perror("mq_notify");
        mq_close(mq_gyro);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("queue notify registered successfully\n");
    }

    /*register signal catching*/
    signal(SIGUSR1, signalHandler);
    signal(SIGINT, signalHandler);

    /*thread declare*/
    pthread_t thrd_Create_File, thrd_Log_Data;

    /*Handle threads*/
    pthread_create(&thrd_Create_File, NULL, createFile, NULL);
    pthread_join(thrd_Create_File, NULL);

    pthread_create(&thrd_Log_Data, NULL, logData, NULL);
    pthread_join(thrd_Log_Data, NULL);
    
    /* Close the message queue */
    mq_close(mq_gyro);
    mq_unlink(MQ_NAME);

    return 0;
}

void *createFile(void *ptr)
{
    fp = fopen("data_output.csv", "w+");
    if(fp == NULL)
    {
        printf("Create file fail\n");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Output file created\n");
    }   
    return NULL;
}

void *logData(void *ptr)
{   
    static uint8_t count  = 1;
    while(1)
    {
        if(count == 1)
        {
            fprintf(fp, "Log file read data from sensor L3G4200D\n");
            fprintf(fp, "Device name: 0x%x\n", device_name);
            fprintf(fp, "data x,data y,data z, temperature\n");
            count = 0;
        }
        
        printf("Waiting for messages...\n");
        pause();
    }
    mq_close(mq_gyro);
    mq_unlink(MQ_NAME);
    
    return NULL;
}

void signalHandler(int sig)
{
    printf("get signal for new message queue\n");
    if(sig == SIGUSR1)
    {
        /*read sensor data from queue*/
        if(mq_receive(mq_gyro, mqSensorBuffer, MQ_MSG_SIZE, NULL) == -1)
        {
            printf("queue reading error\n");
        }
        else
        {
            /*copy data from buffer to varibles*/
            memcpy(&xAxis, mqSensorBuffer, sizeof(int16_t));
            memcpy(&yAxis, mqSensorBuffer + 1*sizeof(int16_t), sizeof(int16_t));
            memcpy(&zAxis, mqSensorBuffer + 2*sizeof(int16_t), sizeof(int16_t));
            memcpy(&temp, mqSensorBuffer + 3*sizeof(int16_t), sizeof(int8_t));

            /*write data to log file*/
            fprintf(fp, "%d,%d,%d,%d\n", xAxis, yAxis, zAxis, temp);
            
            printf("receive buffer DONE\n");
            
            /*setup message queue notification*/
            mqSignal.sigev_notify = SIGEV_SIGNAL;
            mqSignal.sigev_signo = SIGUSR1;

            if(mq_notify(mq_gyro, &mqSignal) == -1)
            {
                printf("msg queue notify SIGUSR1 create fail\n");
                mq_close(mq_gyro);
                exit(EXIT_FAILURE);
            }
        }
    }
    else if(sig == SIGINT)
    {
        printf("\nCaught SIGINT, cleaning up...\n");
        mq_close(mq_gyro);
        mq_unlink(MQ_NAME);
        fclose(fp);
        exit(EXIT_SUCCESS);
    }
    
}