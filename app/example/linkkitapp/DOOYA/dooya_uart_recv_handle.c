#include "dooya_uart_recv_handle.h"
#include "dooya_uart.h"
#include "dooya_dev_info.h"
#include "dooya_wifi_status.h"
#include "dooya_fac.h"


#include "netmgr.h"

extern uint8_t dooya_CurtainPosition_data;
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
	

	
}

static void dooya_check_motor_zone_percent_dec(uint8_t data)
{

	printf("########motor_zone is [%d]\r\n",data);

	if(data!=0xFF)
	{
		dooya_set_dev_CurtainPosition_dec(data);
	}
	else
	{
		dooya_set_dev_CurtainPosition_dec(0);


	}
	

	
}


static void dooya_check_motor_run_boundary(uint8_t data)
{
	printf("########motor_zone is [%d]\r\n",data);

}

static void dooya_check_direction(uint8_t data)
{
	printf("########dooya_check_direction is [%d]\r\n",data);
	switch (data)
	{
		case 0x00:/*正向*/
			//dooya_set_dev_SetDir( 353 );
		break;
		case 0x01:/*fan向*/
			//dooya_set_dev_SetDir(351 );
		break;
		
	}
}

static void dooya_check_motor_dec(uint8_t data)
{
	printf("########dooya_check_motor is [%d]\r\n",data);
	switch (data)
	{
		case 0x01:/*打开*/
			dooya_set_dev_CurtainOperation_dec(0x01);
		break;
		case 0x02:/*关闭*/
			dooya_set_dev_CurtainOperation_dec(0x00);
		break;
		case 0x00:/*暂停*/
			dooya_set_dev_CurtainOperation_dec(0x02);
		break;
		
	}

}


static void dooya_check_motor(uint8_t data)
{
	printf("########dooya_check_motor is [%d]\r\n",data);
	switch (data)
	{
		case 0x01:/*打开*/
			dooya_set_dev_CurtainOperation(0x01);
		break;
		case 0x02:/*关闭*/
			dooya_set_dev_CurtainOperation(0x00);
		break;
		case 0x00:/*暂停*/
			dooya_set_dev_CurtainOperation(0x02);
		break;
		
	}

}

void dooya_motor_response_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	dooya_check_motor_zone_percent(payload_msg[6]); /*当前位置（百分比）*/
	dooya_check_direction(payload_msg[7]);			/*电机默认方向*/
												    /*手拉启动使能*/
	dooya_check_motor(payload_msg[9]);              /*电机状态*/
	
}


void dooya_wifi_module_control_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[4])
	{
		case MOTOR_MODULE_CONTROL_SMARTCONFIG:
			if(msg_len==7)
			{
				dooya_set_wifi_smartconfig();
				aos_msleep(500);
				netmgr_clear_ap_config();
				aos_msleep(100);
    			HAL_Reboot();
			}
		break;
	}
	
}



void dooya_motor_self_response_handle(uint8_t *payload_msg,uint8_t msg_len)
{
	switch(payload_msg[4])
	{
		case MOTOR_RESPONSE_MOTOR_INFO:
			dooya_check_motor_dec(payload_msg[9]);   
			if(payload_msg[9]==0x00)
			{
				if(dooya_CurtainPosition_data!=0xff)
				{
					if(abs(dooya_CurtainPosition_data-payload_msg[6])>3)
					{
						dooya_CurtainPosition_data=0xff;
						dooya_check_motor_zone_percent_dec(payload_msg[6]);
					}
					
				}
				else
				{
					dooya_check_motor_zone_percent_dec(payload_msg[6]);
				}
			}
			if(payload_msg[9]==0x01)
			{
				dooya_set_dev_CurtainPosition_dec(100);
			}
			if(payload_msg[9]==0x02)
			{
				dooya_set_dev_CurtainPosition_dec(0);
			}			   
		break;
	}
	
}






