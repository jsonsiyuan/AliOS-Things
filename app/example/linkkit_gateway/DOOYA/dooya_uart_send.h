#ifndef __DOOYA_UART_SEND_H__
#define __DOOYA_UART_SEND_H__

#include <stdint.h>

void dooya_zigbee_add_sub(void);
void dooya_zigbee_del_sub(uint16_t address);
void dooya_zigbee_send_control(uint16_t address,uint16_t cluse,uint8_t endpoint,uint8_t *data_array,uint8_t len);
void dooya_zigbee_get_info(uint16_t address);




#endif



