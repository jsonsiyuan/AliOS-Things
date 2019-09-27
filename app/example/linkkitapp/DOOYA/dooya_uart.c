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
	//printf("##dooya_uart_lock_mutex\r\n");
	return  aos_mutex_lock(&dooya_uart_mutex, AOS_WAIT_FOREVER);
}

static int dooya_uart_unlock_mutex(void)
{
	//printf("##dooya_uart_unlock_mutex\r\n");
	return	aos_mutex_unlock(&dooya_uart_mutex);
}


static void uart_timer_handler(void * p_context)
{
	//printf("uart_timer_handler##\r\n");
	/*retry_num++;
	if(retry_num>5)
	{
		printf("UART_ERROR##\r\n");
		dooya_set_led_g_status(LED_CLOSE,1);
		dooya_set_led_r_status(LED_TAGGLE,10);
	}*/
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
	dooya_uart_init_mutex();

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
	
	uint8_t recv_flag;
	uint8_t recv_len;
	uint8_t i;
	
	while(1)
	{
		recv_flag=0;
		recv_len=0;
		
		rx_size=0;
		ret = -1;
		memset(uart_data_buf,0,sizeof(uart_data_buf));
		ret=hal_uart_recv_II(&uart_use, uart_data_buf, 3,&rx_size, 100);/*拿3个数据*/
		if ((ret == 0))
		{
			if(uart_data_buf[0]==0x55&&uart_data_buf[1]==DOOYA_UART_ID_L&&uart_data_buf[2]==DOOYA_UART_ID_L)
			{
				rx_size=0;
				ret = -1;
				ret=hal_uart_recv_II(&uart_use, uart_data_buf+3, 1,&rx_size, 100);/*拿3个数据*/
				if ((ret == 0))
				{
					rx_size=0;
					ret = -1;
					switch(uart_data_buf[3])
					{
						case WIFI_MODULE_READ :
							ret =hal_uart_recv_II(&uart_use, uart_data_buf+4, 2,&rx_size, 200);
							if(ret == 0)
							{
								rx_size=0;
								ret = -1;
								ret =hal_uart_recv_II(&uart_use, uart_data_buf+6, uart_data_buf[5]+2,&rx_size, 200);
								if(ret == 0)
								{
									recv_flag=1;
									recv_len=uart_data_buf[5]+2+6;
								}
							}
						break;
						case WIFI_MODULE_WRITE :
							ret =hal_uart_recv_II(&uart_use, uart_data_buf+4, 3,&rx_size, 200);
							if(ret == 0)
							{
								recv_flag=1;
								recv_len=7;
							}
						break;
						case MOTOR_RESPONSE:
							ret =hal_uart_recv_II(&uart_use, uart_data_buf+4, 2,&rx_size, 200);
							{
								rx_size=0;
								ret = -1;
								if(uart_data_buf[4]==MOTOR_RESPONSE_MOTOR_INFO)
								{
									ret =hal_uart_recv_II(&uart_use, uart_data_buf+6, uart_data_buf[5]+2,&rx_size, 500);
									if(ret == 0)
									{
										recv_flag=1;
										recv_len=uart_data_buf[5]+2+6;
									}
								}
								else
								{
									ret =hal_uart_recv_II(&uart_use, uart_data_buf+6, 2,&rx_size, 500);
									if(ret == 0)
									{
										recv_flag=1;
										recv_len=2+6;
									}
								}
							}
						break;
							
						case WIFI_MODULE_CONTROL :
							ret =hal_uart_recv_II(&uart_use, uart_data_buf+4, 1,&rx_size, 200);
							if(ret == 0)
							{
								rx_size=0;
								ret = -1;
								switch(uart_data_buf[4])
								{
									case WIFI_MODULE_CONTROL_POSITION:
									case MOTOR_MODULE_CONTROL_SMARTCONFIG:
									case MOTOR_MODULE_CONTROL_UNBIND:
										ret =hal_uart_recv_II(&uart_use, uart_data_buf+5, 2,&rx_size, 200);
										if(ret==0)
										{
											rx_size=0;
											ret = -1;
											ret =hal_uart_recv_II(&uart_use, uart_data_buf+7, 1,&rx_size, 20);
											if(ret==0)
											{
												recv_flag=1;
												recv_len=5+3;
											}
											else
											{
												recv_flag=1;
												recv_len=5+2;
											}
											
										}
										
									break;
									
									default :
										ret =hal_uart_recv_II(&uart_use, uart_data_buf+5, 2,&rx_size, 200);
										if(ret==0)
										{
											recv_flag=1;
											recv_len=5+2;
										}
									break;
									
								}
							}

						break;

					}
				}

				if(recv_flag)
				{
					
					printf("recv data LEN is [%d]  is ",recv_len);
					for (i=0;i<recv_len;i++)
					{
						printf(" %x ",uart_data_buf[i]);								
					}
					printf("\r\n");
					
					crc_tmp=qioucrc16(DOOYA_UART_CRC_INIT,uart_data_buf, recv_len-2);
					if((uart_data_buf[recv_len-2]==(crc_tmp/256))
							&&(uart_data_buf[recv_len-1]==(crc_tmp%256)))
					{
						printf("recive crc is ok\r\n");
						switch(uart_data_buf[3])
						{
							case WIFI_MODULE_READ :
								dooya_motor_response_handle(uart_data_buf,recv_len);
							break;
							case WIFI_MODULE_WRITE :
							break;
							case WIFI_MODULE_CONTROL :
								dooya_wifi_module_control_handle(uart_data_buf,recv_len);
							break;
							case MOTOR_RESPONSE :
								
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
	dooya_uart_lock_mutex();
	hal_uart_send(&uart_use, src, size, 1000);
	dooya_uart_unlock_mutex();
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


void dooya_wifi_status_uart( uint8_t data)
{
	dooya_wifi_module_control_smartconfig(data);
}



