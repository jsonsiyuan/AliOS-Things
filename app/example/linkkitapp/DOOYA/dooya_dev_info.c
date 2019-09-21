#include "dooya_dev_info.h"
#include "cJSON.h"
#include "dooya_uart.h"
#include "dooya_uart_send.h"
#include "aos/kv.h"
#include "netmgr.h"
#include "dooya_remout.h"
#include "dooya_flash.h"

uint8_t dooya_post_flag=1;
uint8_t dooya_post_flag_motor_status=0;

uint8_t dooya_CurtainPosition_data=0;

user_dev_status_t user_dev_status=
{
	.CurtainPosition=0,
	.CurtainOperation=MOTOR_STOP,
	.Error_status=0,
	.SetDir=DIR_POSITIVE,
};

user_dev_status_t * _g_pDEVMgr = &user_dev_status;

user_dev_status_t *  dooya_get_dev_info(void)
{
	return _g_pDEVMgr;
}

CurtainOperation_T dooya_get_dev_CurtainOperation(void  )
{
	user_dev_status_t * dev_tmp=dooya_get_dev_info();
	return dev_tmp->CurtainOperation;
}

SetDir_T dooya_get_dev_SetDir(void  )
{
	user_dev_status_t * dev_tmp=dooya_get_dev_info();
	return dev_tmp->SetDir;
}

int dooya_get_dev_CurtainPosition(void)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	return dev_tmp->CurtainPosition;
}

int dooya_get_dev_error(void)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	return dev_tmp->Error_status;
}


void dooya_set_dev_CurtainOperation(CurtainOperation_T  data)
{   
	user_dev_status_t * dev_tmp=dooya_get_dev_info();
	if(dev_tmp->CurtainOperation!=data)
	{
		if(data!=MOTOR_STOP)
		{
			dooya_post_flag=1;
		}
		else
		

		{
			dooya_post_flag_motor_status=1;
		}
		
	}
	dev_tmp->CurtainOperation=data;
}

void dooya_set_dev_SetDir(SetDir_T data  )
{
	user_dev_status_t * dev_tmp=dooya_get_dev_info();
	if(dev_tmp->SetDir!=data)
	{
		dooya_post_flag=1;
	}
	dev_tmp->SetDir=data;
}

int CurtainPosition_tmp=0;
int CurtainPosition_number=0;
void dooya_set_dev_CurtainPosition(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	if(CurtainPosition_tmp!=data)
	{
		CurtainPosition_tmp=data;
	}
	else if(CurtainPosition_tmp==data)
	{
		CurtainPosition_number++;
		if(CurtainPosition_number>1)
		{
			CurtainPosition_number=0;
			//if(dev_tmp->CurtainPosition!=data)
			if(abs(dev_tmp->CurtainPosition-data)>3)
			{
				dooya_post_flag=1;
				dooya_CurtainPosition_data=0xff;
				dev_tmp->CurtainPosition=data;
			}
			else
			{
				dooya_CurtainPosition_data=0xff;
			}


			
		}
	}
	
}
void dooya_set_dev_CurtainPosition_dec(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	if(abs(dev_tmp->CurtainPosition-data)>3)
	//if(dev_tmp->CurtainPosition!=data)
	{
		dooya_post_flag=1;
		CurtainPosition_tmp=0xff;
		dev_tmp->CurtainPosition=data;
	}
	
}

void dooya_set_dev_error(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	dev_tmp->Error_status=data;
}


#define dev_property_json "{\"curtainPosition\":%d,\"curtainConrtol\":%d} "
void dooya_dev_property_update(char *data)
{
	sprintf(data,dev_property_json, _g_pDEVMgr->CurtainPosition,
			_g_pDEVMgr->CurtainOperation);
}


#define dev_CurtainOperation_json "{\"curtainConrtol\":%d} "
void dooya_dev_property_update_motor_status(char *data)
{
	sprintf(data,dev_CurtainOperation_json,
			_g_pDEVMgr->CurtainOperation);
}


#define dev_event_json "{\"ErrorCode\":%d}" 

void dooya_dev_event_update(char *data)
{
	sprintf(data,dev_event_json, _g_pDEVMgr->Error_status);
}

