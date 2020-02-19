#include "dooya_uart.h"
#include "dooya_uart_recv_handle.h"

#include "dooya_uart_send.h"
#include "dooya_led.h"

#define UART_PORT_NUM  1
#define UART_baud_rate 9600

#define UART_BUF_SIZE   10
#define UART_TX_TIMEOUT 10
#define UART_RX_TIMEOUT 10

static aos_timer_t uart_timer;
static uint16_t retry_num=0;
static uint8_t retry_over_flag=0;

static uart_dev_t uart_use={
	.port = UART_PORT_NUM,
	.config.baud_rate    = UART_baud_rate,
	.config.data_width   = DATA_WIDTH_8BIT,
	.config.parity       = NO_PARITY,
	.config.stop_bits    = STOP_BITS_1,
	.config.flow_control = FLOW_CONTROL_DISABLED,
	.config.mode         = MODE_TX_RX,
};

static aos_mutex_t  dooya_uart_mutex ;
	
static int dooya_uart_init_mutex(void)
{
	return  aos_mutex_new(&dooya_uart_mutex);
}

static int dooya_uart_lock_mutex(void)
{
	printf("##dooya_uart_lock_mutex\r\n");
	return  aos_mutex_lock(&dooya_uart_mutex, AOS_WAIT_FOREVER);
}

static int dooya_uart_unlock_mutex(void)
{
	printf("##dooya_uart_unlock_mutex\r\n");
	return	aos_mutex_unlock(&dooya_uart_mutex);
}

static void uart_timer_handler(void * p_context)
{
	while(1)
	{
		retry_num++;
		if(retry_num>5)
		{
			//dooya_set_led_g_status(LED_CLOSE,1);
			//dooya_set_led_r_status(LED_TAGGLE,10);
			retry_over_flag=1;
		}
		else if(retry_over_flag)
		{
			retry_over_flag=0;
			//dooya_set_led_r_status(LED_CLOSE,1);
		}
		if(dooya_fac_check()==1)
		{
			retry_num=0;
		}
		else
		{
			dooya_start_motor_check();
		}
		aos_msleep(10000);
	}
}

static void dooya_uart_time_init(void)
{

	
}
static void dooya_uart_time_start(void)
{
	aos_timer_start(&uart_timer);
}

static void dooya_uart_init(void)
{
	hal_uart_init(&uart_use);
	dooya_uart_init_mutex();

}


static void dooya_uart_handle(void *paras)
{
	aos_msleep(100);
	int rx_size ;
	uint8_t uart_data_buf[256];
	uint16_t crc_tmp;
	int32_t ret = -1;
	printf("####sun# dooya_led_r_handle start\r\n");
	while(1)
	{
		rx_size=0;
		ret = -1;
		memset(uart_data_buf,0,sizeof(uart_data_buf));
		ret=hal_uart_recv_II(&uart_use, uart_data_buf, 3,&rx_size, 500);
		if ((ret == 0))
		{
			if(uart_data_buf[0]==0x55&&uart_data_buf[1]==0xAA)
			{
				rx_size=0;
				ret = -1;
				ret =hal_uart_recv_II(&uart_use, uart_data_buf+3, uart_data_buf[2],&rx_size, 5*uart_data_buf[2]);
				if((ret == 0))
				{
					crc_tmp=CRC16_MODBUS(uart_data_buf, uart_data_buf[2]+1);
					if((uart_data_buf[uart_data_buf[2]+1]==(crc_tmp/256))
							&&(uart_data_buf[uart_data_buf[2]+2]==(crc_tmp%256)))
						{
							retry_num=0;
							switch(uart_data_buf[3])
							{
								case CONTROL_CODE:
									dooya_control_handle(uart_data_buf+4,uart_data_buf[2]-2);
								break;
								case CHECK_CODE:
									dooya_check_handle(uart_data_buf+4,uart_data_buf[2]-2);
								break;
								case NOTICE_CODE:
									dooya_notice_handle(uart_data_buf+4,uart_data_buf[2]-2);
								break;
								case OTA:
								break;
							}

						}


					
				}
				
			}
		}
		
		
	}	
}





uint8_t dooya_create_uart_thread(void)
{
	dooya_uart_init();
	printf("do dooya_create_uart_thread\r\n");	
	aos_task_new("uart", (void (*)(void *))dooya_uart_handle, NULL, 1024);
	aos_task_new("uart_time", (void (*)(void *))uart_timer_handler, NULL, 1024);
	return 0;

}

void dooya_uart_send( uint8_t *src, uint32_t size)
{
	dooya_uart_lock_mutex();
	hal_uart_send(&uart_use, src, size, 1000);
	dooya_uart_unlock_mutex();
}

uint16_t CRC16_MODBUS(uint8_t *puchMsg, uint16_t usDataLen)
{
	uint16_t wCRCin = UUID;

	int16_t wCPoly = 0x8005;
	uint8_t wChar = 0;
	uint8_t i = 0;
	while (usDataLen--)
	{
		wChar = *(puchMsg++);
		wCRCin ^= (wChar << 8);
		for(i = 0; i < 8; i++)
		{
			if(wCRCin & 0x8000)
			{
				wCRCin = (wCRCin << 1) ^ wCPoly;
			}
			else
			{
				wCRCin = wCRCin << 1;
			}
		}
	}
	return (wCRCin);
}





