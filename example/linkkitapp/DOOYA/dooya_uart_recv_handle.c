#include "dooya_uart_recv_handle.h"
#include "dooya_uart.h"
#include "dooya_dev_info.h"


extern uint8_t start_percent;
extern uint8_t start_boundary;
extern uint8_t motor_status;


static void dooya_check_motor_zone_percent(uint8_t data)
{

	printf("########motor_zone is [%d]\r\n",data);

	if(data!=0xFF)
	{
		dooya_set_dev_CurtainPosition(data);
	}
	else
	{
		dooya_set_dev_CurtainPosition(0);


	}
	start_percent=1;
	

	
}

static void dooya_check_motor_run_boundary(uint8_t data)
{
	printf("########motor_zone is [%d]\r\n",data);
	start_boundary=1;
}



static void dooya_check_motor(uint8_t data)
{
	printf("########motor_status is [%d]\r\n",data);
	switch (data)
	{
		case 0x01:/*打开*/
			dooya_set_dev_CurtainOperation(0x01);
		break;
		case 0x02:/*关闭*/
			dooya_set_dev_CurtainOperation(0x00);
		break;
		case 0x03:/*暂停*/
			dooya_set_dev_CurtainOperation(0x02);
		break;
		
	}
	motor_status=1;
}


void dooya_control_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	
}


void dooya_motor_send_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[0])
	{
		case MOTOR_SEND_SMARTCONFIG:
		break;
		case MOTOR_SEND_RESET:
		break;
		case MOTOR_SEND_CHECK_NET:
		break;
		case MOTOR_SEND_CHECK_TIME:
		break;
		case MOTOR_SEND_FAC:
		break;
		case MOTOR_SEND_MODEL:
		break;
		case MOTOR_SEND_KEY:
		break;
		case MOTOR_SEND_SECRET:
		break;
		case MOTOR_SEND_LED_ENABLE:
		break;
		
	}
}

void dooya_motor_response_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[0])
	{
		case MOTOR_RESPONSE_MOTOR_INFO:
			//dooya_check_motor(payload_msg[1]);
			//dooya_check_motor_zone_percent(payload_msg[2]);
			//dooya_check_motor_run_boundary(payload_msg[4]);
			/*上报*/
			
		break;
		case MOTOR_RESPONSE_NET_STATUS:
		break;
		case MOTOR_RESPONSE_CHECK_SN:
		break;
		case MOTOR_RESPONSE_SET_FAC:
		break;
		case MOTOR_RESPONSE_SET_UP_WORK:
		break;
		case MOTOR_RESPONSE_SET_DOWN_WORK:
		break;
	}
}









