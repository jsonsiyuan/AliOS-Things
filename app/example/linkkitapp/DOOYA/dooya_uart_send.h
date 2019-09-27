#ifndef __DOOYA_UART_SEND_H__
#define __DOOYA_UART_SEND_H__

#include <stdint.h>

void dooya_wifi_module_control_open(void);
void dooya_wifi_module_control_close(void);
void dooya_wifi_module_control_stop(void);
void dooya_wifi_module_control_position(uint8_t data);
void dooya_wifi_module_control_smartconfig(uint8_t data);
void dooya_wifi_module_control_stroke(void);
void dooya_wifi_module_control_factory(void);
void dooya_wifi_module_write_direction(uint8_t data);
void dooya_wifi_module_read_status(void);
void dooya_start_motor_check(void);







#endif



