
#include "dooya_wdg.h"
#include "aos/hal/wdg.h"



wdg_dev_t dooya_wdg;
void dooya_wdg_start(void)
{
	rec_wdt_init(1000);
}

void dooya_wdg_feed(void)
{
	rec_wdt_feed();
}

void dooya_wdg_stop(void)
{
	//hal_wdg_finalize(&dooya_wdg);
}

int dooya_wgd_handle(void *paras)
{
	dooya_wdg_start();
	aos_msleep(100);
	printf("####sun# %s start\r\n",__func__);
	while(1)
	{
		dooya_wdg_feed();
		aos_msleep(500);
	}	
	dooya_wdg_stop();
	aos_task_exit(0);
}

uint8_t dooya_create_wdg_thread(void)
{
		
	aos_task_new("wdg", (void (*)(void *))dooya_wgd_handle, NULL, 1024 * 1);

	return 0;
}

