#ifndef __DOOYA_UART_H__
#define __DOOYA_UART_H__

#include <stdio.h>
#include <stdint.h>
#include "aos/kernel.h"
#include "aos/hal/gpio.h"
#include "aos/kernel.h"

#include <aos/hal/uart.h>

#define UUID 0x0926


typedef enum 
{
	CONTROL_CODE=1,
	CHECK_CODE,
	NOTICE_CODE,
	OTA=0X10,
}FUNCTION_CODE_T;

/*CONTROL COMMAND*/
#define CONTROL_MOTOR_STATUS        0X01
#define CONTROL_ANGLE_AND_PERCENT   0x02
#define CONTROL_HAND_ENABLE         0X03
#define CONTROL_DIRECTION           0x04
#define CONTROL_LOW_SWITCH_MODE     0X05
#define CONTROL_HIGH_SWITCH_MODE    0X06
#define CONTROL_HAND_OPEN_BOUNDARY  0X07
#define CONTROL_HAND_CLOSE_BOUNDARY 0X08
#define CONTROL_SET_RUN_BOUNDARY    0X09
#define CONTROL_SET_RUN_POINT       0X0A
#define CONTROL_DEL_RUN_BOUNDARY    0X0B
#define CONTROL_CONTINUOUS_COMMAND  0X0C
#define CONTROL_SET_ANGLE_NUMBLE    0X0D
#define CONTROL_COPY_RUN_BOUNDARY   0X0E
#define CONTROL_PASTE_RUN_BOUNDARY  0X0F
#define CONTROL_RESET				0XF0

/*CHECK CODE*/

#define CHECK_MOTOR_INFO            0X00
#define CHECK_MOTOR_STATUS          0X01
#define CHECK_MOTOR_ZONE_PERCENT    0X02
#define CHECK_MOTOR_ANGLE           0X03
#define CHECK_MOTOR_RUN_BOUNDARY    0X04
#define CHECK_MOTOR_HAND_ENABLE     0X05
#define CHECK_MOTOR_DIRECTION       0X06
#define CHECK_LOW_SWITCH            0X07
#define CHECK_HIGH_SWITCH           0X08
#define CHECK_OPEN_BOUNDARY         0X09
#define CHECK_CLOSE_BOUNDARY        0X0A
#define CHECK_THREE_RUN_BOUNDARY    0X0B
#define CHECK_MOTRO_CLASS           0XF0
#define CHECK_MOTOR_MODEL           0XF1
#define CHECK_MOTOR_VER             0XF2

/*NOTICE_CODE*/

#define NOTICE_MOTOR_INFO           0x01
/*OTA*/
#define OTA_START                   0X01
#define OTA_SEND                    0x02
#define OTA_END                     0X03






uint8_t dooya_create_uart_thread(void);
void dooya_uart_send( uint8_t *src, uint32_t size);
uint16_t CRC16_MODBUS(uint8_t *puchMsg, uint16_t usDataLen);

#endif



