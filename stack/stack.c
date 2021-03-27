#include "../list/heder/list.h"
#include "heder/stack.h"


typedef struct stack
{
    struct list* container;
} stack_t;




stack_t*            
init_stack(stack_t* stack, struct init_list* init)
{
    const size_t size       = init->size_data;
    const size_t size_type  = init->size_dataa_type;
    init_list_value_t data  = init->data;

    for (int i = 0; i < size; ++i)
    {
        push_to_stack(stack, data);
        data += size_type;
    }

    return stack;
}


inline
unsigned char       
is_empty_stack(stack_t* stack)
{
    return is_empty_list(stack->container);
}



inline
void                
swap_stack(stack_t* l, stack_t* r)
{
    swap_list(l->container, r->container);
}


inline
void                
push_to_stack(stack_t* stack, stack_value_t val)
{
    push_back_to_list(stack->container, val);
}


inline
stack_value_t       
pop_from_stack(stack_t* stack)
{
    if (is_empty_list(stack->container))
        return NULL;

    list_iterator_t* back = get_back_from_list(stack->container);
    stack_value_t   back_val = back->key;
    remove_from_list(stack->container, back);

    return back_val;
}



inline
stack_value_t       
get_top_to_stack(stack_t* stack)
{
    return get_back_from_list(stack->container)->key;
}



struct stack*       
make_std_stack()
{
    struct stack* new_stack = malloc(SIZE_STACK_STRCUT);
    new_stack->container    = make_std_list();

    return new_stack;
}


struct stack*       
make_stack(allocator_t allocate, deallocator_t deallocate)
{
    struct stack* new_stack = malloc(SIZE_STACK_STRCUT);
    new_stack->container    = make_list(allocate, deallocate);

    return new_stack;
}




inline
void                
free_stack(struct stack* pstack)
{
    free_list(pstack->container);
    free(pstack);

    pstack = NULL;
}