#ifndef __DOOYA_REMOUT_H__
#define __DOOYA_REMOUT_H__

#include <stdio.h>
#include "aos/kernel.h"
#include "aos/hal/gpio.h"

uint8_t dooya_get_remout_data(void);
void dooya_set_remout_data(uint8_t data);
void dooya_clean_remout_data(void);
uint8_t dooya_create_remout_thread(void);
void dooya_fac_remout_send(void);
uint32_t dooya_get_remout_address(void);




#endif


