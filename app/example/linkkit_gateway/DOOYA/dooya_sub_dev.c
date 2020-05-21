#include "dooya_sub_dev.h"
#include "aos/kernel.h"
#include "aos/kv.h"
#include "dooya_uart_send.h"
#include "cJSON.h"


#include "iot_export.h"
#include "iot_import.h"


#define data_len 16

uint8_t   all_number=0;
uint16_t  number_bit_flag=0;




#define dooya_sub_kv "dev_nv_%d"

#define dooya_pro_na "pro_na_%d"
#define dooya_pro_se "pro_se_%d"
#define dooya_dev_na "dev_na_%d"
#define dooya_dev_se "dev_se_%d"
uint8_t ali_tree_array[50]={0};



#define dooya_sub_all_member_kv "dev_nv_all_number"


int dooya_all_number_change(void)
{
	return aos_kv_set(dooya_sub_all_member_kv, (void *)&all_number, sizeof(uint8_t),1);
}
int dooya_add_sub_flash(user_sub_dev_t *data_tmp,uint8_t index)
{
	uint8_t kv_string[20]={0};
	sprintf(kv_string,dooya_sub_kv,index);
	printf("###########kv_string %s\r\n",kv_string);
	return aos_kv_set(kv_string, (void *)data_tmp, sizeof(user_sub_dev_t),1);
}
int dooya_add_sub_pro_na(uint8_t *string_tmp,uint8_t index)
{
	uint8_t kv_string[20]={0};
	sprintf(kv_string,dooya_pro_na,index);
	printf("###########kv_string %s\r\n",kv_string);
	return aos_kv_set(kv_string, (void *)string_tmp, strlen(string_tmp),1);
}
int dooya_add_sub_pro_se(uint8_t *string_tmp,uint8_t index)
{
	uint8_t kv_string[20]={0};
	sprintf(kv_string,dooya_pro_se,index);
	printf("###########kv_string %s\r\n",kv_string);
	return aos_kv_set(kv_string, (void *)string_tmp, strlen(string_tmp),1);
}
int dooya_add_sub_dev_na(uint8_t *string_tmp,uint8_t index)
{
	uint8_t kv_string[20]={0};
	sprintf(kv_string,dooya_dev_na,index);
	printf("###########kv_string %s\r\n",kv_string);
	return aos_kv_set(kv_string, (void *)string_tmp, strlen(string_tmp),1);
}
int dooya_add_sub_dev_se(uint8_t *string_tmp,uint8_t index)
{
	uint8_t kv_string[20]={0};
	sprintf(kv_string,dooya_dev_se,index);
	printf("###########kv_string %s\r\n",kv_string);
	return aos_kv_set(kv_string, (void *)string_tmp, strlen(string_tmp),1);
}

int dooya_get_sub_dev_na(uint8_t *string_tmp,int *len,uint8_t index)
{
	uint8_t kv_string[20]={0};
	sprintf(kv_string,dooya_dev_na,index);
	printf("###########kv_string %s\r\n",kv_string);
	return aos_kv_get(kv_string, (void *)string_tmp, &len);
}


int dooya_del_sub_all(void)
{
	uint8_t i;
	for(i=0;i<data_len;i++)
	{
		dooya_del_sub_flash( i);
	}
	all_number=0;
	dooya_all_number_change();

}

int dooya_del_sub_flash(uint8_t index)
{
	uint8_t kv_string[20]={0};
	
	memset(kv_string,0,sizeof(kv_string));
	sprintf(kv_string,dooya_sub_kv,index);
	aos_kv_del(kv_string);

	memset(kv_string,0,sizeof(kv_string));
	sprintf(kv_string,dooya_pro_na,index);
	aos_kv_del(kv_string);

	memset(kv_string,0,sizeof(kv_string));
	sprintf(kv_string,dooya_pro_se,index);
	aos_kv_del(kv_string);

	memset(kv_string,0,sizeof(kv_string));
	sprintf(kv_string,dooya_dev_na,index);
	aos_kv_del(kv_string);

	memset(kv_string,0,sizeof(kv_string));
	sprintf(kv_string,dooya_dev_se,index);
	aos_kv_del(kv_string);
	
}

int dooya_find_sub_from_flash(user_sub_dev_t *data_tmp,uint8_t index)
{
	uint8_t kv_string[20]={0};
	int len=sizeof(user_sub_dev_t);
	sprintf(kv_string,dooya_sub_kv,index);
	
	return aos_kv_get(kv_string, (void *)data_tmp, &len);
}

