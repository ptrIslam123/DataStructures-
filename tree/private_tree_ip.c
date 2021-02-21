#include "heder/private_tree_ip.h"



void                
insert_node_to_tree(tree_node_t* root, tree_node_t* new_node)
{
    
}


struct tree_node* 
make_tree_node(allocator_t allocate, tree_value_t data)
{
    struct tree_node* new_node = allocate(SIZE_TREE_NODE);

    new_node->data              = data;
    new_node->left_node         = NULL;
    new_node->right_node        = NULL;
    new_node->parent            = NULL;

    return new_node;
}



void                
free_tree_node(deallocator_t deallocate, struct tree_node* node)
{
    deallocate(node);
}
