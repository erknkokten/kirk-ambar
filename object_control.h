#ifndef OBJECT_CONTROL_H
#define OBJECT_CONTROL_H

#include <objects.h>
#include <stdint.h>

/** Error codes of objects */
typedef enum{

    OBJ_ERR_SUCCESS = 0x0000, /** no error*/
    OBJ_ERR_NO_INDEX = 0x0002, /** index has not been founded*/
    OBJ_ERR_NO_SUB_INDEX = 0x0004, /** sub-index has not been founded*/
    OBJ_ERR_WRITEONLY = 0x0008, /** attempt to read a write only object*/
    OBJ_ERR_READONLY = 0x0010, /** attempt to write a read only object */
    OBJ_ERR_NULL_PARAM  = 0x0020, /**< 0x0020 , detect Null parameter */
}Obj_Error_Code;

/**
 * Structure for obj_arg
 * It's like an object control workspace.
 * It's filling temporarily user data and getting some functions value
*/
typedef struct{
    /** address of the object*/
    void* data;
    /** holds a copy of data or holds a data to be written*/
    const uint8_t* databuffer;
     /** Index element number in index_struct array*/
    uint16_t i_element;
    /** buradan altı bildiğimiz değerler*/
    uint16_t index; /* kullanıcıdan gelir*/
    uint8_t subIndex; /* kullanıcıdan gelir*/
    uint8_t attr;
    uint8_t length;
}Obj_arg_t;

typedef struct{
    /** Pointer to obj_index structture array */
    const Obj_index_t* obj_index;
    /** size of obj_index structurre array */
    uint8_t nof_index;
    /** Control data buffer to copy object data.
       * It must mapped obj_arg_t data buffer  */
    uint8_t databuffer[4];
    /** See #obj_arg_t */
    Obj_arg_t obj_arg;

}Obj_control_t;


Obj_Error_Code obj_read( Obj_control_t* control, uint16_t index, uint8_t subIndex );

Obj_Error_Code obj_write( Obj_control_t* control, uint16_t index, uint8_t subIndex );


#endif // OBJECT_CONTROL_H