void dooya_sub_dev_init_mini(void)
{
	int ret=1;
	int len= sizeof(uint8_t);
	ret=aos_kv_get(dooya_sub_all_member_kv, (void *)&all_number, &len);
	printf("###########number_bit_flag1 0x%x\r\n",number_bit_flag);
}


void dooya_sub_dev_init(void)
{
	int ret=1;
	uint8_t kv_array_tmp[30]={0};
	uint8_t i=0;
	user_sub_dev_t data_tmp;
	iotx_linkkit_dev_meta_info_t ali_tmp;
	int len= sizeof(uint8_t);
	uint8_t all_number_tmp;

	int index_tmp;
		
	ret=aos_kv_get(dooya_sub_all_member_kv, (void *)&all_number, &len);
	all_number_tmp=all_number;
	number_bit_flag=0;
	printf("###########number_bit_flag1 0x%x\r\n",number_bit_flag);
	if(0==ret)
	{
		printf("###########all_number %d\r\n",all_number_tmp);
		while(all_number_tmp>0)
		{
			memset(kv_array_tmp,0,sizeof(kv_array_tmp));
			sprintf(kv_array_tmp,dooya_sub_kv,i);
			printf("###########dooya_sub_dev_init %s\r\n",kv_array_tmp);
			ret=1;
			memset(&data_tmp,0,sizeof(data_tmp));
			len= sizeof(user_sub_dev_t);
			ret=aos_kv_get(kv_array_tmp, (void *)&data_tmp, &len);
			

			if(0==ret)
			{
				
				if(data_tmp.enable_flag==1)
				{
					all_number_tmp--;
					number_bit_flag|=(1<<i);
					printf("data_tmp.address is 0x%x,data_tmp.all_point is 0x%x ,data_tmp.cluse is 0x%x,data_tmp.index is 0x%x\r\n",
						data_tmp.address,data_tmp.all_point,data_tmp.cluse,data_tmp.index);

					//上电注册
					//pro_na
					memset(kv_array_tmp,0,sizeof(kv_array_tmp));
					memset(ali_tmp.product_key,0,sizeof(ali_tmp.product_key));
					sprintf(kv_array_tmp,dooya_pro_na,i);
					len=sizeof(ali_tmp.product_key);
					aos_kv_get(kv_array_tmp, (void *)ali_tmp.product_key, &len);

					printf("###########product_key %s\r\n",ali_tmp.product_key);
					//pro_se
					memset(kv_array_tmp,0,sizeof(kv_array_tmp));
					memset(ali_tmp.product_secret,0,sizeof(ali_tmp.product_secret));
					sprintf(kv_array_tmp,dooya_pro_se,i);
					len=sizeof(ali_tmp.product_secret);
					aos_kv_get(kv_array_tmp, (void *)ali_tmp.product_secret, &len);
					printf("###########product_secret %s\r\n",ali_tmp.product_secret);

					//dev_na
					memset(kv_array_tmp,0,sizeof(kv_array_tmp));
					memset(ali_tmp.device_name,0,sizeof(ali_tmp.device_name));
					sprintf(kv_array_tmp,dooya_dev_na,i);
					len=sizeof(ali_tmp.device_name);
					aos_kv_get(kv_array_tmp, (void *)ali_tmp.device_name, &len);
				

					//dev_se
					memset(kv_array_tmp,0,sizeof(kv_array_tmp));
					memset(ali_tmp.device_secret,0,sizeof(ali_tmp.device_secret));
					sprintf(kv_array_tmp,dooya_dev_se,i);
					len=sizeof(ali_tmp.device_secret);
					aos_kv_get(kv_array_tmp, (void *)ali_tmp.device_secret, &len);

					index_tmp=example_add_subdev(&ali_tmp);
					
					if(index_tmp !=-1)
					{
						data_tmp.index=ret;
						dooya_add_sub_flash(&data_tmp,i);
					}
					
				}
			}
			printf("###########number_bit_flag 0x%x\r\n",number_bit_flag);
			i++;
			if(i>data_len)
			{
				return ;
			}
		}
	}
	else
	{
		all_number=0;
		dooya_all_number_change();
		printf("###########all_number fail\r\n");
	}
}
extern int example_add_subdev(iotx_linkkit_dev_meta_info_t *meta_info);

