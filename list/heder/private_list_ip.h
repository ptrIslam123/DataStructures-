#ifndef _PRIVATE_LIST_IP_H_
#define _PRIVATE_LIST_IP_H_

#include "list.h"

struct node*    make_node(allocator_t , value_t );
void            free_node(deallocator_t , struct node* );

void            free_list_struct(struct list* );
void            clear_list(struct list* );

#endif // !_PRIVATE_LIST_IP_H_
