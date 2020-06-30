#include "dooya_uart_recv_handle.h"
#include "dooya_uart.h"
#include "dooya_dev_info.h"
#include "dooya_fac.h"



extern uint8_t dooya_CurtainPosition_data;

static void dooya_check_motor_zone_percent(uint8_t data)
{

	printf("########dooya_check_motor_zone_percent is [%d]\r\n",data);

	if(data!=0xFF)
	{
		dooya_set_dev_CurtainPosition(data);
	}
	else
	{
		dooya_set_dev_CurtainPosition(0);


	}

	

	
}
static void dooya_check_motor_zone_percent_dec(uint8_t data)
{

	printf("########dooya_check_motor_zone_percent_dec is [%d]\r\n",data);

	if(data!=0xFF)
	{
		dooya_set_dev_CurtainPosition_dec(data);
	}
	else
	{
		dooya_set_dev_CurtainPosition_dec(0);


	}

	

	
}

static void dooya_check_motor_dir(uint8_t data)
{
	printf("########dooya_check_motor_dir is [%d]\r\n",data);
	switch (data)
	{
		case 0x01:/*正*/
			dooya_set_dev_SetDir(DIR_POSITIVE);
		break;
		case 0x02:/*反*/
			dooya_set_dev_SetDir(DIR_REVERSE);
		break;


	}
	

}


static void dooya_check_motor_run_boundary(uint8_t data)
{
	//printf("########dooya_check_motor_run_boundary is [%d]\r\n",data);
	
}



static void dooya_check_motor(uint8_t data)
{
	printf("########motor_status is [%d]\r\n",data);
	switch (data)
	{
		case 0x01:/*打开*/
			dooya_set_dev_CurtainOperation(MOTOR_OPEN);
		break;
		case 0x02:/*关闭*/
			dooya_set_dev_CurtainOperation(MOTOR_CLOSE);
		break;
		case 0x03:/*暂停*/
			dooya_set_dev_CurtainOperation(MOTOR_STOP);
		break;
		
	}

}


static void dooya_control_motor(uint8_t data)
{
	printf("########motor_control is [%d]\r\n",data);
	switch (data)
	{
		case 0x01:/*打开*/
			dooya_set_dev_CurtainOperation(MOTOR_OPEN);
			dooya_set_dev_CurtainPosition_dec(100);
		break;
		case 0x02:/*关闭*/
			dooya_set_dev_CurtainOperation(MOTOR_CLOSE);
			dooya_set_dev_CurtainPosition_dec(0);
		break;
		case 0x03:/*暂停*/
			dooya_set_dev_CurtainOperation(MOTOR_STOP);
		break;
		
	}

}


void dooya_control_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[0])
	{
		case CONTROL_MOTOR_STATUS:
			dooya_control_motor(payload_msg[1]);
		break;
		
	}
}

void dooya_check_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[0])
	{
		case CHECK_MOTOR_INFO:
			dooya_check_motor(payload_msg[1]);
			dooya_check_motor_zone_percent(payload_msg[2]);
			dooya_check_motor_run_boundary(payload_msg[4]);
			//dooya_check_motor_dir(payload_msg[6]);
		break;
		case CHECK_MOTOR_STATUS:
			//dooya_check_motor(payload_msg[1]);
		break;
		case CHECK_MOTOR_ZONE_PERCENT:
			//dooya_check_motor_zone_percent(payload_msg[1]);
		break;
		case CHECK_MOTOR_ANGLE:
		break;
		case CHECK_MOTOR_RUN_BOUNDARY:
			//dooya_check_motor_run_boundary(payload_msg[1]);
		break;
		case CHECK_MOTOR_HAND_ENABLE:
		break;
		case CHECK_MOTOR_DIRECTION:
		break;
		case CHECK_LOW_SWITCH:
		break;
		case CHECK_HIGH_SWITCH:
		break;
		case CHECK_OPEN_BOUNDARY:
		break;
		case CHECK_CLOSE_BOUNDARY:
		break;
		case CHECK_THREE_RUN_BOUNDARY:
		break;
		case CHECK_MOTRO_CLASS:
		break;
		case CHECK_MOTOR_MODEL:
		break;
		case CHECK_MOTOR_VER:
		break;
		
		

		
	}
}

void dooya_notice_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[0])
	{
		case NOTICE_MOTOR_INFO:
			
			dooya_check_motor(payload_msg[1]);
			if(payload_msg[1]==0x03)
			{
				if(dooya_CurtainPosition_data!=0xff)
				{
					if(abs(dooya_CurtainPosition_data-payload_msg[2])>2)
					{
						dooya_check_motor_zone_percent_dec(payload_msg[2]);
					}
					
				}
				else
				{
					dooya_check_motor_zone_percent_dec(payload_msg[2]);
				}
				
			}
		/*	dooya_check_motor_run_boundary(payload_msg[4]);
			dooya_check_motor_dir(payload_msg[6]);
			*//*上报*/
			
		break;
		case NOTICE_TO_FAC_MODEL:
			dooya_fac_set();
		break;


	}
}
void dooya_ota_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[0])
	{
		case OTA_START:
		break;
		case OTA_END:
		break;
	}		
}








