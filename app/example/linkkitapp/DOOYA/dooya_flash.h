#ifndef __DOOYA_FLASH_H__
#define __DOOYA_FLASH_H__

#include <stdio.h>
#include <stdint.h>

#include "aos/kernel.h"

void dooya_use_flash_info(void);
void dooya_use_flash_read(uint32_t offset,void *data,uint32_t length);
void dooya_use_flash_erase(uint32_t offset,uint32_t length);
void dooya_use_flash_write(uint32_t offset,void *data,uint32_t length);


#endif
