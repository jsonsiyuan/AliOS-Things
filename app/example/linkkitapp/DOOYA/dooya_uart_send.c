#include "dooya_uart_send.h"
#include "dooya_uart.h"




void dooya_response_fac(uint8_t rec_data,uint8_t rssi_data)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=NOTICE_CODE;
	data[4]=NOTICE_TO_FAC_MODEL;
	data[5]=rec_data;
	data[6]=rssi_data;
	crc16_tmp= CRC16_MODBUS(data,7);
	data[7]=crc16_tmp/256;
	data[8]=crc16_tmp%256;
	dooya_uart_send(data,9);


}
void dooya_control_motor_open(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_MOTOR_STATUS;
	data[5]=0x01;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}

void dooya_control_motor_close(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_MOTOR_STATUS;
	data[5]=0x02;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}
void dooya_control_motor_stop(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_MOTOR_STATUS;
	data[5]=0x03;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}

void dooya_control_percent(uint8_t p_flag,uint8_t a_flag)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x06;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_ANGLE_AND_PERCENT;
	data[5]=p_flag;
	data[6]=a_flag;
	crc16_tmp= CRC16_MODBUS(data,7);
	data[7]=crc16_tmp/256;
	data[8]=crc16_tmp%256;
	dooya_uart_send(data,9);

}


void dooya_control_positine_dir(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_DIRECTION;
	data[5]=0x01;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}
void dooya_control_reverse_dir(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_DIRECTION;
	data[5]=0x02;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}


void dooya_control_change_dir(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_DIRECTION;
	data[5]=0x03;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}


void dooya_control_del_all_boundary(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x05;
	data[3]=CONTROL_CODE;
	data[4]=CONTROL_DEL_RUN_BOUNDARY;
	data[5]=0x10;
	crc16_tmp= CRC16_MODBUS(data,6);
	data[6]=crc16_tmp/256;
	data[7]=crc16_tmp%256;
	dooya_uart_send(data,8);
}

void dooya_check_motor_status(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x04;
	data[3]=CHECK_CODE;
	data[4]=CHECK_MOTOR_STATUS;
	crc16_tmp= CRC16_MODBUS(data,5);
	data[5]=crc16_tmp/256;
	data[6]=crc16_tmp%256;
	dooya_uart_send(data,7);

}

void dooya_check_zone_percent(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x04;
	data[3]=CHECK_CODE;
	data[4]=CHECK_MOTOR_ZONE_PERCENT;
	crc16_tmp= CRC16_MODBUS(data,5);
	data[5]=crc16_tmp/256;
	data[6]=crc16_tmp%256;
	dooya_uart_send(data,7);

}

void dooya_check_run_boundary(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x04;
	data[3]=CHECK_CODE;
	data[4]=CHECK_MOTOR_RUN_BOUNDARY;
	crc16_tmp= CRC16_MODBUS(data,5);
	data[5]=crc16_tmp/256;
	data[6]=crc16_tmp%256;
	dooya_uart_send(data,7);

}

void dooya_check_all_status(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x04;
	data[3]=CHECK_CODE;
	data[4]=CHECK_MOTOR_INFO;
	crc16_tmp= CRC16_MODBUS(data,5);
	data[5]=crc16_tmp/256;
	data[6]=crc16_tmp%256;
	dooya_uart_send(data,7);

}


void dooya_start_motor_check(void)
{
	dooya_check_all_status();


	
}






