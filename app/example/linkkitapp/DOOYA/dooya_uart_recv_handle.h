#ifndef __DOOYA_UART_RECV_HANDLE_H__
#define __DOOYA_UART_RECV_HANDLE_H__


#include <stdio.h>
#include <stdint.h>

void dooya_control_handle(uint8_t *payload_msg,uint8_t msg_len);
void dooya_check_handle(uint8_t *payload_msg,uint8_t msg_len);
void dooya_notice_handle(uint8_t *payload_msg,uint8_t msg_len);
void dooya_ota_handle(uint8_t *payload_msg,uint8_t msg_len);



#endif
