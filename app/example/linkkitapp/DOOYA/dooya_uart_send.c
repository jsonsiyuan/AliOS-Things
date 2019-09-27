#include "dooya_uart_send.h"
#include "dooya_uart.h"


void dooya_wifi_module_control_open(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL;
	data_buf[4]=WIFI_MODULE_CONTROL_OPEN;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,5);
	data_buf[5]=crc16_tmp/256;
	data_buf[6]=crc16_tmp%256;
	dooya_uart_send(data_buf,7);
}

void dooya_wifi_module_control_close(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL;
	data_buf[4]=WIFI_MODULE_CONTROL_CLOSE;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,5);
	data_buf[5]=crc16_tmp/256;
	data_buf[6]=crc16_tmp%256;
	dooya_uart_send(data_buf,7);
}

void dooya_wifi_module_control_stop(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL;
	data_buf[4]=WIFI_MODULE_CONTROL_STOP;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,5);
	data_buf[5]=crc16_tmp/256;
	data_buf[6]=crc16_tmp%256;
	dooya_uart_send(data_buf,7);
}

void dooya_wifi_module_control_position(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL; 
	data_buf[4]=WIFI_MODULE_CONTROL_POSITION;
	data_buf[5]=data;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,6);
	data_buf[6]=crc16_tmp/256;
	data_buf[7]=crc16_tmp%256;
	dooya_uart_send(data_buf,8);
}

void dooya_wifi_module_control_smartconfig(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL; 
	data_buf[4]=MOTOR_MODULE_CONTROL_SMARTCONFIG;
	data_buf[5]=data;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,6);
	data_buf[6]=crc16_tmp/256;
	data_buf[7]=crc16_tmp%256;
	dooya_uart_send(data_buf,8);
}


void dooya_wifi_module_control_stroke(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL;
	data_buf[4]=WIFI_MODULE_CONTROL_DELETE_STROKE;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,5);
	data_buf[5]=crc16_tmp/256;
	data_buf[6]=crc16_tmp%256;
	dooya_uart_send(data_buf,7);

}

void dooya_wifi_module_control_factory(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_CONTROL;
	data_buf[4]=WIFI_MODULE_CONTROL_FACTORY;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,5);
	data_buf[5]=crc16_tmp/256;
	data_buf[6]=crc16_tmp%256;
	dooya_uart_send(data_buf,7);

}

void dooya_wifi_module_write_direction(uint8_t data)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_WRITE;
	data_buf[4]=WIFI_MODULE_WRITE_DIRECTION;
	data_buf[5]=1;
	data_buf[6]=data;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,7);
	data_buf[7]=crc16_tmp/256;
	data_buf[8]=crc16_tmp%256;
	dooya_uart_send(data_buf,9);

}

void dooya_wifi_module_read_status(void)
{
	uint8_t data_buf[10];
	uint16_t crc16_tmp;
	data_buf[0]=0x55;
	data_buf[1]=DOOYA_UART_ID_L;
	data_buf[2]=DOOYA_UART_ID_H;
	data_buf[3]=WIFI_MODULE_READ;
	data_buf[4]=WIFI_MODULE_READ_POSITION;
	data_buf[5]=4;
	crc16_tmp= qioucrc16(DOOYA_UART_CRC_INIT,data_buf,6);
	data_buf[6]=crc16_tmp/256;
	data_buf[7]=crc16_tmp%256;
	dooya_uart_send(data_buf,8);

}



void dooya_start_motor_check(void)
{
	dooya_wifi_module_read_status();
}







