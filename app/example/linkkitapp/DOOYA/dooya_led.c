#include "dooya_led.h"


#define led_port 12

typedef  struct 
{
	uint8_t led_new_status;
	uint8_t led_HZ;
}LED_STATUS_T;



static gpio_dev_t led={
	.port=led_port,
	.config=OUTPUT_PUSH_PULL,
	};


	
static LED_STATUS_T led_status={
	.led_new_status=LED_CLOSE,
	.led_HZ=1,
};


	

static void dooya_led_init(void)
{
	hal_gpio_init(&led);
}

static void dooya_open_led(void)
{

	hal_gpio_output_low(&led);
	led_status.led_new_status=LED_OPEN;
}

static void dooya_close_led(void)
{

	hal_gpio_output_high(&led);

	led_status.led_new_status=LED_CLOSE;
}

static void dooya_toggle_led(void)
{
	hal_gpio_output_toggle(&led);
	led_status.led_new_status=LED_TAGGLE;
}





static int dooya_led_handle(void *paras)
{
	dooya_close_led();
	aos_msleep(100);
	printf("####sun# dooya_led_handle start\r\n");
	while(1)
	{
		switch(led_status.led_new_status)
		{
			
			case LED_OPEN:
				dooya_open_led();
				aos_msleep(100);
			break;
			case LED_CLOSE:
				dooya_close_led();
				aos_msleep(100);
			break;
			case LED_TAGGLE:
				dooya_toggle_led();
				aos_msleep(1000/led_status.led_HZ);
			break;
		}
		
	}
}

void dooya_set_led_status(LED_ACTION_T status,uint8_t hz)
{
	led_status.led_new_status=status;
	led_status.led_HZ=hz;
}


uint8_t dooya_create_led_thread(void)
{
	dooya_led_init();	
	aos_task_new("led", (void (*)(void *))dooya_led_handle, NULL, 1024 * 1);
	return 0;
}
