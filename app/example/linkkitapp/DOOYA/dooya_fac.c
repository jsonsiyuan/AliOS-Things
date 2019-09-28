#include <aos/yloop.h>
#include "dooya_fac.h"
#include "dooya_wifi_status.h"
#include "dooya_led.h"
#include "dooya_uart_send.h"
#include "netmgr.h"
#include "dooya_remout.h"
#include "k_api.h"
#include "esp_common.h"



#include "network/hal/wifi.h"
#define dooya_fac_ssid "chanxiancheck"


#define FAC_TIME_OUT 180
static uint8_t dooya_fac_model=0;
static uint8_t dooya_fac_wifi_model=0;
static uint8_t dooya_fac_led_model=0;
static uint8_t dooya_fac_key_model=0;

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
}

void dooya_fac_stop(void)
{
	netmgr_clear_ap_config();
	dooya_fac_model=0;
}

uint8_t dooya_fac_wifi_model_check(void)
{
	return dooya_fac_wifi_model;
}

void dooya_fac_wifi_model_connected(void)
{
	dooya_fac_wifi_model=1;
	
}

uint8_t dooya_fac_key_model_check(void)
{

	return dooya_fac_key_model;
}

void dooya_fac_key_model_key1_set(void)
{

	dooya_fac_key_model=dooya_fac_key_model|0x01;
}

void dooya_fac_key_model_key2_set(void)
{

	dooya_fac_key_model=dooya_fac_key_model|0x02;
}

void dooya_fac_key_model_key3_set(void)
{

	dooya_fac_key_model=dooya_fac_key_model|0x04;
}

void dooya_fac_key_model_key4_set(void)
{

	dooya_fac_key_model=dooya_fac_key_model|0x08;
}

static int dooya_fac_handle(void *paras)
{
	dooya_fac_start();
	aos_msleep(100);
	
	uint8_t wifi_tmp=0;
	uint8_t key_tmp=0;
	uint8_t count_tmp=0;
	uint8_t i;
	int8_t rss=31;
	printf("####sun# %s start\r\n",__func__);
	while(1)
	{
		if(dooya_fac_check()==1)
		{

			
			wifi_tmp=dooya_fac_wifi_model_check();
			key_tmp=dooya_fac_key_model_check();
			if(wifi_tmp==0x01)
			{
				rss=wifi_station_get_rssi();
				printf("########wifi db is {%d}\r\n",wifi_station_get_rssi());
				
				

				
			}
			if((wifi_tmp==0x01)&&(key_tmp==0x0f))
			{
				/*433 send*/
				for(i=0;i<3;i++)
				{
					CPSR_ALLOC();
					RHINO_CRITICAL_ENTER();
					dooya_fac_remout_send();
					RHINO_CRITICAL_EXIT();
					aos_msleep(100);
				}
				aos_msleep(100);
				dooya_response_fac(1,rss,dooya_get_remout_address());
				
				dooya_fac_stop();
			}
			if(count_tmp>FAC_TIME_OUT)
			{
				/*fail*/
				dooya_response_fac(0,0,dooya_get_remout_address());
				dooya_fac_stop();
			}
			else
			{
				count_tmp++;
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

