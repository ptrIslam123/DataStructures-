#ifndef _SET_STRUCT_H_
#define _SET_STRUCT_H_

#include <stdlib.h>
#include "../../clib/heder/clib.h"


struct set;
typedef struct set          set_t;
typedef void* (*allocator_t)(size_t );
typedef void (*deallocator_t)(void* );
typedef void*               set_value_t;
typedef unsigned char (*set_compare_t)(const set_value_t , const set_value_t );


#define SIZE_SET_STRCUT   (sizeof(struct set))
#define GET_SETV(T,V)         ((T*)V)


set_t*                  init_set(set_t* , struct init_list* );


unsigned char           is_empty_set(set_t* );
/* проверяет принадлежит ли элемент данному множеству */
unsigned char           in_here(set_t* , set_value_t );
size_t                  set_size(set_t* );
/* операция проверки на то 
ялвяется ли одно множество подмножеством другого множества */
unsigned char           is_sub_set(set_t* , set_t* );
/* операция для проверку  пересекаемости двух множеств*/
set_t*                  intersection_set(set_t* , set_t* , set_t* );
/* операция обьединения двух множеств */
set_t*                  union_set(set_t* , set_t* , set_t* );
/* операция разности для множеств */
set_t*                  difference_set(set_t* , set_t* , set_t* );

void                    push_to_set(set_t* , set_value_t );
set_value_t*            pop_from_set(set_t* , size_t );
void                    remove_from_set(set_t* , size_t );

void                    for_each_set(set_t* , void** );


struct set*             make_std_set(
                            set_compare_t is_eq,
                            set_compare_t is_less,
                            set_compare_t is_more
);

struct set*             make_set(
                            set_compare_t is_eq,
                            set_compare_t is_less,
                            set_compare_t is_more,
                            allocator_t , 
                            deallocator_t 
);

void                    free_set(struct set* );



unsigned char           is_eqi_set(
                            const set_value_t root, 
                            const set_value_t other
);
unsigned char           is_lessi_set(
                            const set_value_t root, 
                            const set_value_t other
);
unsigned char           is_morei_set(
                            const set_value_t root, 
                            const set_value_t other
);

#endif // !_SET_STRUCT_H_
