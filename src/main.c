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

int16_t xAxis = 0;
int16_t yAxis = 0; 
int16_t zAxis = 0;

int main(void)
{
    /*thread declare*/
    pthread_t thrd_Create_File, thrd_Read_Data, thrd_Log_Data, thrd_Init;

    /*variables init*/
    uint8_t buf[1]={0};
    int8_t temp=0;

    /*function declare*/
    void *createFile(void *ptr);
    void *systemInit(void *ptr);
    void *readSensorData(void *ptr);
    
    //Handle thread
    pthread_create(&thrd_Create_File, NULL, createFile, NULL);
    pthread_create(&thrd_Init, NULL, systemInit, NULL);
    pthread_join(thrd_Create_File, NULL);
    pthread_join(thrd_Init, NULL);

    while(1)
    {
        usleep(100000);
        readTemperature(&temp);
        printf("device temperature: %d\n", temp);
        readDeviceName(buf);
        printf("device name: 0x%x\n", buf[0]);
        pthread_create(&thrd_Read_Data, NULL, readSensorData, NULL);
        pthread_join(thrd_Read_Data, NULL);       
    }
    return 0;    
}

void *createFile(void *ptr)
{
    FILE *fp;
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
    read_X_Axis(&xAxis);
    read_Y_Axis(&yAxis);
    read_Z_Axis(&zAxis);
    printf("X axis: %d |Y axis: %d|Z axis: %d\n",xAxis, yAxis, zAxis);
}