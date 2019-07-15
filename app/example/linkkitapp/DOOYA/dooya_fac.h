#ifndef __DOOYA_FAC_H__
#define __DOOYA_FAC_H__

#include <stdio.h>
#include <stdint.h>

#include "aos/kernel.h"

void dooya_fac_set(void);
uint8_t dooya_fac_check(void);
void dooya_fac_start(void);
void dooya_fac_stop(void);
uint8_t dooya_fac_wifi_model_check(void);
void dooya_fac_wifi_model_ok(void);
void dooya_fac_key_led_check(void);
uint8_t dooya_create_fac_thread(void);


#endif
