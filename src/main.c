#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "main.h"

/*system i2c config*/
int i2c_File;
char i2c_Device[]="/dev/i2c-2";
uint8_t device_Address = 0x69;

int main(void)
{
    uint8_t buf[1]={0};

    i2cInit();
    readDeviceName(buf);

    while(1)
    {
        sleep(1);
    }
    return 0;    
}