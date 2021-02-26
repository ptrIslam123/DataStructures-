#include "heder/private_avl_tree_ip.h"


tree_iterator_t*        
find_node_to_avl_tree(tree_t* tree, tree_node_t* root, tree_value_t val)
{
   if (root == NULL)
    return NULL;

    else if (tree->is_eq(root->data, val))
        return root;

    else if (tree->is_more(root->data, val))
        return find_node_to_avl_tree(tree, root->left_node, val);
    
    else return find_node_to_avl_tree(tree, root->right_node, val);
}



tree_iterator_t*        
find_max_node_to_avl_tree(tree_node_t* root)
{
    if (root->right_node != NULL)
        return find_max_node_to_avl_tree(root->right_node);

    return root;
}

tree_iterator_t*        
find_min_node_to_avl_tree(tree_node_t* root)
{
    if (root->left_node != NULL)
        return find_min_node_to_avl_tree(root->left_node);

    return root;
}


void                    
insert_node_to_avl_tree(tree_t* tree, tree_node_t** root, tree_node_t** new_node)
{
    tree_node_t* tmp_root = *root;
    tree_node_t* tmp_node = *new_node;

    if (tree->is_more(tmp_root->data, tmp_node->data))
    {
        if (tmp_root->left_node != NULL)
        {
            insert_node_to_avl_tree(tree, &(tmp_root->left_node), &tmp_node);
        }
        else
        {
            tmp_root->left_node     = tmp_node;
            tmp_node->parent        = tmp_root;
        }
    }
    else
    {
        if (tmp_root->right_node != NULL)
        {
            insert_node_to_avl_tree(tree, &(tmp_root->right_node), &tmp_node);
        }
        else
        {
            tmp_root->right_node    = tmp_node;
            tmp_node->parent        = tmp_root;
        } 
    }
}

struct avl_tree_node*   
make_avl_tree_node(allocator_t allocate, avl_tree_value_t data)
{
    avl_tree_node_t* new_node = allocate(SIZE_AVL_TREE_NODE);

    new_node->data          = data;
    new_node->left_node     = NULL;
    new_node->right_node    = NULL;
    new_node->parent        = NULL;
    new_node->height        = 0;

    return new_node;
}