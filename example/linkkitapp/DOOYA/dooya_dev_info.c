#include "dooya_dev_info.h"
#include "cJSON.h"
#include "dooya_uart.h"
#include "dooya_uart_send.h"



user_dev_status_t user_dev_status=
{
	.CurtainPosition=0,
	.CurtainOperation=2,
	.Error_status=0,
	.SetDir=0,
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
	dev_tmp->CurtainOperation=data;
}

void dooya_set_dev_SetDir(SetDir_T data  )
{
	user_dev_status_t * dev_tmp=dooya_get_dev_info();
	dev_tmp->SetDir=data;
}

void dooya_set_dev_CurtainPosition(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	dev_tmp->CurtainPosition=data;
}

void dooya_set_dev_error(int data)
{
	user_dev_status_t *dev_tmp=dooya_get_dev_info();
	dev_tmp->Error_status=data;
}

//#define dev_property_json "{\"CurtainPosition\":%d,\"CurtainOperation\":%d,\"SetDir\":%d} "
#define dev_property_json "{\"CurtainPosition\":%d,\"CurtainOperation\":%d} "
void dooya_dev_property_update(char *data)
{
	sprintf(data,dev_property_json, _g_pDEVMgr->CurtainPosition,
			_g_pDEVMgr->CurtainOperation,_g_pDEVMgr->Error_status);
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
	item_CurtainPosition = cJSON_GetObjectItem(root, "CurtainPosition");
	if (item_CurtainPosition != NULL || cJSON_IsNumber(item_CurtainPosition))
	{
		printf("#######CurtainPosition is [%d]\r\n",item_CurtainPosition->valueint);
		dooya_control_percent(item_CurtainPosition->valueint); 
		//dooya_set_dev_CurtainPosition(item_CurtainPosition->valueint);

	}

	item_CurtainOperation = cJSON_GetObjectItem(root, "CurtainOperation");
	if (item_CurtainOperation != NULL || cJSON_IsNumber(item_CurtainOperation))
	{
		printf("##########CurtainOperation is [%d]\r\n",item_CurtainOperation->valueint);
		//dooya_set_dev_CurtainOperation(item_CurtainOperation->valueint);
		switch(item_CurtainOperation->valueint)
		{
			case MOTOR_CLOSE:
				dooya_control_motor_close();
			break;
			case MOTOR_OPEN:
				dooya_control_motor_open();
			break;
			case MOTOR_STOP:
				dooya_control_motor_stop();
			break;
			
		}


	}

	item_SetDir = cJSON_GetObjectItem(root, "SetDir");
	if (item_SetDir != NULL || cJSON_IsNumber(item_SetDir))
	{
		printf("SetDir is [%d]\r\n",item_SetDir->valueint);
		dooya_set_dev_SetDir(item_SetDir->valueint);
		switch(item_SetDir->valueint)
		{
			case DIR_POSITIVE:
				//dooya_control_positine_dir();
			break;
			case DIR_REVERSE:
				//dooya_control_reverse_dir();
			break;
			
		}


	}

	
	cJSON_Delete(root);
}


