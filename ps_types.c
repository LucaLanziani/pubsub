/*
 * publisher_list.c
 *
 *  Created on: 15/ago/2010
 *      Author: mosca
 */

#include "ps_types.h"

PSErrors ps_data_new(PSData_p* d_p) {
    if (d_p==NULL) return params_error;
    *d_p=(PSData_p)calloc(1,sizeof(PSData_t));
    return StatusOK;
};

PSErrors ps_data_init(PSData_p d) {
    if (d==NULL) return params_error;
    d->data=NULL;
    return StatusOK;
};



PSErrors ps_data_new_init_fill_with_string(PSData_p *data,char *string) {
    PSData_p temp_d;
    PSErrors result;
    if ((result=ps_data_new(&temp_d))!=StatusOK) return result;
    if ((result=ps_data_init(temp_d))!=StatusOK) return result;
    if (data!=NULL) *data=temp_d;
    return ps_data_fill_with_string(temp_d,string);
};

PSErrors ps_data_fill_with_string(PSData_p data,char *string) {
	if ((data==NULL) || (string==NULL)) return params_error;
	data->DataType=char_ptr_t;
	data->data=(void *)calloc(strlen(string),sizeof(char));
        return StatusOK;
};
PSErrors ps_data_fill_with_int(PSData_p data,int number);
	
