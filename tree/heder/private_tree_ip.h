#ifndef _PRIVATE_TREE_STRUCT_H_
#define _PRIVATE_TREE_STRUCT_H_

#include "tree.h"


tree_iterator_t*    find_min_node_to_tree(tree_node_t* );
tree_iterator_t*    find_max_node_to_tree(tree_node_t* );

void                for_each_node_to_tree(tree_t* , tree_node_t* , tree_func_t , void** );

tree_iterator_t*    find_node_to_tree(tree_t* , tree_node_t* , tree_value_t );
void                insert_node_to_tree(tree_t* , tree_node_t** , tree_node_t** );

struct tree_node*   make_tree_node(allocator_t , tree_value_t );
void                free_tree_node(deallocator_t , struct tree_node** );

void                clear_node_to_tree(tree_t* , tree_iterator_t** , void** );


#endif // !_PRIVATE_TREE_STRUCT_H_
