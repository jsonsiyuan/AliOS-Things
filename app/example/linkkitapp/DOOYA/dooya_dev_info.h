#include <stdint.h>
#include <stdio.h>

#define USER_DATA_CURTAINPOSITION   "CurtainPosition"
#define USER_DATA_CURTAINOPERATION   "CurtainOperation"
#define USER_DATA_ERROR   "Error"
#define USER_DATA_SETDIR   "SetDir"



typedef enum	
{
	MOTOR_CLOSE=0,
	MOTOR_OPEN,
	MOTOR_STOP,
}CurtainOperation_T;
	
typedef enum	
{
	DIR_POSITIVE=0,
	DIR_REVERSE,

}SetDir_T;

typedef struct _user_dev_status_t{

    int CurtainPosition;
    int CurtainOperation;
    int Error_status;
    int SetDir;

}user_dev_status_t;

user_dev_status_t *  dooya_get_dev_info(void);
CurtainOperation_T dooya_get_dev_CurtainOperation(void  );
SetDir_T dooya_get_dev_SetDir(void  );
int dooya_get_dev_CurtainPosition(void);
int dooya_get_dev_error(void);
void dooya_set_dev_CurtainOperation(CurtainOperation_T           data);
void dooya_set_dev_SetDir(SetDir_T data  );
void dooya_set_dev_CurtainPosition(int data);
void dooya_set_dev_CurtainPosition_dec(int data);
void dooya_set_dev_error(int data);
void dooya_dev_property_update(char *data);
void dooya_dev_property_update_motor_status(char *data);

void dooya_dev_event_update(char *data);
void dooya_user_property_parse(char *data);

uint8_t dooya_set_three_array_info(void);
uint8_t dooya_show_three_array_info(void);


