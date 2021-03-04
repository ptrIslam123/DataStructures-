#ifndef _SET_STRUCT_H_
#define _SET_STRUCT_H_

#include <stdlib.h>

struct set;
typedef struct set set_t;
typedef void* (*allocator_t)(size_t );
typedef void (*deallocator_t)(void* );
typedef void* set_value_t;

#define SIZE_SET_STRCUT   (sizeof(struct set))
#define GET_SETV(T,V)         ((T*)V)


unsigned char       is_empty_set(set_t* );

void                swap_set(set_t* , set_t* );

void                push_to_set(set_t* , set_value_t );
set_value_t         pop_from_set(set_t* , size_t );

struct set*         make_std_set();
struct set*         make_set(allocator_t , deallocator_t );

void                free_set(struct set* );

#endif // !_SET_STRUCT_H_
