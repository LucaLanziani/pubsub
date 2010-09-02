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

#define DEBUG
#define YELLOW "\033[1;33m"
#define RED "\033[31m"
#define GREEN "\033[32m"

#ifdef DEBUG
#define PRINT_D(format, args...)  printf(YELLOW format"\033[0m\n", ##args);
#else
#define PRINT_D(format, args...)
#endif

typedef enum {
    StatusOK = 0,
    params_error = -1,
    not_found = -2,
    duplicated_name = -3
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
