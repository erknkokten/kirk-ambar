#include "object_control.h"

static Obj_Error_Code getObjectLength(Obj_control_t* control){
    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if(object->nof_SubIndex == 0U){
        control->obj_arg.length = object->length;
    }
    else if (object->nof_SubIndex < control->obj_arg.subIndex) {
        /* OUT OF BOUND */
        return OBJ_ERR_NO_SUB_INDEX;
    }
    else { /* it has subIndex, which means length is 0. Type casting is needed */
        control->obj_arg.length = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].length;
    }
    return OBJ_ERR_SUCCESS;
}

static Obj_Error_Code getObjectAttr(Obj_control_t* control){
    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if(object->nof_SubIndex == 0U){
        control->obj_arg.attr = object->attr;
    }
    else if (object->nof_SubIndex < control->obj_arg.subIndex) {
        /* OUT OF BOUND */
        return OBJ_ERR_NO_SUB_INDEX;
    }
    else { /* it has subIndex, which means attr is 0. Type casting is needed */
        control->obj_arg.attr = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].attr;
    }
    return OBJ_ERR_SUCCESS;
}

static Obj_Error_Code getObjectAddress(Obj_control_t* control){
    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;
    /* since we learned the index number of the
     * desired object from findObject(), we create a pointer to that object. */
    const Obj_index_t* object = &control->obj_index[control->obj_arg.i_element];

    if(object->nof_SubIndex == 0U){
        control->obj_arg.data = object->data;
    }
    else if (control->obj_arg.subIndex > object->nof_SubIndex) {
        return OBJ_ERR_NO_SUB_INDEX;
    }
    else {
        /* if it has subIndex, the data pointer points to subIndex.
         *  Therefore, typecasting to Obj_subIndex_t helps us */
        control->obj_arg.data = ((Obj_subIndex_t*)(object->data))[control->obj_arg.subIndex].data;
    }
    return OBJ_ERR_SUCCESS;
}

static Obj_Error_Code findObject(Obj_control_t* control){
    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;

    const Obj_index_t* indexListHead;
    uint16_t index = control->obj_arg.index;

    for(int i = 0; i < control->nof_index; i++){
        indexListHead = &control->obj_index[i];

        if(indexListHead->index == index){
            control->obj_arg.i_element = i;
            return OBJ_ERR_SUCCESS;
        }
    }
    return OBJ_ERR_NO_INDEX;
}

static Obj_Error_Code initWriteRead(Obj_control_t* control, uint16_t index, uint8_t subIndex){

    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;

    control->obj_arg.index = index;
    control->obj_arg.subIndex = subIndex;

    /*find object in index array*/
    err =findObject(control);
    if(err != OBJ_ERR_SUCCESS)
        return err;

    /* get object address to odf arg */
    err = getObjectAddress(control);
    if(err != OBJ_ERR_SUCCESS)
        return err;

    /* get object length*/
    err = getObjectLength(control);

    /* get object attribute */
    err = getObjectAttr(control);



    return OBJ_ERR_SUCCESS;
}


Obj_Error_Code obj_read( Obj_control_t* control, uint16_t index, uint8_t subIndex ){

    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;
    err = initWriteRead(control, index, subIndex);/** returns an error code*/
     if(err != OBJ_ERR_SUCCESS)
         return err;

     /*is it readable*/
     if( (control->obj_arg.attr & OBJ_READABLE) == 0 )
         return OBJ_ERR_WRITEONLY; /* ATTEMPT TO READ A WRITE-ONLY OBJ.*/

     /* start to copy data*/
     uint8_t* buffer = (uint8_t*)control->obj_arg.databuffer;
     uint8_t* Objectdata = (uint8_t*)control->obj_arg.data;
     uint8_t length = control->obj_arg.length;

     /*copy data from object to buffer*/
     if(Objectdata != 0){
         for(int i = 0; i < length; i++){
             *buffer = *Objectdata;
             buffer++;
             Objectdata++;
         }
     }
     return OBJ_ERR_SUCCESS;
}

Obj_Error_Code obj_write( Obj_control_t* control, uint16_t index, uint8_t subIndex ){

    if(control == 0 /*NULL*/)
       return OBJ_ERR_NULL_PARAM;

    Obj_Error_Code err;
    err = initWriteRead(control, index, subIndex);/** returns an error code*/
     if(err != OBJ_ERR_SUCCESS)
         return err;

     /*is it writeable*/
     if( (control->obj_arg.attr & OBJ_WRITEABLE) == 0 )
         return OBJ_ERR_READONLY; /* ATTEMPT TO WRITE A READ-ONLY OBJ.*/

     /* start to copy data*/
     uint8_t* buffer = (uint8_t*)control->obj_arg.databuffer;
     uint8_t* Objectdata = (uint8_t*)control->obj_arg.data;
     uint8_t length = control->obj_arg.length;

     /* copy data from buffer to object*/
     if(buffer!=0){
        for(int i = 0; i<length;i++){
            *Objectdata = *buffer;
            buffer++;
            Objectdata++;
        }
     }
    return OBJ_ERR_SUCCESS;
}

