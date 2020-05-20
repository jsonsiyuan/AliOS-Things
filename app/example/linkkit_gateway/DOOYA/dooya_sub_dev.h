#ifndef __DOOYA_SUB_DEV_H__
#define __DOOYA_SUB_DEV_H__

#include <stdio.h>
#include <stdint.h>

typedef struct _user_sub_dev_t{
	uint8_t enable_flag;
	uint8_t all_point;
	uint16_t index;
	uint16_t address;
	uint16_t cluse;
	/*uint8_t pro_na[12];
	uint8_t pro_se[20];
	uint8_t dev_na[40];
	uint8_t dev_se[40];*/
}user_sub_dev_t;

int dooya_all_number_change(void);
int dooya_add_sub_flash(user_sub_dev_t *data_tmp,uint8_t index);

int dooya_add_sub_pro_na(uint8_t *string_tmp,uint8_t index);
int dooya_add_sub_pro_se(uint8_t *string_tmp,uint8_t index);
int dooya_add_sub_dev_na(uint8_t *string_tmp,uint8_t index);
int dooya_add_sub_dev_se(uint8_t *string_tmp,uint8_t index);
int dooya_get_sub_dev_na(uint8_t *string_tmp,int *len,uint8_t index);

int dooya_del_sub_flash(uint8_t index);
int dooya_find_sub_from_flash(user_sub_dev_t *data_tmp,uint8_t index);

void dooya_sub_dev_init(void);
int dooya_add_sub(    uint8_t * product_key,uint8_t *product_secret,uint8_t *device_name,uint8_t *device_secret);
void dooya_zigbee_net_deal(uint8_t *payload_msg,uint8_t msg_len);

int8_t  dooya_find_sub_index_from_flash(uint8_t start);
uint8_t  dooya_find_no_sub_index_from_flash(void);
void dooya_sub_zigbee_del(int devid,int8_t index);


void dooya_zigbee_window_open(uint16_t address,uint16_t cluse);
void dooya_zigbee_window_close(uint16_t address,uint16_t cluse);
void dooya_zigbee_window_stop(uint16_t address,uint16_t cluse);
void dooya_zigbee_window_position(uint16_t address,uint16_t cluse,uint8_t data_tmp);

void dooya_sub_zigbee_number(char *data);





#endif

