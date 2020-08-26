#ifndef OBJECTS_H
#define OBJECTS_H

#include <stdint.h>


typedef struct {
    uint8_t nos_index, led1, led2, led3, led4;
}Led_Service; /* 1000 */

typedef struct {
    uint8_t nos_index, ch1_duty, ch2_duty;
    uint16_t pwm_status;
}Pwm_Service; /* 1001 */

typedef struct{
    Led_Service led_service; /*1000*/
    Pwm_Service pwm_service; /*1001*/
    uint32_t value_1, value_2; /*1002, 1003*/
    uint16_t value_3;/* 2000*/
    uint8_t value_4;/*2001*/
}Object;


typedef struct{
    /** # of index*/
    uint16_t index;
    /** # of sub index*/
    uint8_t nof_SubIndex;
    /** attributes*/
    uint8_t attr;
    /** type: since type changes as the length of the data type changes, we use length*/
    uint16_t length;
    /** data itself, but as a memory location. if object has sub index, this will point to Obj_sub_Index_t*/
    void* data;

}Obj_index_t;

 /**
   * Bu struct eğer bir index’in sub-index
   * parametreleri var ise o index’in data pointer’ına eşitlenir.
   * */
typedef struct{
    /** data itself, but as a memory location*/
    void* data;
    /** attributes*/
    uint16_t attr;
    /** type: since type changes as the length of the data type changes, we use length*/
    uint16_t length;

}Obj_subIndex_t;

typedef enum {OBJ_WRITEABLE = 0x0001U, OBJ_READABLE = 0x0002U}obj_attr_t;


#endif // OBJECTS_H
