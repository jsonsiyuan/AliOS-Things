#include "dooya_flash.h"
#include "aos/hal/flash.h"



void dooya_use_flash_info(void)
{
	hal_logic_partition_t *dooya_flash_p;
	dooya_flash_p =hal_flash_get_info(HAL_PARTITION_PARAMETER_1);

	printf("HAL_PARTITION_CUSTOM_1	partition_description is [%s],\
			partition_start_addr is [%x],\
			partition_length is [%x]\r\n",dooya_flash_p->partition_description,
									dooya_flash_p->partition_start_addr,
									dooya_flash_p->partition_length);
}

void dooya_use_flash_read(uint32_t offset,void *data,uint32_t length)
{
	uint32_t a_tmp;
	a_tmp=offset;
	if(hal_flash_read(HAL_PARTITION_PARAMETER_1, &a_tmp,data, length))
	{
		printf("dooya_use_flash_read rror\r\n");
	}
	

}

void dooya_use_flash_erase(uint32_t offset,uint32_t length)
{
	uint32_t a_tmp;
	a_tmp=offset;
	if(hal_flash_erase(HAL_PARTITION_PARAMETER_1, a_tmp,length))
	{
		printf("dooya_use_flash_erase error \r\n");	
	}
}


void dooya_use_flash_write(uint32_t offset,void *data,uint32_t length)
{
	uint32_t a_tmp;
	a_tmp=offset;
	if(hal_flash_write(HAL_PARTITION_PARAMETER_1, &a_tmp,data, length))
	{
		printf("dooya_use_flash_write error\r\n");	
	}
}




