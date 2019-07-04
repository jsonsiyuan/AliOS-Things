#ifndef __DOOYA_UART_H__
#define __DOOYA_UART_H__

#include <stdio.h>
#include <stdint.h>
#include "aos/kernel.h"



#define dooya 0xFFFF
#define timao 0x1804


typedef enum 
{
	MOTOR_SEND=1,
	WIFI_MODULE_RESPONSE,
	WIFI_MODULE_SEND,
	MOTOR_RESPONSE,
	MAX=0XFF,
}FUNCTION_CODE_T;



/*MOTOR_REQUEST*/

#define MOTOR_SEND_SMARTCONFIG   0X01
#define MOTOR_SEND_RESET         0x02
#define MOTOR_SEND_CHECK_NET     0X03
#define MOTOR_SEND_CHECK_TIME    0x04
#define MOTOR_SEND_FAC           0X07
#define MOTOR_SEND_MODEL         0X08
#define MOTOR_SEND_KEY           0X09
#define MOTOR_SEND_SECRET        0X0A
#define MOTOR_SEND_LED_ENABLE    0X0B

/*WIFI_MODULE_RESPONSE*/
#define WIFI_MODULE_RESPONSE_SMARTCONFIG   0X01
#define WIFI_MODULE_RESPONSE_RESET         0x02
#define WIFI_MODULE_RESPONSE_CHECK_NET     0X03
#define WIFI_MODULE_RESPONSE_CHECK_TIME    0x04
#define WIFI_MODULE_RESPONSE_FAC           0X07
#define WIFI_MODULE_RESPONSE_MODEL         0X08
#define WIFI_MODULE_RESPONSE_KEY           0X09
#define WIFI_MODULE_RESPONSE_SECRET        0X0A
#define WIFI_MODULE_RESPONSE_LED_ENABLE    0X0B

/*WIFI_MODULE_REQUEST*/
#define WIFI_MODULE_SEND_OPEN               0X01
#define WIFI_MODULE_SEND_CLOSE              0x02
#define WIFI_MODULE_SEND_STOP               0X03
#define WIFI_MODULE_SEND_PER                0x04
#define WIFI_MODULE_SEND_POINT_UP_WORK      0X05
#define WIFI_MODULE_SEND_POINT_DOWN_WORK    0X06
#define WIFI_MODULE_SEND_REVERSING          0X07
#define WIFI_MODULE_SEND_NET_STATUS         0X08
#define WIFI_MODULE_SEND_CHECK_SN           0X09
#define WIFI_MODULE_SEND_CHECK_MOTOR_STATUS 0X0F
#define WIFI_MODULE_SEND_SET_FAC            0x11
#define WIFI_MODULE_SEND_CLEAR              0X12
#define WIFI_MODULE_SEND_MOTOR_INFO         0x13
#define WIFI_MODULE_SEND_SET_UP_WORK        0X14
#define WIFI_MODULE_SEND_SET_DOWN_WORK      0X15

/*MOTOR_RESPONSE*/
#define MOTOR_RESPONSE_MOTOR_INFO         0X01
#define MOTOR_RESPONSE_NET_STATUS         0x08
#define MOTOR_RESPONSE_CHECK_SN           0X09
#define MOTOR_RESPONSE_SET_FAC            0x11
#define MOTOR_RESPONSE_SET_UP_WORK        0x14
#define MOTOR_RESPONSE_SET_DOWN_WORK      0x15



uint8_t dooya_create_uart_thread(void);
void dooya_uart_send( uint8_t *src, uint32_t size);
unsigned int qioucrc16(unsigned int crc,unsigned char *buf,unsigned int x);
unsigned int calccrc(unsigned char crcbuf,unsigned int crc);







#endif



