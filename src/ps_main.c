#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "main.h"
#include <pthread.h>

/*system i2c config*/
int i2c_File;
char i2c_Device[]="/dev/i2c-2";
uint8_t device_Address = 0x69;
enum deviceOperationMode device_Mode = Device_Mode_Normal;

/*sensor raw data*/
int16_t xAxis = 0;
int16_t yAxis = 0; 
int16_t zAxis = 0;
/*sensor device name*/
uint8_t device_name = 0;
/*sensor temperature*/
int8_t temp=0;

/*pointer log file*/
FILE *fp;

int main(void)
{
    /*thread declare*/
    pthread_t thrd_Create_File, thrd_Read_Data, thrd_Log_Data, thrd_Init;

    /*function declare*/
    void *createFile(void *ptr);
    void *systemInit(void *ptr);
    void *readSensorData(void *ptr);
    void *logData(void *ptr);
    
    //Handle thread
    pthread_create(&thrd_Create_File, NULL, createFile, NULL);
    pthread_create(&thrd_Init, NULL, systemInit, NULL);
    pthread_join(thrd_Create_File, NULL);
    pthread_join(thrd_Init, NULL);

    pthread_create(&thrd_Read_Data, NULL, readSensorData, NULL);
    pthread_create(&thrd_Log_Data, NULL, logData, NULL);
    pthread_join(thrd_Read_Data, NULL);
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

void *systemInit(void *ptr)
{
    uint8_t ret_i2c = 1;
    while (ret_i2c == 1)
    {
        ret_i2c = i2cInit();
    }
    
    setDeviceMode(device_Mode);
    return NULL;
}

void *readSensorData(void *ptr)
{
    while (1)
    {
        read_X_Axis(&xAxis);
        read_Y_Axis(&yAxis);
        read_Z_Axis(&zAxis);
        readTemperature(&temp);
        readDeviceName(&device_name);
        
        printf("device temperature: %d\n", temp);
        printf("device name: 0x%x\n", device_name);
        printf("X axis: %d |Y axis: %d|Z axis: %d\n",xAxis, yAxis, zAxis);

        usleep(100000);
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