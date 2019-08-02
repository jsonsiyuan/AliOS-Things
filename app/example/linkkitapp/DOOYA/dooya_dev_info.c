#include "dooya_dev_info.h"
#include "cJSON.h"
#include "dooya_uart.h"
#include "dooya_uart_send.h"
#include "aos/kv.h"
#include "netmgr.h"
#include "dooya_led.h"

uint8_t dooya_post_flag=0;
user_dev_status_t user_dev_status=
{
	.Error_status=0,
	.LightSwitch=0,
};

user_dev_status_t * _g_pDEVMgr = &user_dev_status;

user_dev_status_t *  dooya_get_dev_info(void)
{
	return _g_pDEVMgr;
}

LightSwitch_T dooya_get_dev_LightSwitch(void  )
{
	user_dev_status_t * dev_tmp=dooya_get_dev_info();
	return dev_tmp->LightSwitch;
}


int dooya_get_dev_error(void)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	return dev_tmp->Error_status;
}


void dooya_set_dev_LightSwitch(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	if(dev_tmp->LightSwitch!=data)
	{
		dooya_post_flag=1;
	}
	dev_tmp->LightSwitch=data;
	dooya_set_led_r_status(data,1);
}

void dooya_set_dev_error(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	dev_tmp->Error_status=data;
}

//#define dev_property_json "{\"CurtainPosition\":%d,\"CurtainOperation\":%d,\"SetDir\":%d} "
#define dev_property_json "{\"LightSwitch\":%d} "
void dooya_dev_property_update(char *data)
{
	sprintf(data,dev_property_json, _g_pDEVMgr->LightSwitch);
}

#define dev_event_json "{\"ErrorCode\":%d}" 

void dooya_dev_event_update(char *data)
{
	sprintf(data,dev_event_json, _g_pDEVMgr->Error_status);
}

void dooya_user_property_parse(char *data)
{
	cJSON *root = NULL, *item_LightSwitch = NULL;
	root = cJSON_Parse(data);
	if (root == NULL || !cJSON_IsObject(root)) 
	{
		return ;
	}
	item_LightSwitch = cJSON_GetObjectItem(root, "LightSwitch");
	if (item_LightSwitch != NULL || cJSON_IsNumber(item_LightSwitch))
	{
		printf("#######CurtainPosition is [%d]\r\n",item_LightSwitch->valueint);
		dooya_set_dev_LightSwitch(item_LightSwitch->valueint);

	}
	cJSON_Delete(root);
}

#define linkkit_product_key    "linkkit_product_key"
#define linkkit_product_secret "linkkit_product_secret"

#define linkkit_device_name    "linkkit_device_name"
#define linkkit_device_secret  "linkkit_device_secret" 


#define D_PRODUCT_KEY_LEN          (20 + 1)
#define D_PRODUCT_SECRET_LEN       (64 + 1)
#define D_DEVICE_NAME_LEN          (32 + 1)
#define D_DEVICE_SECRET_LEN        (64 + 1)

uint8_t dooya_set_product_key_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_PRODUCT_KEY_LEN;
	res=aos_kv_get(linkkit_product_key, array, &tmp);
	if(0==res)
	{
		if(0!=strlen(array))
		{
			return 0;
		}
	}
	return 1;
}
uint8_t dooya_set_product_secret_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_PRODUCT_SECRET_LEN;
	res=aos_kv_get(linkkit_product_secret, array, &tmp);
	if(0==res)
	{
		if(0!=strlen(array))
		{
			return 0;
		}
	}
	return 1;
}
uint8_t dooya_set_device_name_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_DEVICE_NAME_LEN;
	res=aos_kv_get(linkkit_device_name, array, &tmp);
	if(0==res)
	{
		if(0!=strlen(array))
		{
			return 0;
		}
	}
	return 1;
}

uint8_t dooya_set_device_secret_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_DEVICE_SECRET_LEN;
	res=aos_kv_get(linkkit_device_secret, array, &tmp);
	if(0==res)
	{
		if(0!=strlen(array))
		{
			return 0;
		}
	}
	return 1;
}

uint8_t PRODUCT_KEY[D_PRODUCT_KEY_LEN]={0};
uint8_t PRODUCT_SECRET[D_PRODUCT_SECRET_LEN]={0};
uint8_t DEVICE_NAME[D_DEVICE_NAME_LEN]={0};
uint8_t DEVICE_SECRET[D_DEVICE_SECRET_LEN]={0};

uint8_t dooya_set_three_array_info(void)
{

	uint8_t res;
	memset(PRODUCT_KEY,0,sizeof(PRODUCT_KEY));
	memset(PRODUCT_SECRET,0,sizeof(PRODUCT_SECRET));
	memset(DEVICE_NAME,0,sizeof(DEVICE_NAME));
	memset(DEVICE_SECRET,0,sizeof(DEVICE_SECRET));

	res=1;
	res=dooya_set_product_key_info(PRODUCT_KEY);
	if(0!=res)
	{	
		return 1;
	}
	printf("\r\n dooya_set_three_array_info product_key is [%s]\r\n",PRODUCT_KEY);

	res=1;
	res=dooya_set_product_secret_info(PRODUCT_SECRET);
	if(0!=res)
	{	
		return 1;
	}	
	printf("\r\n dooya_set_three_array_info product_secret is [%s]\r\n",PRODUCT_SECRET);

	res=1;
	res=dooya_set_device_name_info(DEVICE_NAME);
	if(0!=res)
	{	
		return 1;
	}
	printf("\r\n dooya_set_three_array_info device_name is [%s]\r\n",DEVICE_NAME);


	res=1;
	res=dooya_set_device_secret_info(DEVICE_SECRET);
	if(0!=res)
	{	
		return 1;
	}
	printf("\r\n dooya_set_three_array_info device_secret is [%s]\r\n",DEVICE_SECRET);

	return 0;
}

uint8_t dooya_show_three_array_info(void)
{

	uint8_t res;
	uint8_t product_key1[D_PRODUCT_KEY_LEN]={0};
	uint8_t product_secret1[D_PRODUCT_SECRET_LEN]={0};
	uint8_t device_name1[D_DEVICE_NAME_LEN]={0};
	uint8_t device_secret1[D_DEVICE_SECRET_LEN]={0};

	res=dooya_set_three_array_info();
	return res;
}
