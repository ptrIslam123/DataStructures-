#include <stdio.h>
#include "heder/private_avl_tree_ip.h"



inline
height_t                
get_height_node(tree_node_t* node)
{
     if (node == NULL)
        return 0;
    return node->height;
}
  



void                
eval_height(tree_node_t* node)
{
    height_t left_h = get_height_node(node->left_node);
    height_t right_h= get_height_node(node->right_node);

    node->height = (left_h > right_h ? left_h : right_h) + 1;
}


inline
balance_t           
balance_check_to_node(tree_node_t* root)
{
    return get_height_node(root->right_node) 
            - get_height_node(root->left_node);
}




void                    
for_each_node_to_avl_tree(
    tree_t*         tree, 
    tree_node_t**   root, 
    tree_func_t     do_something, 
    void**          data
)
{
    tree_node_t* node = *root;

    if (node == NULL)
        return;
    
    for_each_node_to_avl_tree(tree, &(node->left_node), 
                        do_something, data);
    
    do_something(tree, &node, data);

    for_each_node_to_avl_tree(tree, &(node->right_node), 
                        do_something, data);
}



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




tree_node_t*                    
smal_left_rotation(tree_node_t* y)
{
    tree_node_t* x  = y->right_node;
    y->right_node   = x->left_node;
    x->left_node    = y;

    eval_height(y);
    eval_height(x);

    return x;
}


tree_node_t*                    
smal_right_rotation(tree_node_t* x)
{
    tree_node_t* y  = x->left_node;
    x->left_node    = y->right_node;
    y->right_node   = x;

    eval_height(x);
    eval_height(y);

    return y;
}


inline
tree_node_t*                    
big_left_rotation(tree_node_t* root)
{
    root->right_node = smal_right_rotation(root->right_node);
    return smal_left_rotation(root);
}


inline
tree_node_t*                    
big_right_rotation(tree_node_t* root)
{
    root->left_node = smal_left_rotation(root->left_node);
    return smal_right_rotation(root);
}




tree_node_t*                    
fix_tree_balance(tree_node_t* root)
{

    if (balance_check_to_node(root) == 2)
    {
        if (balance_check_to_node(root->right_node) < 0)
            root->right_node = smal_right_rotation(root->right_node);
        
        return smal_left_rotation(root);
    }

    if (balance_check_to_node(root) == -2)
    {
        if (balance_check_to_node(root->left_node) > 0)
            root->left_node = smal_left_rotation(root->left_node);
        return smal_right_rotation(root);
    }

    return root;
}



tree_node_t*                    
insert_node_to_avl_tree(
    tree_t* tree, 
    tree_node_t** root, 
    tree_node_t** new_node
)
{
    tree_node_t* tmp_root =*root;
    tree_node_t* tmp_node = *new_node;

    if (tmp_root == NULL)
    {
        return tmp_node;
    }

    if (tree->is_more(tmp_root->data, tmp_node->data))
    {
        tmp_root->left_node = insert_node_to_avl_tree(
            tree, 
            &(tmp_root->left_node), 
            &tmp_node
        );
    }
    else
    {
        tmp_root->right_node = insert_node_to_avl_tree(
            tree,
            &(tmp_root->right_node), 
            &tmp_node
        );
    }
    
    eval_height(tmp_root);

    return fix_tree_balance(tmp_root);
}



tree_node_t*            
remove_node_to_avl_tree(
    tree_t* tree, 
    tree_node_t* root, 
    tree_iterator_t* itr
)
{
    return NULL;
}


struct avl_tree_node*   
make_avl_tree_node(allocator_t allocate, avl_tree_value_t data)
{
    avl_tree_node_t* new_node = allocate(SIZE_AVL_TREE_NODE);

    new_node->data          = data;
    new_node->left_node     = NULL;
    new_node->right_node    = NULL;
    new_node->parent        = NULL;
    new_node->height        = 1;

    return new_node;
}





void                    
free_tree(tree_t* tree, tree_node_t* root)
{
    tree_node_t* left = root->left_node;
    tree_node_t* right = root->right_node;

    if (left != NULL && right != NULL)
    {
        free_tree(tree, root->left_node);
        free_tree(tree, root->right_node);
    }
    else if (left != NULL && right == NULL)
    {
        free_tree(tree, root->left_node);
    }
    else if (left == NULL && right != NULL)
    {
        free_tree(tree, root->right_node);
    }
    
    tree->deallocate(root);
    tree->size_tree--;
}

void                    
free_avl_node(deallocator_t deallocate, tree_node_t* node)
{
    deallocate(node);
    node = NULL;
}