int dooya_add_sub(    uint8_t * product_key,uint8_t *product_secret,uint8_t *device_name,uint8_t *device_secret)
{
	int ret;
	iotx_linkkit_dev_meta_info_t subdevArr_tmp={0};
	memcpy(subdevArr_tmp.product_key,product_key,11);
	memcpy(subdevArr_tmp.product_secret,product_secret,16);
	memcpy(subdevArr_tmp.device_name,device_name,20);
	memcpy(subdevArr_tmp.device_secret,device_secret,32);

	return example_add_subdev(&subdevArr_tmp);

	
	
}


uint8_t  dooya_find_no_sub_index_from_flash(void)
{
	uint8_t i;
	uint64_t  number_bit_flag_tmp=0;
	for(i=0;i<data_len;i++)
	{
		number_bit_flag_tmp=0;
		number_bit_flag_tmp |=(1<<i);	
		if((number_bit_flag_tmp&number_bit_flag)==0)
		{
			return i;
		}
	}
	return i;
	
}
int8_t  dooya_find_sub_index_from_flash(uint8_t start)
{
	uint8_t i;
	uint16_t  number_bit_flag_tmp=0;
	uint16_t  number_bit_flag_tmp1=0;
	if(start<data_len)
	{
	

		number_bit_flag_tmp=number_bit_flag>>start;
		
		

		if(number_bit_flag_tmp)
		{
			for(i=0+start;i<data_len;i++)
			{
				number_bit_flag_tmp1=0;
				number_bit_flag_tmp1 |=(1<<i);
				
				if(number_bit_flag_tmp1&number_bit_flag_tmp)
				{
					return i;
				}
			}
		}

	}


	return -1;
	

	
}


/*地址+簇+端口总数+三元组*/

void dooya_zigbee_net_deal(uint8_t *payload_msg,uint8_t msg_len)
{
	int ret;
	user_sub_dev_t data_tmp;
	uint8_t index_tmp=0;
	int len;
	memset(&data_tmp,0,sizeof(user_sub_dev_t));

	data_tmp.address=payload_msg[0]*256+payload_msg[1];
	data_tmp.cluse=payload_msg[2]*256+payload_msg[3];
	data_tmp.all_point=payload_msg[4];
	/****/
     // Add next subdev 
    ret= dooya_add_sub(payload_msg+5,payload_msg+16,payload_msg+32,payload_msg+52);
	if(ret !=-1)
	{
		//data_tmp.index=1;
		data_tmp.index=ret;
		data_tmp.enable_flag=1;
		
		len=sizeof(uint8_t);
		aos_kv_get(dooya_sub_all_member_kv, (void *)&all_number, &len);
		all_number++;
		printf("all_number is [%d]\r\n",all_number);
		dooya_all_number_change();
		
		index_tmp=dooya_find_no_sub_index_from_flash();
		
		printf("dooya_zigbee_net_deal index_tmp is [%d]\r\n",index_tmp);
		ret=dooya_add_sub_flash(&data_tmp,index_tmp);
		printf("dooya_zigbee_net_deal ret is [%d]\r\n",ret);

		memset(ali_tree_array,0,sizeof(ali_tree_array));
		memcpy(ali_tree_array,payload_msg+5,11);
		dooya_add_sub_pro_na(ali_tree_array, index_tmp);

		memset(ali_tree_array,0,sizeof(ali_tree_array));
		memcpy(ali_tree_array,payload_msg+16,16);
		dooya_add_sub_pro_se(ali_tree_array, index_tmp);

		memset(ali_tree_array,0,sizeof(ali_tree_array));
		memcpy(ali_tree_array,payload_msg+32,20);
		dooya_add_sub_dev_na(ali_tree_array, index_tmp);

		memset(ali_tree_array,0,sizeof(ali_tree_array));
		memcpy(ali_tree_array,payload_msg+52,32);
		dooya_add_sub_dev_se(ali_tree_array, index_tmp);
		number_bit_flag|=(1<<index_tmp);
		
		printf("dooya_zigbee_net_deal number_bit_flag is [%x]\r\n",number_bit_flag);
	}

}

/*向云端上报机制*/
/*55 AA 10 03 01 
88 F6 01 02 01 
18 62 0A 08 00 20 32 DE 25*/

