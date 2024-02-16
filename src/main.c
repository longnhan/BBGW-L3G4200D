#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include "main.h"

int main(void)
{
    i2cInit();
    printf("Test GDBServer\n");
    while(1)
    {
        sleep(1);
    }
    return 0;    
}