void dooya_user_property_parse(char *data)
{
	cJSON *root = NULL, *item_CurtainPosition = NULL, *item_from_cloud = NULL;
	cJSON * item_CurtainOperation= NULL;
	cJSON * item_SetDir= NULL;

	root = cJSON_Parse(data);
	if (root == NULL || !cJSON_IsObject(root)) 
	{
		return ;
	}
	item_CurtainPosition = cJSON_GetObjectItem(root, "curtainPosition");
	if (item_CurtainPosition != NULL || cJSON_IsNumber(item_CurtainPosition))
	{
	
		printf("#######curtainPosition is [%d]\r\n",item_CurtainPosition->valueint);
		//dooya_set_dev_CurtainPosition_dec(item_CurtainPosition->valueint);
		//dooya_control_percent(item_CurtainPosition->valueint,0xff); 
		
		//dooya_CurtainPosition_data=item_CurtainPosition->valueint;
		if(item_CurtainPosition->valueint==100)
		{
			dooya_set_remout_data(0x02);
		}
		else if(item_CurtainPosition->valueint==0)
		{
			dooya_set_remout_data(0x08);
		}

	}

	item_CurtainOperation = cJSON_GetObjectItem(root, "curtainConrtol");
	if (item_CurtainOperation != NULL || cJSON_IsNumber(item_CurtainOperation))
	{
	
		printf("##########curtainConrtol is [%d]\r\n",item_CurtainOperation->valueint);
		
		dooya_CurtainPosition_data=0xff;

		switch(item_CurtainOperation->valueint)
		{
			case MOTOR_CLOSE:
				//dooya_control_motor_close();
				dooya_set_remout_data(0x08);
			break;
			case MOTOR_OPEN:
				//dooya_control_motor_open();
				dooya_set_remout_data(0x02);
			break;
			case MOTOR_STOP:
				//dooya_control_motor_stop();
				dooya_set_remout_data(0x04);
			break;
			
		}


	}

	item_SetDir = cJSON_GetObjectItem(root, "SetDir");
	if (item_SetDir != NULL || cJSON_IsNumber(item_SetDir))
	{
	/*
		printf("SetDir is [%d]\r\n",item_SetDir->valueint);
		//dooya_set_dev_SetDir(item_SetDir->valueint);
		switch(item_SetDir->valueint)
		{
			case DIR_POSITIVE:
				dooya_control_positine_dir();
			break;
			case DIR_REVERSE:
				dooya_control_reverse_dir();
			break;
			
		}*/


	}

	
	cJSON_Delete(root);
}



/**********************************************************************************/
#define linkkit_product_key    "linkkit_product_key"
#define linkkit_product_secret "linkkit_product_secret"

#define linkkit_device_name    "linkkit_device_name"
#define linkkit_device_secret  "linkkit_device_secret" 


#define D_PRODUCT_KEY_LEN          (11 + 1)
#define D_DEVICE_NAME_LEN          (20 + 1)
#define D_DEVICE_SECRET_LEN        (32 + 1)

static uint8_t dooya_set_product_key_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_PRODUCT_KEY_LEN;

	printf("dooya_set_product_key_info\r\n");
	res=dooya_flash_read_productkey(0,array,D_PRODUCT_KEY_LEN-1);
	if(0==res)
	{
		if(0!=strlen(array))
		{
			return 0;
		}
	}
	return 1;
}


static uint8_t dooya_set_device_name_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_DEVICE_NAME_LEN;
	res=dooya_flash_read_productkey(11,array,D_DEVICE_NAME_LEN-1);
	if(0==res)
	{
		if(0!=strlen(array))
		{
			return 0;
		}
	}
	return 1;
}

static uint8_t dooya_set_device_secret_info(uint8_t *array)
{
	uint8_t res;
	uint8_t tmp=D_DEVICE_SECRET_LEN;
	res=dooya_flash_read_productkey(31,array,D_DEVICE_SECRET_LEN-1);
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
uint8_t DEVICE_NAME[D_DEVICE_NAME_LEN]={0};
uint8_t DEVICE_SECRET[D_DEVICE_SECRET_LEN]={0};

uint8_t dooya_set_three_array_info(void)
{

	uint8_t res;
	memset(PRODUCT_KEY,0,sizeof(PRODUCT_KEY));
	memset(DEVICE_NAME,0,sizeof(DEVICE_NAME));
	memset(DEVICE_SECRET,0,sizeof(DEVICE_SECRET));

	res=1;
	res=dooya_set_product_key_info(PRODUCT_KEY);
	if(0!=res)
	{	
		return 1;
	}
	printf("\r\n  product_key is [%s]\r\n",PRODUCT_KEY);

	res=1;
	res=dooya_set_device_name_info(DEVICE_NAME);
	if(0!=res)
	{	
		return 1;
	}
	printf("\r\n  device_name is [%s]\r\n",DEVICE_NAME);


	res=1;
	res=dooya_set_device_secret_info(DEVICE_SECRET);
	if(0!=res)
	{	
		return 1;
	}
	printf("\r\n  device_secret is [%s]\r\n",DEVICE_SECRET);

	return 0;
}

uint8_t dooya_show_three_array_info(void)
{
#if 0
	uint8_t res;
	uint8_t product_key1[D_PRODUCT_KEY_LEN]={0};
	uint8_t device_name1[D_DEVICE_NAME_LEN]={0};
	uint8_t device_secret1[D_DEVICE_SECRET_LEN]={0};

	res=dooya_set_three_array_info();
	return res;
#endif
}
