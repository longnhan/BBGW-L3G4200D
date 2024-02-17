#include "l3g4.h"

uint8_t readDeviceName(uint8_t *ptr)
{
    getI2cData(DEVICE_NAME, ptr, 1);
    printf("devce name: 0x%x\n", ptr[0]);
}