uint8_t dev_Position_json[]= "{\"CurtainPosition\":%d} ";
uint8_t send_data[50];
void dooya_zigbee_report(uint8_t *payload_msg,uint8_t msg_len)
{
	uint16_t address_tmp=0;
	uint16_t cluse=0;
	uint8_t pointer=0;
	uint8_t data_tmp;
	uint8_t i;
	int8_t index_tmp;
	user_sub_dev_t data_t_tmp;
	memset(send_data,0,sizeof(send_data));
	
	address_tmp=payload_msg[0]*256+payload_msg[1];
	cluse=payload_msg[2]*256+payload_msg[3];
	pointer=payload_msg[4];
	
	if(cluse==0x0102)
	{
		/*窗*/
		data_tmp=payload_msg[11];
		printf("CurtainPosition is [%d]\r\n",data_tmp);
		sprintf(send_data,dev_Position_json,data_tmp);
		
		for(i=0;i<data_len;i++)
		{
			index_tmp=-1;
			index_tmp=dooya_find_sub_index_from_flash(i);
			printf("index_tmp is [%d]\r\n",index_tmp);
			if(index_tmp >=0)
			{
				printf("index_tmp ok\r\n",index_tmp);
				memset(&data_t_tmp,0,sizeof(user_sub_dev_t));
				dooya_find_sub_from_flash(&data_t_tmp,index_tmp);
				
				if(data_t_tmp.address==address_tmp)
				{
					printf("data_t_tmp.address==address_tmp\r\n");
					if(data_t_tmp.enable_flag)
					{
						printf("data_t_tmp.index is [%d]\r\n",data_t_tmp.index);
						
						IOT_Linkkit_Report(data_t_tmp.index, ITM_MSG_POST_PROPERTY, send_data,strlen(send_data));
						break;
					}
				}
			}
		}
		
	}
	
}



void dooya_sub_zigbee_deal(int devid,char *data)
{
	cJSON *root = NULL, *item_tmp = NULL, *item_tmp1 = NULL;
	
	uint8_t i;
	int8_t index_tmp;
	user_sub_dev_t data_t_tmp;

	root = cJSON_Parse(data);
	if (root == NULL || !cJSON_IsObject(root)) 
	{
		return ;
	}
	
	for(i=0;i<data_len;i++)
	{
		
		index_tmp=-1;
		index_tmp=dooya_find_sub_index_from_flash(i);
		printf("index_tmp is [%d]\r\n",index_tmp);
		if(index_tmp >=0)
		{
			printf("index_tmp ok\r\n",index_tmp);
			memset(&data_t_tmp,0,sizeof(user_sub_dev_t));
			dooya_find_sub_from_flash(&data_t_tmp,index_tmp);
			
			if(data_t_tmp.index==devid)
			{
				printf("data_t_tmp.address==address_tmp\r\n");
				if(data_t_tmp.enable_flag)
				{
					printf("data_t_tmp.index is [%d]\r\n",data_t_tmp.index);
					
					break;
				}
			}
		}
	}

	if(data_t_tmp.cluse==0x0102)
	{
		item_tmp = cJSON_GetObjectItem(root, "CurtainPosition");
		if (item_tmp != NULL || cJSON_IsNumber(item_tmp))
		{
			printf("#######CurtainPosition is [%d]\r\n",item_tmp->valueint);
			/*百分比*/
			dooya_zigbee_window_position( data_t_tmp.address, data_t_tmp.cluse,item_tmp->valueint);
		}

		item_tmp1 = cJSON_GetObjectItem(root, "CurtainOperation");
		if (item_tmp1 != NULL || cJSON_IsNumber(item_tmp1))
		{
			printf("#######CurtainOperation is [%d]\r\n",item_tmp1->valueint);
			switch(item_tmp1->valueint)
			{
				case 0:/*开*/
					dooya_zigbee_window_open(data_t_tmp.address, data_t_tmp.cluse);
				break;
				case 1:/*关*/
					dooya_zigbee_window_close(data_t_tmp.address, data_t_tmp.cluse);
				break;
				case 2:/*停*/
					dooya_zigbee_window_stop(data_t_tmp.address, data_t_tmp.cluse);
				break;
				
				
			}

		}
	}	
	cJSON_Delete(root);
}


