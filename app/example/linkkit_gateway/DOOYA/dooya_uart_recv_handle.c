#include "dooya_uart_recv_handle.h"
#include "dooya_uart.h"

#include "dooya_fac.h"
#include "dooya_sub_dev.h"








void dooya_control_handle(uint8_t *payload_msg,uint8_t msg_len)
{

}

void dooya_check_handle(uint8_t *payload_msg,uint8_t msg_len)
{

}

void dooya_notice_handle(uint8_t *payload_msg,uint8_t msg_len)
{

	switch(payload_msg[0])
	{
		case NOTICE_MOTOR_INFO:
			printf("NOTICE_MOTOR_INFO\r\n");
			dooya_zigbee_report(payload_msg+1,msg_len-1);
		break;
		case NOTICE_ZIGBEE_NET:
			printf("NOTICE_ZIGBEE_NET\r\n");
			dooya_zigbee_net_deal(payload_msg+1,msg_len-1);
		break;
		case NOTICE_ZIGBEE_RESET:
			
		break;
		case NOTICE_TO_FAC_MODEL:
			
		break;


	}
}
void dooya_ota_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	
}








