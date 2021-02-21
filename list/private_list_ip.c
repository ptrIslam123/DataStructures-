#include "heder/private_list_ip.h"

struct node*    
make_node(allocator_t allocate, value_t k)
{
    struct node* new_node = allocate(SIZE_STRUCT_NODE);

    new_node->next_node = NULL;
    new_node->next_node = NULL;
    new_node->key       = k;

    return new_node;
}


inline
void            
free_node(deallocator_t deallocate, struct node* in)
{
    deallocate(in);
    in = NULL;
}




inline
void            
free_list_struct(struct list* list)
{
    list->deallocate(list);
    list = NULL;
}



void            
clear_list(struct list* list)
{
    while (list->begin != NULL)
    {
        pop_front_from_list(list);
    }
}
