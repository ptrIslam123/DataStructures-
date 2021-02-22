#include "heder/private_tree_ip.h"




void                
for_each_node_to_tree(tree_node_t* root, tree_func_t do_something)
{
    if (root == NULL)
        return;
    
    for_each_node_to_tree(root->left_node, do_something);

    do_something(root);
    
    for_each_node_to_tree(root->right_node, do_something);
}


tree_iterator_t*    
find_node_to_tree(tree_t* tree, tree_node_t* root, tree_value_t data)
{
    if (root == NULL)
        return NULL;

    else if (tree->is_eq(root->data, data))
        return root;

    else
    {
        if (tree->is_gt(root->data, data))
            return find_node_to_tree(tree, root->left_node, data);

        else return find_node_to_tree(tree, root->right_node, data);
    }
}

void                
insert_node_to_tree(tree_t* tree, tree_node_t** root, tree_node_t* new_node)
{
    if (*root == NULL)
    {
        *root                = new_node;
        new_node->parent    = (*root)->parent;

        tree->size_tree++;
    }
    else
    {
        if (tree->is_gt((*root)->data, new_node->data))
        {
            insert_node_to_tree(tree, &(*root)->left_node, new_node);
        }
        else 
        {
            insert_node_to_tree(tree, &(*root)->right_node, new_node);
        }
    }
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




void                
free_tree(tree_node_t* root)
{

}