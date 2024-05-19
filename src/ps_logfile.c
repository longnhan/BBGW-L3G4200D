#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <pthread.h>

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

int main()
{
    /*thread declare*/
    pthread_t thrd_Create_File, thrd_Log_Data;

    /*function declare*/
    void *createFile(void *ptr);
    void *logData(void *ptr);

    /*Handle threads*/
    pthread_create(&thrd_Create_File, NULL, createFile, NULL);
    pthread_join(thrd_Create_File, NULL);

    pthread_create(&thrd_Log_Data, NULL, logData, NULL);
    pthread_join(thrd_Log_Data, NULL);
    
    return 0;
}

void *createFile(void *ptr)
{
    fp = fopen("data_output.csv", "w+");
    if(fp == NULL)
    {
        printf("Create file fail\n");
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
            fprintf(fp, "Read data from sensor L3G4200D\n");
            fprintf(fp, "Device name: 0x%x\n", device_name);
            fprintf(fp, "data x,data y,data z, temperature\n");
            count = 0;
        }
        fprintf(fp, "%d,%d,%d,%d\n", xAxis, yAxis, zAxis, temp);
        usleep(100000);
    }
    return NULL;
}