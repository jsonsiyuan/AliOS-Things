#ifndef __DOOYA_UART_RECV_HANDLE_H__
#define __DOOYA_UART_RECV_HANDLE_H__


#include <stdio.h>
#include <stdint.h>


void dooya_motor_send_handle(uint8_t *payload_msg,uint8_t msg_len);
void dooya_motor_response_handle(uint8_t *payload_msg,uint8_t msg_len);


#endif
