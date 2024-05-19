#include "main.h"
#include "l3g4.h"
#include "i2c_driver.h"

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


int main(void)
{
    /*thread declare*/
    pthread_t thrd_Read_Data, thrd_Init;

    /*function declare*/
    void *systemInit(void *ptr);
    void *readSensorData(void *ptr);
    
    /*Handle thread*/
    pthread_create(&thrd_Init, NULL, systemInit, NULL);
    pthread_join(thrd_Init, NULL);

    pthread_create(&thrd_Read_Data, NULL, readSensorData, NULL);
    pthread_join(thrd_Read_Data, NULL);
    
    return 0;    
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
