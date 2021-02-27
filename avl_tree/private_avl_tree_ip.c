#include <stdio.h>
#include "heder/private_avl_tree_ip.h"




void                    
fix_tree_balance(tree_node_t* root)
{
    height_t left_balance = get_height_node(root->right_node) 
                                - get_height_node(root->left_node);

    height_t right_balance = get_height_node(root->left_node)
                                - get_height_node(root->right_node);


    printf("root->data = %d\n", *(GET_ATK(int, root)));
    //printf("left_balance = %d\nright_balance = %d\n\n", left_balance, right_balance);

    if (left_balance == 2)
    {
        
    }
    else if (right_balance == 2)
    {

    }
    else
    {
        // nothing
    }
}


height_t                
get_height_node(tree_node_t* node)
{
     if (node == NULL)
        return 0;

    height_t left_h = get_height_node(node->left_node);
    height_t rigth_h = get_height_node(node->right_node);

    return (left_h > rigth_h ? left_h : rigth_h) + 1;
}
  


inline
balance_t           
balance_check_to_node(tree_node_t* root)
{
    return get_height_node(root->left_node) - get_height_node(root->right_node);
}




void                    
smal_left_rotation(tree_node_t* root)
{
    tree_node_t* right      = root->right_node;
    tree_node_t* sub_tree   = right->left_node;

    right->left_node = root;
    root->right_node = sub_tree;
}


void                    
smal_right_rotation(tree_node_t* root)
{
    tree_node_t* left       = root->left_node;
    tree_node_t* sub_tree   = left->right_node;

    left->right_node = root;
    root->right_node = sub_tree;
}


inline
void                    
big_left_rotation(tree_node_t* root)
{
    smal_right_rotation(root->right_node);
    smal_left_rotation(root);
}


inline
void                    
big_right_rotation(tree_node_t* root)
{
    smal_left_rotation(root->left_node);
    smal_right_rotation(root);
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

    fix_tree_balance(tmp_node);
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



void                    
free_avl_node(deallocator_t deallocate, tree_node_t* node)
{
    deallocate(node);
    node = NULL;
}