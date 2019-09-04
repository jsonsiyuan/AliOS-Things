#ifndef __DOOYA_LED_H__
#define __DOOYA_LED_H__

#include <stdio.h>
#include "aos/kernel.h"
#include "aos/hal/gpio.h"


typedef enum	
{
	LED_CLOSE=0,
	LED_OPEN,
	LED_TAGGLE,
}LED_ACTION_T;


uint8_t dooya_create_led_thread(void);
void dooya_set_led_status(LED_ACTION_T status,uint8_t hz);



#endif

