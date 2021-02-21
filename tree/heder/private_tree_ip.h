#ifndef _PRIVATE_TREE_STRUCT_H_
#define _PRIVATE_TREE_STRUCT_H_

#include "tree.h"


void                insert_node_to_tree(tree_node_t* , tree_node_t* );

struct tree_node*   make_tree_node(allocator_t , tree_value_t );
void                free_tree_node(deallocator_t , struct tree_node* );


#endif // !_PRIVATE_TREE_STRUCT_H_
