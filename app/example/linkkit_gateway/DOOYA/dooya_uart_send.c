#include "dooya_uart_send.h"
#include "dooya_uart.h"

void dooya_zigbee_add_sub(void)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x04;
	data[3]=NOTICE_CODE;
	data[4]=NOTICE_ZIGBEE_NET;
	crc16_tmp= CRC16_MODBUS(data,5);
	data[5]=crc16_tmp/256;
	data[6]=crc16_tmp%256;
	dooya_uart_send(data,7);


}
void dooya_zigbee_del_sub(uint16_t address)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x06;
	data[3]=NOTICE_CODE;
	data[4]=NOTICE_ZIGBEE_RESET;
	data[5]=address/256;
	data[6]=address%256;
	crc16_tmp= CRC16_MODBUS(data,7);
	data[7]=crc16_tmp/256;
	data[8]=crc16_tmp%256;
	dooya_uart_send(data,9);


}
/*地址+簇+端口+具体数据
55 aa 0d 01 00 88 f6 01 02 01 01 01 05 32 fe 8c
*/
void dooya_zigbee_send_control(uint16_t address,uint16_t cluse,uint8_t endpoint,uint8_t *data_array,uint8_t len)
{
	uint8_t data[50]={0};
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x06;
	data[3]=CONTROL_CODE;
	data[4]=0;
	data[5]=address/256;
	data[6]=address%256;
	data[7]=cluse/256;
	data[8]=cluse%256;

	data[9]=endpoint;
	memcpy(data+10,data_array,len);
	data[2]=len+9;
	crc16_tmp= CRC16_MODBUS(data,10+len);
	data[10+len]=crc16_tmp/256;
	data[11+len]=crc16_tmp%256;
	dooya_uart_send(data,12+len);


}

/**/
void dooya_zigbee_get_info(uint16_t address)
{
	uint8_t data[10];
	uint16_t crc16_tmp;
	data[0]=0x55;
	data[1]=0xAA;
	data[2]=0x06;
	data[3]=CHECK_CODE;
	data[4]=CHECK_MOTOR_INFO;
	data[5]=address/256;
	data[6]=address%256;
	crc16_tmp= CRC16_MODBUS(data,7);
	data[7]=crc16_tmp/256;
	data[8]=crc16_tmp%256;
	dooya_uart_send(data,9);


}






