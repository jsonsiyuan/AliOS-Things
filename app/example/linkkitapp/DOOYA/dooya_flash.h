#ifndef __DOOYA_FLASH_H__
#define __DOOYA_FLASH_H__

#include <stdio.h>
#include <stdint.h>

#include "aos/kernel.h"

uint8_t dooya_flash_read_productkey(uint32_t offset,void *data,uint32_t length);
uint8_t dooya_flash_read_devicename(uint32_t offset,void *data,uint32_t length);
uint8_t dooya_flash_read_devicesecret(uint32_t offset,void *data,uint32_t length);
uint8_t dooya_flash_read_433(uint32_t offset,void *data,uint32_t length);



#endif
