#include "dooya_key.h"
#include "dooya_remout.h"
#include "dooya_fac.h"
#include "dooya_led.h"


typedef enum	
{
	KEY_LOW=0,
	KEY_HIGH,
}KEY_MODE_T;


//#define GPIO_INPUT_KEY_1     4
#define GPIO_INPUT_KEY_2     5
#define GPIO_INPUT_KEY_3     16
#define GPIO_INPUT_KEY_4     2
/*
static gpio_dev_t key1={
	.port=GPIO_INPUT_KEY_1,
	.config=INPUT_PULL_UP,
	};*/
static gpio_dev_t key2={
	.port=GPIO_INPUT_KEY_2,
	.config=INPUT_PULL_UP,
	};
static gpio_dev_t key3={
	.port=GPIO_INPUT_KEY_3,
	.config=INPUT_PULL_UP,
	};
static gpio_dev_t key4={
	.port=GPIO_INPUT_KEY_4,
	.config=INPUT_PULL_UP,
	};



#define KEY_QUEUE_BUF_SIZE              (10)

static char         key_queue_buf[KEY_QUEUE_BUF_SIZE];



static void dooya_key_init(void)
{
	//hal_gpio_init(&key1);
	hal_gpio_init(&key2);
	//gpio16_input_conf();
	//hal_gpio_init(&key4);
}

static uint32_t dooya_get_key1_status(void)
{
	//uint32_t value;
	//hal_gpio_input_get(&key1, &value);
	//return value;

}

static uint32_t dooya_get_key2_status(void)
{
	uint32_t value;
	hal_gpio_input_get(&key2, &value);
	return value;

}

static uint32_t dooya_get_key3_status(void)
{
	uint32_t value;
	value=gpio16_input_get();
	return value;

}

static uint32_t dooya_get_key4_status(void)
{
	uint32_t value;
	hal_gpio_input_get(&key4, &value);
	return value;

}



static int dooya_read_key_value(void)
{
	unsigned char key_flag=0;

	if(KEY_LOW==dooya_get_key2_status())
	{
		if(dooya_fac_check()==1)
		{
			dooya_fac_key_model_key2_set();
		}
		else
		{
			key_flag=key_flag|0x02;
		}
	}
	/*
	if(KEY_LOW==dooya_get_key3_status())
	{
		if(dooya_fac_check()==1)
		{
			dooya_fac_key_model_key3_set();
		}
		else
		{
			key_flag=key_flag|0x04;
		}
	}
	if(KEY_LOW==dooya_get_key4_status())
	{
		if(dooya_fac_check()==1)
		{
			dooya_fac_key_model_key4_set();
		}
		else
		{
			key_flag=key_flag|0x08;
		}
		
	}
	*/
	return key_flag;
}
extern int user_master_dev_available(void);

static void dooya_key_handle(void *paras)
{
	unsigned char key_flag_tmp;
	unsigned char key_flag_tmp1;
	while(1)
	{
		key_flag_tmp=0;
		key_flag_tmp=dooya_read_key_value();
		if(0!=key_flag_tmp)
		{
			aos_msleep(50);
			
			key_flag_tmp1=0;
			key_flag_tmp1=dooya_read_key_value();
			
			if(key_flag_tmp1==key_flag_tmp)
			{
				
				
					dooya_set_remout_data(key_flag_tmp1,0);
					if(user_master_dev_available())
					{
						dooya_set_led_status(LED_TAGGLE_TIME,1,1);
					}
					aos_msleep(500);
				

				
			}
			
		}

		aos_msleep(30);
	}
}



uint8_t dooya_create_key_thread(void)
{
	printf("dooya_create_key_thread\r\n");
	dooya_key_init();
	aos_task_new("key", (void (*)(void *))dooya_key_handle, NULL, 1024 * 1);
	
	return 0;
}

