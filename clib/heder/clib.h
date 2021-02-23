#ifndef _CLIB_H_
#define _CLIB_H_

#include <stdlib.h>


struct part;
struct init_list;



#define SIZE_PART_STRUCT        (sizeof(struct part))
#define SIZE_INIT_LIST_STRUCT   (sizeof(struct init_list))




typedef void* value_part_t;
typedef struct part
{
    value_part_t    first;
    value_part_t    second;

} part_t;


#define GET_FIRST_PART(T, P) (T*)(P->first)
#define GET_SECOND_PART(T, P) (T*)(P->second)
struct part*    make_part(value_part_t , value_part_t );
void            free_part_struct(part_t* );




typedef void** init_list_value_t;
typedef struct init_list
{
    init_list_value_t   data;
    size_t              size_data;
    size_t              size_dataa_type;

} init_list_t;

#define GET_INIT_LISTK(T, LIST, ITER) (T*)LIST->data[ITER]
#define PRINT_INIT_LIST(T, LIST, FORMAT)                                \
            for (int i = 0; i < LIST->size_data; i++)           \
            {                                                   \
                printf(FORMAT, *GET_INIT_LISTK(T, LIST, i));    \
            }   
/*
    Данный метод может корретно с типами данных {
        int, float
    }
*/
struct init_list*   make_init_list(void* args, ... );






int*            make_int(int );
char*           make_char(char );
float*          make_float(float );
double*         make_double(double );

#endif // !_CLIB_H_