#ifndef _STACK_STRUCT_H_
#define _STACK_STRUCT_H_

#include <stdlib.h>
#include "../../clib/heder/clib.h"

struct stack;
typedef struct stack stack_t;
typedef void* (*allocator_t)(size_t );
typedef void (*deallocator_t)(void* );
typedef void* stack_value_t;

#define SIZE_STACK_STRCUT   (sizeof(struct stack))
#define GET_SV(T,V)         ((T*)V)


stack_t*            init_stack(stack_t* stack, struct init_list* init);


unsigned char       is_empty_stack(stack_t* );

void                swap_stack(stack_t* , stack_t* );

void                push_to_stack(stack_t* , stack_value_t );
stack_value_t       pop_from_stack(stack_t* );

stack_value_t       get_top_to_stack(stack_t* );

struct stack*       make_std_stack();
struct stack*       make_stack(allocator_t , deallocator_t );

void                free_stack(struct stack* );


#endif // !_STACK_STRUCT_H_