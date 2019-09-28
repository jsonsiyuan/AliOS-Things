#ifndef __DOOYA_UART_SEND_H__
#define __DOOYA_UART_SEND_H__

#include <stdint.h>


void dooya_response_fac(uint8_t ret,int8_t rssi,uint32_t address);
void dooya_control_motor_open(void);
void dooya_control_motor_close(void);
void dooya_control_motor_stop(void);
void dooya_control_percent(uint8_t p_flag,uint8_t a_flag);

void dooya_control_positine_dir(void);
void dooya_control_reverse_dir(void);
void dooya_control_change_dir(void);

void dooya_control_del_all_boundary(void);

void dooya_check_motor_status(void);
void dooya_check_zone_percent(void);
void dooya_check_run_boundary(void);

void dooya_start_motor_check(void);



#endif