void dooya_zigbee_window_open(uint16_t address,uint16_t cluse)
{
	
	uint8_t data_array_tmp[3]={0x01, 0x0F, 0x00};
	dooya_zigbee_send_control(address,cluse,1,data_array_tmp,3);
}
void dooya_zigbee_window_close(uint16_t address,uint16_t cluse)
{
	uint8_t data_array_tmp[3]={0x01, 0x0F, 0x01};
	dooya_zigbee_send_control(address,cluse,1,data_array_tmp,3);

}
void dooya_zigbee_window_stop(uint16_t address,uint16_t cluse)
{
	uint8_t data_array_tmp[3]={0x01, 0x0F, 0x02};
	dooya_zigbee_send_control(address,cluse,1,data_array_tmp,3);

}
void dooya_zigbee_window_position(uint16_t address,uint16_t cluse,uint8_t data_tmp)
{
	uint8_t data_array_tmp[4]={0x01, 0x0F, 0x05, 0x32};
	data_array_tmp[3]=data_tmp;
	dooya_zigbee_send_control(address,cluse,1,data_array_tmp,4);
}


void dooya_sub_zigbee_del(int devid,int8_t index)
{
	int len=sizeof(uint8_t);
	uint16_t number_bit_flag_tmp=1<<index;
	printf("number_bit_flag_tmp is 0x%x\r\n",number_bit_flag_tmp);
	aos_kv_get(dooya_sub_all_member_kv, (void *)&all_number, &len);
	all_number--;
	dooya_all_number_change();

	dooya_del_sub_flash(index);
	IOT_Linkkit_Close(devid);
	
	
	number_bit_flag &=(~number_bit_flag_tmp);
	
	printf("number_bit_flag2 is 0x%x\r\n",number_bit_flag);
}

void dooya_sub_zigbee_number(char *data)
{
	cJSON *root = NULL, *item_tmp = NULL, *item_tmp1 = NULL;
	
	uint8_t i,k;
	int8_t index_tmp;
	user_sub_dev_t data_t_tmp;
	int arrySize=0;
	uint8_t dev_name[20]={0};
	int len;

	
	root = cJSON_Parse(data);
	if (root == NULL || !cJSON_IsArray(root)) 
	{
		return ;
	}
	
	arrySize=cJSON_GetArraySize(root);//数组大小
	len=sizeof(uint8_t);
	aos_kv_get(dooya_sub_all_member_kv, (void *)&all_number, &len);
	printf("################dooya_sub_zigbee_number {%d}[%d]\r\n",arrySize,all_number);
	if(arrySize<all_number)
	{
		
		for(i=0;i<data_len;i++)
		{
			
			index_tmp=-1;
			index_tmp=dooya_find_sub_index_from_flash(i);
			printf("index_tmp is [%d]\r\n",index_tmp);
			


			if(index_tmp >=0)
			{
				memset(dev_name,0,sizeof(dev_name));
				len=sizeof(dev_name);
				dooya_get_sub_dev_na(dev_name,&len, index_tmp);
				printf("vn deviceName is %s\r\n",dev_name);
				if(arrySize==0)
				{
					/*删除*/
					dooya_find_sub_from_flash(&data_t_tmp,i);
							
					dooya_sub_zigbee_del(data_t_tmp.index,index_tmp);
				}
				else
				{
					for(k=0;k<arrySize;k++)

					{
						item_tmp = cJSON_GetArrayItem(root, k);
						item_tmp1 = cJSON_GetObjectItem(item_tmp, "deviceName");
						if (item_tmp1 != NULL || cJSON_IsString(item_tmp1))
						{
							printf("deviceName is %s\r\n",item_tmp1->valuestring);
							if(!strcmp(item_tmp1->string,dev_name))
							{
								break;
							}
							/*删除*/
							dooya_find_sub_from_flash(&data_t_tmp,i);
							
							dooya_sub_zigbee_del(data_t_tmp.index,index_tmp);
						}
					}
				}
			}
		}
	}


	
	/*for(k=0;k<arrySize;k++)
	{
		item_tmp = cJSON_GetArrayItem(root, k);
		item_tmp1 = cJSON_GetObjectItem(item_tmp, "deviceName");
		if (item_tmp1 != NULL || cJSON_IsString(item_tmp1))
		{
			printf("deviceName is %s\r\n",item_tmp1->valuestring);
			memset(dev_name,0,sizeof(dev_name));
			len=sizeof(dev_name);
			dooya_get_sub_dev_na(dev_name,&len, 0);
			printf("vn deviceName is %s\r\n",dev_name);
			
		}

	}*/
	cJSON_Delete(root);
}




