#include "objects.h"

Object objects = {
    {0x04, 0x00, 0x00, 0x00,0x00}, /*Led_Service, 1000*/
    {0x03, 0x00, 0x00, 0x00},     /*Pwm_Service, 1001*/
    0x100, /*value1, 1002*/
    0x200, /*value2, 1003*/
    0x50, /*value3, 2000*/
    0x10, /*value3, 2001*/
};


Obj_subIndex_t LED_Service_1000[5] = {
    { (void *)&objects.led_service.nos_index, OBJ_READABLE, 1 },
    { (void *)&objects.led_service.led1, OBJ_READABLE + OBJ_WRITEABLE , 1 },
    { (void *)&objects.led_service.led2, OBJ_READABLE + OBJ_WRITEABLE , 1 },
    { (void *)&objects.led_service.led3, OBJ_READABLE + OBJ_WRITEABLE , 1 },
    { (void *)&objects.led_service.led4, OBJ_READABLE + OBJ_WRITEABLE , 1 }

};

Obj_subIndex_t PWM_Service_1001[4] = {
    { (void *)&objects.pwm_service.nos_index, OBJ_READABLE, 1 },
    { (void *)&objects.pwm_service.ch1_duty, OBJ_READABLE + OBJ_WRITEABLE , 1 },
    { (void *)&objects.pwm_service.ch2_duty, OBJ_READABLE + OBJ_WRITEABLE , 1 },
    { (void *)&objects.pwm_service.pwm_status, OBJ_READABLE + OBJ_WRITEABLE , 2 },
};


Obj_index_t index_objects[6] = {
    { 0x1000, 0x05, 0, 0, (void*)&LED_Service_1000 },
    { 0x1001, 0x04, 0, 0, (void*)&PWM_Service_1001 },
    { 0x1002, 0, (OBJ_READABLE + OBJ_WRITEABLE), 4, (void*)&objects.value_1 },
    { 0x1003, 0, OBJ_READABLE, 4, (void*)&objects.value_2 },
    { 0x2000, 0, (OBJ_READABLE + OBJ_WRITEABLE), 2, (void*)&objects.value_3 },
    { 0x2001, 0, (OBJ_READABLE + OBJ_WRITEABLE), 1, (void*)&objects.value_4 }
};

