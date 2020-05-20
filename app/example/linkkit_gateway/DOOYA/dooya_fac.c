
#include <aos/yloop.h>
#include "dooya_fac.h"
#include "dooya_wifi_status.h"
#include "dooya_led.h"
#include "dooya_uart_send.h"
#include "netmgr.h"
#include "network/hal/wifi.h"

#define FAC_TIME_OUT 60
static uint8_t dooya_fac_model=0;
static uint8_t dooya_fac_wifi_model=0;
static uint8_t dooya_fac_led_model=0;

void dooya_fac_set(void)
{
	dooya_set_wifi_FAC();
	aos_msleep(100);
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
	dooya_set_led_g_status(LED_TAGGLE ,1);
}

void dooya_fac_stop(void)
{
	dooya_set_wifi_STA();
	netmgr_clear_ap_config();
}

uint8_t dooya_fac_wifi_model_check(void)
{
	return dooya_fac_wifi_model;
}

void dooya_fac_wifi_model_ok(void)
{
	dooya_fac_wifi_model=1;
	
	 
}

void dooya_fac_key_led_check(void)
{
	if(dooya_fac_wifi_model_check()==1)
	{
		dooya_fac_led_model=1;
	}
	
}

int dooya_fac_handle(void *paras)
{
	aos_msleep(100);
	uint8_t count_tmp=0;
	int8_t wifi_rssi_int;
	int8_t wifi_rssi[4];
	hal_wifi_link_stat_t out_info;
	printf("####sun# %s start\r\n",__func__);
	while(1)
	{

		if((dooya_fac_wifi_model_check()==1)&&(dooya_fac_led_model==0))
		{
			count_tmp= 0;		
			hal_wifi_get_link_stat(NULL, &out_info);
			
			printf("test ressi is (%d)\r\n",out_info.wifi_strength);
			wifi_rssi_int=(char)out_info.wifi_strength;
			printf("test ressi is (%d)\r\n",wifi_rssi_int);
//			dooya_response_fac(1,wifi_rssi_int);	

			
		}
		else if((dooya_fac_wifi_model_check()==1)&&(dooya_fac_led_model==1))
		{
			count_tmp= 0;
			dooya_set_led_g_status(LED_CLOSE ,1);
			dooya_set_led_r_status( LED_TAGGLE,1);
			dooya_fac_stop();
			while(1)
			{
				aos_msleep(5000);
				
				
			}
		}
		else 
		{
			count_tmp++;
		}		
		if(count_tmp>FAC_TIME_OUT)
		{
			//dooya_response_fac(0,0);
			dooya_fac_stop();
			while(1)
			{
				aos_msleep(5000);
				
				
			}
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

