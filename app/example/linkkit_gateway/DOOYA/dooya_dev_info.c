#include "dooya_dev_info.h"
#include "cJSON.h"
#include "dooya_uart.h"
#include "dooya_uart_send.h"
#include "aos/kv.h"
#include "netmgr.h"









void dooya_user_property_parse(char *data)
{
/*	cJSON *root = NULL, *item_CurtainPosition = NULL, *item_from_cloud = NULL;
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


	}

	item_CurtainOperation = cJSON_GetObjectItem(root, "curtainConrtol");
	if (item_CurtainOperation != NULL || cJSON_IsNumber(item_CurtainOperation))
	{



	}

	item_SetDir = cJSON_GetObjectItem(root, "mode");
	if (item_SetDir != NULL || cJSON_IsNumber(item_SetDir))
	{
		printf("mode is [%d]\r\n",item_SetDir->valueint);
		dooya_set_dev_SetDir(item_SetDir->valueint);
		switch(item_SetDir->valueint)
		{

			
		}


	}

	
	cJSON_Delete(root);*/
}



