#ifndef __DOOYA_LED_H__
#define __DOOYA_LED_H__

#include <stdio.h>
#include "aos/kernel.h"
#include "aos/hal/gpio.h"

typedef  struct 
{
	uint8_t led_status;
	uint8_t led_HZ;
}LED_STATUS_T;

typedef enum	
{
	LED_CLOSE=0,
	LED_OPEN,
	LED_TAGGLE,
}LED_ACTION_T;

extern LED_STATUS_T led_g_status;

extern LED_STATUS_T led_r_status;


uint8_t dooya_create_led_thread(void);
void dooya_set_led_r_status(LED_ACTION_T status,uint8_t hz);
void dooya_set_led_g_status(LED_ACTION_T status,uint8_t hz);


#endif

