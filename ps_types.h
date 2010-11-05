/*
 * message_type.h
 *
 *  Created on: 15/ago/2010
 *      Author: mosca
 */

#ifndef PS_TYPES_H_
#define PS_TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

#ifndef PS_DEBUG
#define PS_DEBUG
#define PS_YELLOW "\033[1;33m"
#define PS_RED "\033[31m"
#define PS_GREEN "\033[32m"

#ifdef PS_DEBUG
#define PRINT_D(format, args...)  printf(PS_YELLOW format"\033[0m\n", ##args);
#else
#define PRINT_D(format, args...)
#endif

#endif


typedef enum {
    StatusOK = 0,
    params_error = -1,
    data_type_error = -2,
    not_found = -3,
    duplicated_name = -4
} PSErrors;

//il tipo dei dati che possono essere restituiti

typedef enum {
    int_t = 0,
    char_t = 1,
    char_ptr_t = 2,
    float_t = 3
} PSTypes;

//la struttura con cui la chiamata restituirà i dati

typedef struct {
	void* data;
	PSTypes DataType;
} PSData_t;

typedef PSData_t* PSData_p;

//definisco il prototipo della funzione che dovrà fornire gli update
typedef int (*update_fun)(PSData_p data);




#endif /* PS_TYPES_H_ */

PSErrors ps_data_new(PSData_p* data);
PSErrors ps_data_init(PSData_p data);
PSErrors ps_data_new_init_fill_with_string(PSData_p *data,char *string);
PSErrors ps_data_fill_with_string(PSData_p data,char *string);
PSErrors ps_data_fill_with_int(PSData_p data,int number);