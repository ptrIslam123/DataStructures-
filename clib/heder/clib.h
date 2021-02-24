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




typedef void* init_list_value_t;
typedef struct init_list
{
    init_list_value_t   data;
    size_t              size_data;
    size_t              size_dataa_type;

} init_list_t;

struct init_list* make_init_list(size_t size, int arg, ... );
/*
    Данный макрос позволяет эмулирует поведение шаблонов (template) c++.
    При вызове данного макроса с указанным типом генерирует находящуюся
    внутри него функции но с указанным типом вместо всех (T), а также
    вшивает в имя функции сам переданый тип данных (эмулирование декорирования имен).
    но почемуто корретно работает только для типа int (в чем проблема не знаю!).
*/
#define MAKE_INIT_LIST(T)                                               \
        struct init_list* make_init_list_##T(size_t size, T arg, ... )  \
        {                                                               \
            T* arr = malloc(sizeof(T) * size);                          \
            T* itr = &arg;                                              \
                                                                        \
            for (int i = 0; i < size; ++i, ++itr)                       \
            {                                                           \
                arr[i] = *itr;                                          \
            }                                                           \
                                                                        \
            struct init_list* list  = malloc(sizeof(init_list_t));      \
                                                                        \
            list->data              = arr;                              \
            list->size_data         = size;                             \
                                                                        \
            list->size_dataa_type   = sizeof(T);                        \
                                                                        \
            return list;                                                \
        }





int*            make_int(int );
char*           make_char(char );
float*          make_float(float );
double*         make_double(double );

#endif // !_CLIB_H_