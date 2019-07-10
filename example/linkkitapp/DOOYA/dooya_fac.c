#include <aos/aos.h>
#include <aos/yloop.h>
#include "dooya_fac.h"
#include "dooya_wifi_status.h"
#include "dooya_led.h"
#include "dooya_uart_send.h"
#include "netmgr.h"

#define FAC_TIME_OUT 60
static uint8_t dooya_fac_model=0;
static uint8_t dooya_fac_wifi_model=0;
static uint8_t dooya_fac_led_model=0;

void dooya_fac_set(void)
{
	dooya_set_wifi_FAC();
	aos_reboot();
}

uint8_t dooya_fac_check(void)
{
	return dooya_fac_model;
}

void dooya_fac_start(void)
{
	dooya_fac_model=1;
	dooya_set_wifi_STA();
	dooya_set_led_r_status(LED_CLOSE ,1 );
	dooya_set_led_g_status(LED_CLOSE ,1);
}

void dooya_fac_stop(void)
{
	dooya_fac_model=0;
	dooya_set_wifi_STA();
}

uint8_t dooya_fac_wifi_model_check(void)
{
	return dooya_fac_wifi_model;
}

void dooya_fac_wifi_model_ok(void)
{
	dooya_fac_wifi_model=1;
	netmgr_clear_ap_config();
	 
}

void dooya_fac_key_led_check(void)
{
	if(dooya_fac_wifi_model_check()==1)
	{
		dooya_set_led_g_status(LED_CLOSE ,1);
		dooya_fac_led_model=1;
	}
	
}

int dooya_fac_handle(void *paras)
{
	dooya_fac_start();
	aos_msleep(100);
	uint8_t count_tmp=0;
	printf("####sun# %s start\r\n",__func__);
	while(1)
	{

		if((dooya_fac_wifi_model_check()==1)&&(dooya_fac_led_model==0))
		{
			count_tmp= 0;	
			dooya_set_led_g_status(LED_TAGGLE ,2);	
			dooya_response_fac(1);	
		}
		else if((dooya_fac_wifi_model_check()==1)&&(dooya_fac_led_model==1))
		{
			count_tmp= 0;
			dooya_set_led_g_status(LED_CLOSE ,1);
		}
		else 
		{
			count_tmp++;
		}		
		if(count_tmp>FAC_TIME_OUT)
		{
			dooya_response_fac(0);
		}
		aos_msleep(1000);
		
	}	
	aos_task_exit(0);
}

uint8_t dooya_create_fac_thread(void)
{
		
	aos_task_new("fac", (void (*)(void *))dooya_fac_handle, NULL, 1024 * 1);

	return 0;
}

