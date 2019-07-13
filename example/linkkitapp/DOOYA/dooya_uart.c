#include "dooya_uart.h"
#include "dooya_uart_recv_handle.h"
#include "hal/hal.h"
#include "hal/soc/soc.h"
#include <aos/aos.h>
#include "dooya_uart_send.h"
#include "dooya_led.h"

#define UART_PORT_NUM  1
#define UART_baud_rate 9600

#define UART_BUF_SIZE   10
#define UART_TX_TIMEOUT 10
#define UART_RX_TIMEOUT 10

static aos_timer_t uart_timer;
static uint16_t retry_num=0;

static uart_dev_t uart_use={
	.port = UART_PORT_NUM,
	.config.baud_rate    = UART_baud_rate,
	.config.data_width   = DATA_WIDTH_8BIT,
	.config.parity       = NO_PARITY,
	.config.stop_bits    = STOP_BITS_1,
	.config.flow_control = FLOW_CONTROL_DISABLED,
	.config.mode         = MODE_TX_RX,
};

static void uart_timer_handler(void * p_context)
{
	printf("uart_timer_handler##\r\n");
	retry_num++;
	if(retry_num>5)
	{
		printf("UART_ERROR##\r\n");
		dooya_set_led_g_status(LED_CLOSE,1);
		dooya_set_led_r_status(LED_TAGGLE,10);
	}
	dooya_start_motor_check();
}

static void dooya_uart_time_init(void)
{

	aos_timer_new(&uart_timer, uart_timer_handler, NULL, 1000, 1);
}
static void dooya_uart_time_start(void)
{
	aos_timer_start(&uart_timer);
}

static void dooya_uart_init(void)
{
	hal_uart_init(&uart_use);
	dooya_uart_time_init();
	dooya_uart_time_start();

}


static void dooya_uart_handle(void *paras)
{
	aos_msleep(100);
	int rx_size ;
	uint8_t uart_data_tmp;
	uint8_t f_index=0;
	uint8_t b_index=0;
	uint8_t uart_data_buf[256];
	uint16_t crc_tmp;
	int32_t ret = -1;
	uint8_t recv_length;
	uint8_t i;
	printf("####sun# dooya_uart_handle start\r\n");
	while(1)
	{
		memset(uart_data_buf,0,sizeof(uart_data_buf));
		ret=hal_uart_recv_II(&uart_use, uart_data_buf, 5,&rx_size, 100);
		if ((ret == 0))
		{
			if(uart_data_buf[0]==0x55&&uart_data_buf[1]==0x00&&uart_data_buf[2]==0x00)
			{
				rx_size=0;
				ret = -1;
				ret =hal_uart_recv_II(&uart_use, uart_data_buf+5, uart_data_buf[4]+2,&rx_size, 500);
				if((ret == 0))
				{
					printf("##sun ok\r\n");
					printf("recv data is ");
					for (i=0;i<uart_data_buf[4]+7;i++)
					{
						printf(" %x ",uart_data_buf[i]);								
					}
					printf("\r\n");
					crc_tmp=qioucrc16(dooya,uart_data_buf, uart_data_buf[4]+5);
					if((uart_data_buf[uart_data_buf[4]+5]==(crc_tmp%256))
							&&(uart_data_buf[uart_data_buf[4]+6]==(crc_tmp/256)))
						{
							printf("recive crc is ok\r\n");
							retry_num=0;
							switch(uart_data_buf[3])
							{
								case MOTOR_SEND:
									dooya_motor_send_handle(uart_data_buf+5,uart_data_buf[4]);
								break;
								case MOTOR_RESPONSE:
									dooya_motor_response_handle(uart_data_buf+5,uart_data_buf[4]);
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
	return 0;

}

void dooya_uart_send( uint8_t *src, uint32_t size)
{
	hal_uart_send(&uart_use, src, size, 1000);
}

/*------------------------------------------------
函数说明：求出数据的CRC校验码crc为初始校验码，*buf为初始地址，x为所求的个数
--------------------------------------------------*/
unsigned int qioucrc16(unsigned int crc,unsigned char *buf,unsigned int x)
{
	unsigned char hi,lo;
	unsigned int i;
	for (i=0;i<x;i++)
	{
	   crc=calccrc(*buf,crc);
	   buf++;
	}
	hi=crc%256;
	lo=crc/256;
	crc=(hi<<8)|lo;
	return crc;
}
/*-------------------------------------------------
调用方式：unsigned int calccrc(uchar crcbuf,uint crc)
函数说明：在crc的基础上求出数CRCBUF的CRC码
--------------------------------------------------*/
unsigned int calccrc(unsigned char crcbuf,unsigned int crc)
{
	unsigned char i; 
	unsigned char chk;
	crc=crc ^ crcbuf;
	for(i=0;i<8;i++)
	{
	  chk=crc&1;
	  crc=crc>>1;
	  crc=crc&0x7fff;
	  if (chk==1)
	  crc=crc^0xa001;
	  crc=crc&0xffff;
	}
	return crc; 
}





