#include "logfile.h"

/*Global path variables*/
char LOGFILE_NAME[PATH_MAX] = "/data_output.csv";

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

int main()
{
    processSetup();

    messageQueue_Init(&mq_gyro, &mq_gyro_attr);
    /*msg queue attributes*/
    // mq_gyro_attr.mq_flags = 0;
    // mq_gyro_attr.mq_maxmsg = MQ_QUEUE_SIZE;
    // mq_gyro_attr.mq_msgsize = MQ_MSG_SIZE;
    // mq_gyro_attr.mq_curmsgs = 0;

    // /*message queue creating*/
    // mq_gyro = mq_open(MQ_NAME, O_RDONLY, 0644, &mq_gyro_attr);
    // if(mq_gyro == -1)
    // {
    //     printf("msg queue open fail\n");
    //     perror("mq_open");
    //     exit(EXIT_FAILURE);
    // }
    // else
    // {
    //     printf("queue opened successfully\n");
    // }

    /*setup message queue notification*/
    messageQueue_Register_Notify(mq_gyro, &mqSignal);
    // mqSignal.sigev_notify = SIGEV_SIGNAL;
    // mqSignal.sigev_signo = SIGUSR1;

    // if(mq_notify(mq_gyro, &mqSignal) == -1)
    // {
    //     printf("msg queue notify SIGUSR1 create fail\n");
    //     perror("mq_notify");
    //     mq_close(mq_gyro);
    //     exit(EXIT_FAILURE);
    // }
    // else
    // {
    //     printf("queue notify registered successfully\n");
    // }

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
    fp = fopen(LOGFILE_NAME, "w+");
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
            printDateTime(fp);
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
            bufferToData(mqSensorBuffer, &xAxis, &yAxis, &zAxis, &temp);

            /*write data to log file*/
            fprintf(fp, "%d,%d,%d,%d\n", xAxis, yAxis, zAxis, temp);
            
            printf("receive buffer DONE\n");
            
            /*re-register message queue notification*/
            messageQueue_Register_Notify(mq_gyro, &mqSignal);
            // mqSignal.sigev_notify = SIGEV_SIGNAL;
            // mqSignal.sigev_signo = SIGUSR1;

            // if(mq_notify(mq_gyro, &mqSignal) == -1)
            // {
            //     printf("msg queue notify SIGUSR1 create fail\n");
            //     mq_close(mq_gyro);
            //     exit(EXIT_FAILURE);
            // }
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

static int bufferToData(char *ptr, int16_t *x, int16_t *y, int16_t *z, int8_t *temp)
{
    if(ptr == NULL | x == NULL | y == NULL | z == NULL | temp == NULL)
    {
        fprintf(stderr, "Error: NULL pointer provided to dataToBuffer\n");
        return -1;  // Indicate failure due to NULL pointer
    }
    else
    {    
        memcpy(x, ptr, sizeof(int16_t));
        memcpy(y, ptr + 1*sizeof(int16_t), sizeof(int16_t));
        memcpy(z, ptr + 2*sizeof(int16_t), sizeof(int16_t));
        memcpy(temp, ptr + 3*sizeof(int16_t), sizeof(int8_t));
    }
    return 0;
}

static void printDateTime(FILE *fp)
{
    time_t now = time(NULL);
    char time_str[100];
    strftime(time_str, sizeof(time_str), "%Y-%m-%d %H:%M:%S", localtime(&now));
    fprintf(fp, "Date and Time: %s\n", time_str);
}

static void curWorkingPath(char *fname)
{
    char cwp[PATH_MAX] = {0};
    if(getcwd(cwp, sizeof(cwp)) != NULL)
    {
        printf("working path is: %s\n", cwp);
        strcat(cwp, fname);
        strcpy(fname, cwp);
        printf("File full path: %s\n", fname);
    }
    else
    {
        perror("getcwd() error");
        exit(EXIT_FAILURE);
    }
}

void processSetup(void)
{
    /*get working path*/
    curWorkingPath(LOGFILE_NAME);
}

void messageQueue_Init(mqd_t *mqd_ptr, struct mq_attr *attr_ptr)
{
    attr_ptr->mq_flags = 0;
    attr_ptr->mq_maxmsg = MQ_QUEUE_SIZE;
    attr_ptr->mq_msgsize = MQ_MSG_SIZE;
    attr_ptr->mq_curmsgs = 0;

    /*message queue creating*/
    *mqd_ptr = mq_open(MQ_NAME, O_RDONLY, 0644, attr_ptr);
    if(*mqd_ptr == -1)
    {
        printf("msg queue open fail\n");
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("queue opened successfully\n");
    }
}

void messageQueue_Register_Notify(mqd_t mqd, struct sigevent *sig_ptr)
{
    sig_ptr->sigev_notify = SIGEV_SIGNAL;
    sig_ptr->sigev_signo = SIGUSR1;

    if(mq_notify(mqd, sig_ptr) == -1)
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
}