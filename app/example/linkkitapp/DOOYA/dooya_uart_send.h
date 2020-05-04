#ifndef __DOOYA_UART_SEND_H__
#define __DOOYA_UART_SEND_H__

#include <stdint.h>

void dooya_response_smartconfig(uint8_t data);
void dooya_response_reset(uint8_t data);
void dooya_response_check_net(uint8_t data);
void dooya_response_check_time(uint8_t *data);
void dooya_response_fac(uint8_t data);
void dooya_response_model(void);
void dooya_response_key(void);
void dooya_response_secret(void);
void dooya_response_led(uint8_t data);

/**********************************************/

void dooya_control_motor_open(void);
void dooya_control_motor_close(void);
void dooya_control_motor_stop(void);
void dooya_control_percent(uint8_t p_flag);
void dooya_control_motor_point_up(void);
void dooya_control_motor_point_down(void);
void dooya_control_change_dir(void);
void dooya_control_net_work(uint8_t data);
void dooya_control_motor_sn(void);
void dooya_control_motor_status(void);
void dooya_control_motor_fac(void);
void dooya_control_motor_clear(void);
void dooya_control_motor_info(void);
void dooya_control_motor_up_work(void);
void dooya_control_motor_down_work(void);
void dooya_start_motor_check(void);





#endif



