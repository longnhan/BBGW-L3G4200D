#include "main.h"
#include "l3g4.h"
#include "i2c_driver.h"

/*function declare*/
void *systemInit(void *ptr);
void *readSensorData(void *ptr);
void signalHandler(int sig);

/*system i2c config*/
int i2c_File;
char i2c_Device[]="/dev/i2c-2";
uint8_t device_Address = 0x69;
enum deviceOperationMode device_Mode = Device_Mode_Normal;

/*message queue*/
mqd_t mq_gyro;

/*sensor raw data*/
int16_t xAxis = 0;
int16_t yAxis = 0; 
int16_t zAxis = 0;
/*sensor device name*/
uint8_t device_name = 0;
/*sensor temperature*/
int8_t temp=0;
/*data sensor to send queue*/
int16_t mqSensorBuffer[5]={0};

int main(void)
{
    printf("start opening msg queue\n");
    /*msg queue attributes*/
    struct mq_attr mq_gyro_attr;
    mq_gyro_attr.mq_flags = 0;
    mq_gyro_attr.mq_maxmsg = MQ_QUEUE_SIZE;
    mq_gyro_attr.mq_msgsize = MQ_MSG_SIZE;
    mq_gyro_attr.mq_curmsgs = 0;
    
    /*open message queue*/
    mq_gyro = mq_open(MQ_NAME, O_CREAT | O_WRONLY | O_NONBLOCK, 0644, &mq_gyro_attr);
    if(mq_gyro == -1)
    {
        printf("msg queue create fail\n");
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("queue created successfully\n");
    }
    
    /*signal catching*/
    signal(SIGINT, signalHandler);

    /*thread declare*/
    pthread_t thrd_Read_Data, thrd_Init;
    
    /*Handle thread*/
    pthread_create(&thrd_Init, NULL, systemInit, NULL);
    pthread_join(thrd_Init, NULL);

    pthread_create(&thrd_Read_Data, NULL, readSensorData, NULL);
    pthread_join(thrd_Read_Data, NULL);
    
    /* Close the message queue */
    mq_close(mq_gyro);
    mq_unlink(MQ_NAME);

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

        mqSensorBuffer[0] = xAxis;
        mqSensorBuffer[1] = yAxis;
        mqSensorBuffer[2] = zAxis;
        mqSensorBuffer[3] = temp;
        mqSensorBuffer[4] = device_name;

        /*sending buffer to queue*/
        if(mq_send(mq_gyro, (char *)mqSensorBuffer, strlen(mqSensorBuffer), 0) == -1)
        {
            printf("queue sending error\n");
            perror("mq_send");
        }
        else
        {
            printf("queue sending successfully\n");
        }

        usleep(10000);
    }
    return NULL;
}

void signalHandler(int sig)
{
    if(sig == SIGINT)
    {
        printf("\nCaught SIGINT, cleaning up...\n");
        mq_close(mq_gyro);
        mq_unlink(MQ_NAME);
        exit(EXIT_SUCCESS);
    }
    else
    {
        
    }
}