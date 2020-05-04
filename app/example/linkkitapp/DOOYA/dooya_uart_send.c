#include "dooya_uart_send.h"
#include "dooya_uart.h"







void dooya_response_smartconfig(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=2;
	data_buf[5]=WIFI_MODULE_RESPONSE_SMARTCONFIG;
	data_buf[6]=data;
	crc16_tmp=qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);
}

void dooya_response_reset(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=2;
	data_buf[5]=MOTOR_SEND_RESET;
	data_buf[6]=data;
	crc16_tmp=qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);

}

void dooya_response_check_net(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=2;
	data_buf[5]=MOTOR_SEND_CHECK_NET;
	data_buf[6]=data;
	crc16_tmp=qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);

}

void dooya_response_check_time(uint8_t *data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=8;
	data_buf[5]=WIFI_MODULE_RESPONSE_CHECK_TIME;
	data_buf[6]=data[0];
	data_buf[7]=data[1];
	data_buf[8]=data[2];
	data_buf[9]=data[3];
	data_buf[10]=data[4];
	data_buf[11]=data[5];
	data_buf[12]=data[6];
	crc16_tmp=qioucrc16(dooya,data_buf,13);
	data_buf[13]=crc16_tmp%256;
	data_buf[14]=crc16_tmp/256;
	dooya_uart_send(data_buf,15);
}

void dooya_response_fac(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=2;
	data_buf[5]=MOTOR_SEND_FAC;
	data_buf[6]=data;
	crc16_tmp=qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);

}

void dooya_response_model(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=1;
	data_buf[5]=MOTOR_SEND_MODEL;
	crc16_tmp=qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_response_key(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=1;
	data_buf[5]=MOTOR_SEND_KEY;
	crc16_tmp=qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_response_secret(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=1;
	data_buf[5]=MOTOR_SEND_SECRET;
	crc16_tmp=qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_response_led(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_RESPONSE;
	data_buf[4]=2;
	data_buf[5]=MOTOR_SEND_LED_ENABLE;
	data_buf[6]=data;
	crc16_tmp=qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);

}
/**********************************************/

void dooya_control_motor_open(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_OPEN;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);
}

void dooya_control_motor_close(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_CLOSE;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}
void dooya_control_motor_stop(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_STOP;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_percent(uint8_t p_flag)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=2;
	data_buf[5]=WIFI_MODULE_SEND_PER;
	data_buf[6]=p_flag;
	crc16_tmp= qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);


}

void dooya_control_motor_point_up(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_POINT_UP_WORK;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}


void dooya_control_motor_point_down(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_POINT_DOWN_WORK;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_change_dir(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_REVERSING;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_net_work(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=2;
	data_buf[5]=WIFI_MODULE_SEND_NET_STATUS;
	data_buf[6]=data;
	crc16_tmp= qioucrc16(dooya,data_buf,7);
	data_buf[7]=crc16_tmp%256;
	data_buf[8]=crc16_tmp/256;
	dooya_uart_send(data_buf,9);

}

void dooya_control_motor_sn(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_CHECK_SN;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_motor_status(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_CHECK_MOTOR_STATUS;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_motor_fac(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_SET_FAC;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_motor_clear(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_CLEAR;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_motor_info(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_MOTOR_INFO;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_motor_up_work(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_SET_UP_WORK;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}

void dooya_control_motor_down_work(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=0x00;
	data_buf[2]=0x00;
	data_buf[3]=WIFI_MODULE_SEND;
	data_buf[4]=1;
	data_buf[5]=WIFI_MODULE_SEND_SET_DOWN_WORK;
	crc16_tmp= qioucrc16(dooya,data_buf,6);
	data_buf[6]=crc16_tmp%256;
	data_buf[7]=crc16_tmp/256;
	dooya_uart_send(data_buf,8);

}


void dooya_start_motor_check(void)
{


	dooya_control_motor_status();
	return;
}







