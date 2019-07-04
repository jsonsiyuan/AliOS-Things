#include "dooya_wifi_status.h"
#include "aos/kv.h"
#include "netmgr.h"
#include "dooya_led.h"



extern void do_awss_active();
//extern void linkkit_event_monitor(int event);

static void dooya_start_smart_config_handle(void *p)
{
    //iotx_event_regist_cb(linkkit_event_monitor);
    printf("%s\n", __func__);
	do_awss_active();
    netmgr_start(true);
    aos_task_exit(0);
}
static void dooya_start_smart_config_start(void)
{
	dooya_set_led_g_status(LED_TAGGLE,4);
	aos_task_new("netmgr_start", dooya_start_smart_config_handle, NULL, 4096);

}

static void dooya_start_sta(void)
{
	//iotx_event_regist_cb(linkkit_event_monitor);
	if(netmgr_wifi_check_ssid()==1)
	{
		dooya_start_smart_config_start();
	}
	else
	{
		netmgr_reconnect_wifi();
	}
}

static void dooya_wifi_check_handle(void *paras)
{	
	int ret;
	D_WIFI_STATUS_T d_wifi_status;
	int tmp=sizeof(D_WIFI_STATUS_T);
	ret=aos_kv_get(dooya_wifi_kv, (void *)&d_wifi_status, &tmp);
	if(0==ret)
	{	
		printf("##sun read is ok wifi_status is [%d]\r\n",d_wifi_status);
		if(d_wifi_status==D_WIFI_SMART_CONFIG)
		{
			dooya_start_smart_config_start();

		}
		else
		{	
			dooya_start_sta();
		}
		
	}
	else
	{
		printf("##sun read is error \r\n");
		dooya_start_smart_config_start();

	}
	aos_task_exit(0);
}
uint8_t dooya_create_wifi_check_thread(void)
{
	
	aos_task_new("wifi_kv", (void (*)(void *))dooya_wifi_check_handle, NULL, 1024 * 5);
	
	return 0;
}

void dooya_set_wifi_smartconfig(void)
{
	D_WIFI_STATUS_T d_wifi_status=D_WIFI_SMART_CONFIG;
	aos_kv_set(dooya_wifi_kv, (void *)&d_wifi_status, sizeof(D_WIFI_STATUS_T),1);
}

void dooya_set_wifi_STA(void)
{
	D_WIFI_STATUS_T d_wifi_status=D_WIFI_STA;
	aos_kv_set(dooya_wifi_kv, (void *)&d_wifi_status, sizeof(D_WIFI_STATUS_T),1);
}
void dooya_set_wifi_softAP(void)
{
	D_WIFI_STATUS_T d_wifi_status=D_WIFI_SOFTAP;
	aos_kv_set(dooya_wifi_kv, (void *)&d_wifi_status, sizeof(D_WIFI_STATUS_T),1);
}




