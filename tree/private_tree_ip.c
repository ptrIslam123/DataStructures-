#include "heder/private_tree_ip.h"
#include <stdio.h>


tree_iterator_t*    
find_min_node_to_tree(tree_node_t* root)
{
    if (root->left_node == NULL)
        return root;

    return find_min_node_to_tree(root->left_node);
}


tree_iterator_t*    
find_max_node_to_tree(tree_node_t* root)
{
    if (root->right_node == NULL)
        return root;
    
    return find_max_node_to_tree(root->right_node);
}




void                
for_each_node_to_tree(tree_t* tree, tree_node_t* root, tree_func_t do_something, void** data)
{
    if (root == NULL)
        return;
    
    for_each_node_to_tree(tree, root->left_node, do_something, data);

    do_something(tree, &root, data);
    
    for_each_node_to_tree(tree, root->right_node, do_something, data);
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
        if (tree->is_more(root->data, data))
            return find_node_to_tree(tree, root->left_node, data);

        else return find_node_to_tree(tree, root->right_node, data);
    }
}

void                
insert_node_to_tree(tree_t* tree, tree_node_t** root, tree_node_t** new_node)
{
    tree_node_t* tmp_root = *root;     //  tmp root
    tree_node_t* tmp_node = *new_node; //  tmp new node

    if (tree->is_more( tmp_root->data, tmp_node->data ))
    {
        if (tmp_root->left_node != NULL)
        {
            insert_node_to_tree(tree, &tmp_root->left_node, &tmp_node);
        }
        else
        {
            tmp_root->left_node = tmp_node;
            tmp_node->parent = tmp_root;
        }
    }
    else
    {
        if (tmp_root->right_node != NULL)
        {
            insert_node_to_tree(tree, &tmp_root->right_node, &tmp_node);
        }
        else
        {
            tmp_root->right_node = tmp_node;
            tmp_node->parent = tmp_root;
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
clear_node_to_tree(tree_t* tree, tree_iterator_t** node, void** data)
{
    if (*node != NULL)
    {
        free_tree_node(tree->deallocate, node);
    }
}

inline
void                
free_tree_node(deallocator_t deallocate, struct tree_node** node)
{
    deallocate(*node);

    (*node)->right_node     = NULL;
    (*node)->left_node      = NULL;
    *node                   = NULL;
}



void                
_free_tree(tree_t* tree, tree_node_t* root)
{
    tree_node_t* left = root->left_node;
    tree_node_t* right = root->right_node;

    if (left != NULL && right != NULL)
    {
        _free_tree(tree, root->left_node);
        _free_tree(tree, root->right_node);
    }
    else if (left != NULL && right == NULL)
    {
        _free_tree(tree, root->left_node);
    }
    else if (left == NULL && right != NULL)
    {
        _free_tree(tree, root->right_node);
    }

    tree->deallocate(root);
    tree->size_tree--;
}


