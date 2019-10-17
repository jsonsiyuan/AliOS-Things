#include "dooya_remout.h"
#include "k_api.h"
#include "dooya_flash.h"





#define CMD_UP 0x11
#define CMD_DOWN 0x33
#define CMD_STOP 0x55
#define CMD_SETUP 0xcc

#define remout_port 14
#define LENGTH_OF_ADDRESS (8+1)

static uint8_t remout_data=0xff;;
static uint8_t net_flag=0;


static uint32_t address_value=0;
static uint8_t address_value_tmp[LENGTH_OF_ADDRESS];
#define  fax_address_value (0x01010101)
#define  fax_value (0x01)


static gpio_dev_t remout={
	.port=remout_port,
	.config=OUTPUT_PUSH_PULL,
	};
static uint8_t CharToInt(char hex) 
{
	if (hex>='0' && hex <='9')
		return hex - '0';
	if (hex>='A' && hex <= 'F')
		return hex-'A'+10;
	if(hex>='a' && hex <= 'f')
		return hex-'a'+10;
	return -1;
}

static uint8_t dooya_remout_get_address(void)
{
	uint8_t res;
	uint8_t tmp=LENGTH_OF_ADDRESS;
	memset(address_value_tmp,0,sizeof(address_value_tmp));
	res=dooya_flash_read_433(63,address_value_tmp,LENGTH_OF_ADDRESS-1);
	if(0==res)
	{
		if(0!=strlen(address_value_tmp))
		{
			printf("\r\n  433 ADDRESS is [%s]\r\n",address_value_tmp);
			return 0;
		}
	}
	return 1;
}


static uint8_t dooya_remout_get_address_hex(void)
{
	uint8_t res;
	uint8_t i;
	uint8_t address_atoi_tmp[LENGTH_OF_ADDRESS-1];
	res=dooya_remout_get_address();
	if(0==res)
	{
		for(i=0;i<LENGTH_OF_ADDRESS-1;i++)
		{
			address_atoi_tmp[i]=CharToInt(address_value_tmp[i]);
		}
	}
	else
	{
		return 1;
	}
	for(i=0;i<LENGTH_OF_ADDRESS-1;i++)
	{
		address_value+=address_atoi_tmp[i]<<((LENGTH_OF_ADDRESS-2-i)*4);
	}
	printf("\r\n  433 ADDRESS is [%x]\r\n",address_value);
	return 0;
}

	
static void dooya_remout_high(void)
{
	hal_gpio_output_high(&remout);
	os_delay_us(720);
	hal_gpio_output_low(&remout);
	os_delay_us(360);
}

static void dooya_remout_low(void)
{
	hal_gpio_output_high(&remout);
	os_delay_us(360);
	hal_gpio_output_low(&remout);
	os_delay_us(720);
}

static void dooya_remout_init(void)
{
	hal_gpio_init(&remout);
	hal_gpio_output_low(&remout);
	dooya_clean_remout_data();
	dooya_remout_get_address_hex();
	
}

static void dooya_remout_send_address(void)
{
	uint32_t address_value_tmp=address_value;
	int i;
	for(i=0;i<32;i++)
	{
		if(address_value_tmp&0x80000000)
		{
			dooya_remout_high();
		}
		else
		{
			 dooya_remout_low();
		}
		address_value_tmp=(address_value_tmp)<<1;
		
	}
	

}

static void dooya_remout_send_data(unsigned char data)
{
	
	unsigned char data_tmp=data;
	int i;
	
	for(i=0;i<8;i++)
	{
		if(data_tmp&0x80)
		{
			dooya_remout_high();
		}
		else
		{
			 dooya_remout_low();
		}	
		data_tmp=data_tmp<<1;	
	}
	
	
}

static void dooya_remout_send(unsigned char data)
{
	hal_gpio_output_high(&remout);
	os_delay_us(4800);
	hal_gpio_output_low(&remout);
	os_delay_us(1500);
	dooya_remout_send_address();
	dooya_remout_send_data(data);
	hal_gpio_output_low(&remout);
}
static uint8_t dooya_get_send_data_from_user(void)
{
	unsigned char key_flag_tmp;
	unsigned char send_data_tmp;
	key_flag_tmp=dooya_get_remout_data();
	send_data_tmp=0xff;

	switch(key_flag_tmp)
	{
		case 0x01:
			send_data_tmp=CMD_SETUP;

		break;
		case 0x02:
			send_data_tmp=CMD_UP;
		break;
		case 0x04:
			send_data_tmp=CMD_STOP;
		break;
		case 0x08:
			send_data_tmp=CMD_DOWN;
		break;
	}
	return send_data_tmp;
}

static void dooya_remout_send_data_of_net(void)
{
	unsigned char send_data_tmp;
	unsigned char send_data_tmp1=0xff;
	uint8_t i=0;
	while (i<15)
	{
		send_data_tmp=dooya_get_send_data_from_user();
		printf("send_data_tmp [%x]\r\n",send_data_tmp);
		if(send_data_tmp!=send_data_tmp1)
		{
			send_data_tmp1=send_data_tmp;
			i=0;
		}
		if(send_data_tmp!=0xff)
		{
			

			CPSR_ALLOC();
			RHINO_CRITICAL_ENTER();
			dooya_remout_send(send_data_tmp);
			RHINO_CRITICAL_EXIT();
			aos_msleep(50);
		}
		i++;
	}
}

static void dooya_remout_handle(void *pvParameters)
{
	unsigned char send_data_tmp;
	int i;
	while(1)
	{

		if(1==dooya_get_net_flag_data())
		{
			dooya_remout_send_data_of_net();
		}
		else
		{
			send_data_tmp=dooya_get_send_data_from_user();

			if(send_data_tmp!=0xff)
			{
				printf("send_data_tmp [%x]\r\n",send_data_tmp);
				for(i=0;i<5;i++)
				{
					CPSR_ALLOC();
					RHINO_CRITICAL_ENTER();
					dooya_remout_send(send_data_tmp);
					RHINO_CRITICAL_EXIT();
					aos_msleep(50);
				}

			}
		}

		dooya_clean_remout_data();
		aos_msleep(100);
	}
}


static void dooya_remout_send_fac_address(void)
{
	uint32_t address_value_tmp=fax_address_value;
	int i;
	for(i=0;i<32;i++)
	{
		if(address_value_tmp&0x80000000)
		{
			dooya_remout_high();
		}
		else
		{
			 dooya_remout_low();
		}
		address_value_tmp=(address_value_tmp)<<1;
		
	}
	

}

void dooya_fac_remout_send(void)
{
	hal_gpio_output_high(&remout);
	os_delay_us(4800);
	hal_gpio_output_low(&remout);
	os_delay_us(1500);
	dooya_remout_send_address();
	dooya_remout_send_data(fax_value);
	hal_gpio_output_low(&remout);
}

uint32_t dooya_get_remout_address(void)
{
	return address_value;
}


uint8_t dooya_get_remout_data(void)
{
	return remout_data;
}

uint8_t dooya_get_net_flag_data(void)
{
	return net_flag;
}

void dooya_set_remout_data(uint8_t data,uint8_t net_flag_tmp)
{
	remout_data=data;
	net_flag=net_flag_tmp;
}
void dooya_clean_remout_data(void)
{
	remout_data=0xff;
	net_flag=0;
}

uint8_t dooya_create_remout_thread(void)
{
	printf("dooya_create_remout_thread\r\n");
	dooya_remout_init();	
	aos_task_new("remout", (void (*)(void *))dooya_remout_handle, NULL, 1024 * 1);
	return 0;
}

