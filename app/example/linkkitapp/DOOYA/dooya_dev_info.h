#include <stdint.h>
#include <stdio.h>

#define USER_DATA_CURTAINPOSITION   "CurtainPosition"
#define USER_DATA_CURTAINOPERATION   "CurtainOperation"
#define USER_DATA_ERROR   "Error"
#define USER_DATA_SETDIR   "SetDir"



typedef enum	
{
	LIGHT_CLOSE=0,
	LIGHT_OPEN,
}LightSwitch_T;
	
typedef struct _user_dev_status_t{


    int Error_status;
	int LightSwitch;

}user_dev_status_t;

user_dev_status_t *  dooya_get_dev_info(void);

LightSwitch_T dooya_get_dev_LightSwitch(void  );
int dooya_get_dev_error(void);
void dooya_set_dev_LightSwitch(int data);
void dooya_set_dev_error(int data);


void dooya_dev_property_update(char *data);
void dooya_dev_event_update(char *data);
void dooya_user_property_parse(char *data);

uint8_t dooya_set_three_array_info(void);
uint8_t dooya_show_three_array_info(void);


