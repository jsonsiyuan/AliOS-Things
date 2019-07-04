#ifndef __DOOYA_WIFI_STATUS_H__
#define __DOOYA_WIFI_STATUS_H__

#include <stdio.h>
#include <stdint.h>

#include "aos/kernel.h"

#define dooya_wifi_kv "wifi_kv"

typedef enum	
{
	D_WIFI_SMART_CONFIG=0,
	D_WIFI_STA,
	D_WIFI_SOFTAP,
}D_WIFI_STATUS_T;

uint8_t dooya_create_wifi_check_thread(void);
void dooya_set_wifi_smartconfig(void);
void dooya_set_wifi_STA(void);
void dooya_set_wifi_softAP(void);

#endif
