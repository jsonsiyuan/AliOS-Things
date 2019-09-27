#ifndef __DOOYA_UART_H__
#define __DOOYA_UART_H__

#include <stdio.h>
#include <stdint.h>
#include "aos/kernel.h"
#include "aos/hal/gpio.h"
#include "aos/kernel.h"

#include <aos/hal/uart.h>


#define DOOYA_UART_CRC_INIT  (0xffff)
#define DOOYA_UART_ID_L (0xFE)
#define DOOYA_UART_ID_H (0xFE)


typedef enum 
{
	WIFI_MODULE_READ=1, /*wifi模块向电机读信息*/
	WIFI_MODULE_WRITE,  /*wifi模块向电机写信息*/
	WIFI_MODULE_CONTROL,/*wifi模块向电机或者反之的控制信息*/
	MOTOR_RESPONSE,     /*电机主动上报*/
	MAX=0XFF,
}FUNCTION_CODE_T;



/*WIFI_MODULE_READ */

#define WIFI_MODULE_READ_ID_L         0X00
#define WIFI_MODULE_READ_ID_H         0x01
#define WIFI_MODULE_READ_POSITION     0X02
#define WIFI_MODULE_READ_DIRECTION    0x03
#define WIFI_MODULE_READ_HAND_ENABLE  0X04
#define WIFI_MODULE_READ_MOTOR_STATUS 0X05


/*WIFI_MODULE_WRITE*/
#define WIFI_MODULE_WRITE_DIRECTION    0x03


/*WIFI_MODULE_CONTROL*/
#define WIFI_MODULE_CONTROL_OPEN               0X01
#define WIFI_MODULE_CONTROL_CLOSE              0x02
#define WIFI_MODULE_CONTROL_STOP               0X03
#define WIFI_MODULE_CONTROL_POSITION           0x04



#define WIFI_MODULE_CONTROL_DELETE_STROKE      0X07
#define WIFI_MODULE_CONTROL_FACTORY            0X08


#define MOTOR_MODULE_CONTROL_SMARTCONFIG       0X15
#define MOTOR_MODULE_CONTROL_UNBIND            0X16


/*MOTOR_RESPONSE*/
#define MOTOR_RESPONSE_MOTOR_INFO         0X02
#define MOTOR_RESPONSE_MOTOR_ERR          0x03




uint8_t dooya_create_uart_thread(void);
void dooya_uart_send( uint8_t *src, uint32_t size);
unsigned int qioucrc16(unsigned int crc,unsigned char *buf,unsigned int x);
unsigned int calccrc(unsigned char crcbuf,unsigned int crc);


void dooya_wifi_status_uart( uint8_t data);





#endif



