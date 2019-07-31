#include "dooya_led.h"

#ifdef CONFIG_ESP8266
	#define led_g_port 15
	#define led_r_port 2
#else
	#define led_g_port 3
	#define led_r_port 2
#endif

static gpio_dev_t led_g={
	.port=led_g_port,
	.config=OUTPUT_PUSH_PULL,
	};

static gpio_dev_t led_r={
	.port=led_r_port,
	.config=OUTPUT_PUSH_PULL,
	};
	
LED_STATUS_T led_g_status={
	.led_status=LED_CLOSE,
	.led_HZ=1,
};

LED_STATUS_T led_r_status={
	.led_status=LED_CLOSE,
	.led_HZ=1,
};

	

void dooya_led_g_init(void)
{
	hal_gpio_init(&led_g);
}

void dooya_led_r_init(void)
{
	hal_gpio_init(&led_r);
}

void dooya_led_init(void)
{
	dooya_led_r_init();
	dooya_led_g_init();
}

void dooya_open_led_g(void)
{
#ifdef CONFIG_ESP8266
	hal_gpio_output_high(&led_g);
#else
	hal_gpio_output_low(&led_g);
#endif
	led_g_status.led_status=LED_OPEN;
}

void dooya_close_led_g(void)
{

#ifdef CONFIG_ESP8266
	hal_gpio_output_low(&led_g);
#else
	hal_gpio_output_high(&led_g);
#endif
	led_g_status.led_status=LED_CLOSE;
}

void dooya_toggle_led_g(void)
{
	hal_gpio_output_toggle(&led_g);
	led_g_status.led_status=LED_TAGGLE;
}


void dooya_open_led_r(void)
{
	hal_gpio_output_high(&led_r);
	led_r_status.led_status=LED_OPEN;
}

void dooya_close_led_r(void)
{
	hal_gpio_output_low(&led_r);
	led_r_status.led_status=LED_CLOSE;
}

void dooya_toggle_led_r(void)
{
	hal_gpio_output_toggle(&led_r);
	led_r_status.led_status=LED_TAGGLE;
}

void dooya_set_led_r_status(LED_ACTION_T status,uint8_t hz)
{
	led_r_status.led_status=status;
	led_r_status.led_HZ=hz;
}

void dooya_set_led_g_status(LED_ACTION_T status,uint8_t hz)
{
	led_g_status.led_status=status;
	led_g_status.led_HZ=hz;
}


int dooya_led_g_handle(void *paras)
{
	dooya_close_led_g();
	aos_msleep(100);
	printf("####sun# dooya_led_g_handle start\r\n");
	while(1)
	{
		switch(led_g_status.led_status)
		{
			
			case LED_OPEN:
				dooya_open_led_g();
				aos_msleep(100);
			break;
			case LED_CLOSE:
				dooya_close_led_g();
				aos_msleep(100);
			break;
			case LED_TAGGLE:
				dooya_toggle_led_g();
				aos_msleep(1000/led_g_status.led_HZ);
			break;
		}
		
	}
}
int dooya_led_r_handle(void *paras)
{
	dooya_close_led_r();
	aos_msleep(100);
	printf("####sun# dooya_led_r_handle start\r\n");
	while(1)
	{
		switch(led_r_status.led_status)
		{
			case LED_OPEN:
				dooya_open_led_r();
				aos_msleep(300);
			break;
			case LED_CLOSE:
				dooya_close_led_r();
				aos_msleep(300);
			break;
			case LED_TAGGLE:
				dooya_toggle_led_r();
				aos_msleep(1000/led_r_status.led_HZ);
			break;
		}
		
	}	
}
uint8_t dooya_create_led_thread(void)
{
	dooya_led_init();	
	aos_task_new("led_g", (void (*)(void *))dooya_led_g_handle, NULL, 1024 * 1);
	aos_task_new("led_r", (void (*)(void *))dooya_led_r_handle, NULL, 1024 * 1);
	return 0;
}
