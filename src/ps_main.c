#include "main.h"
#include "l3g4.h"
#include "i2c_driver.h"

/*system i2c config*/
int i2c_File;
char i2c_Device[]="/dev/i2c-2";
uint8_t device_Address = 0x69;
enum deviceOperationMode device_Mode = Device_Mode_Normal;

/*message queue*/
mqd_t mq_gyro;
/*msg queue attributes*/
struct mq_attr mq_gyro_attr;

/*sensor raw data*/
int16_t xAxis = 0;
int16_t yAxis = 0; 
int16_t zAxis = 0;
/*sensor device name*/
uint8_t device_name = 0;
/*sensor temperature*/
int8_t temp=0;
/*data sensor to send queue*/
char mqSensorBuffer[MQ_MSG_SIZE]={};
char str_test[MQ_MSG_SIZE] = {};

int main(void)
{
    waitToStart();
    
    printf("start opening msg queue\n");
    /*msg queue attributes*/
    mq_gyro_attr.mq_flags = 0;
    mq_gyro_attr.mq_maxmsg = MQ_QUEUE_SIZE;
    mq_gyro_attr.mq_msgsize = MQ_MSG_SIZE;
    mq_gyro_attr.mq_curmsgs = 0;
    
    /*open message queue*/
    mq_gyro = mq_open(MQ_NAME, O_CREAT | O_WRONLY, 0644, &mq_gyro_attr);
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

    usleep(100000);

    /*thread declare*/
    pthread_t thrd_Read_Data, thrd_Init, thrd_Call_App;
    
    /*Handle thread*/
    pthread_create(&thrd_Init, NULL, systemInit, NULL);
    pthread_join(thrd_Init, NULL);

    pthread_create(&thrd_Call_App, NULL, logProcessCall, NULL);
    
    usleep(100000);
    
    pthread_create(&thrd_Read_Data, NULL, readSensorData, NULL);
    pthread_join(thrd_Call_App, NULL);
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
        /*get data from sensor*/
        read_X_Axis(&xAxis);
        read_Y_Axis(&yAxis);
        read_Z_Axis(&zAxis);
        readTemperature(&temp);
        readDeviceName(&device_name);
        
        /*print out the sensor's data*/
        printf("\n|-----------------------------------------------------|\n");
        printf("device temperature: %d\n", temp);
        printf("device name: 0x%x\n", device_name);
        printf("X axis: %d |Y axis: %d|Z axis: %d\n",xAxis, yAxis, zAxis);

        /*copy sensor value to buffer*/
        dataToBuffer(mqSensorBuffer, xAxis, yAxis, zAxis, temp);

        /*sending buffer to queue*/
        if(mq_send(mq_gyro, mqSensorBuffer, MQ_MSG_SIZE, 0) == -1)
        {
            printf("queue sending error\n");
            perror("mq_send");
        }
        else
        {
            printf("queue sending successfully\n");
            /*print out the number message*/
            mq_getattr(mq_gyro, &mq_gyro_attr);
            printf("current messgae in queue: %d\n", mq_gyro_attr.mq_curmsgs);
        }

        usleep(100000);
    }
    mq_close(mq_gyro);
    mq_unlink(MQ_NAME);

    return NULL;
}

void *logProcessCall(void *ptr)
{
    pid_t pid = fork();
    if (pid == 0) 
    {
        // Child process
        execlp("./l3g4_prj_logfile", "./l3g4_prj_logfile", NULL);
        perror("execlp");
        exit(EXIT_FAILURE);
    } 
    else if (pid < 0) 
    {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // Parent process continues
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

static int dataToBuffer(char *ptr, int16_t x, int16_t y, int16_t z, int16_t temp)
{
    if(ptr == NULL)
    {
        fprintf(stderr, "Error: NULL pointer provided to dataToBuffer\n");
        return -1;  // Indicate failure due to NULL pointer
    }
    else
    {    
        memcpy(ptr, &x, sizeof(int16_t));
        memcpy(ptr + 1*sizeof(int16_t), &y, sizeof(int16_t));
        memcpy(ptr + 2*sizeof(int16_t), &z, sizeof(int16_t));
        memcpy(ptr + 3*sizeof(int16_t), &temp, sizeof(int16_t));
    }
    return 0;
}

static void waitToStart(void)
{
    printf("Type anything to start: "); //test
    scanf("%s", str_test); //test
}