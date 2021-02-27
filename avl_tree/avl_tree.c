#include <stdio.h>
#include "heder/avl_tree.h"
#include "heder/private_avl_tree_ip.h"

inline
unsigned char           
is_empty_avl_tree(avl_tree_t* tree)
{
    return !(tree->size_tree);
}



inline
height_t                
get_height_avl_tree(avl_tree_t* tree)
{
    return get_height_node(tree->root);
}


inline
balance_t           
balance_check_to_avl_tree(avl_tree_t* tree)
{
    return balance_check_to_node(tree->root);
}



inline
avl_tree_iterator_t*    
get_min_to_avl_tree(avl_tree_t* tree)
{
    if (is_empty_avl_tree(tree))
        return NULL;

    return find_min_node_to_avl_tree(tree->root);
}


inline
avl_tree_iterator_t*    
get_max_to_avl_tree(avl_tree_t* tree)
{
    if (is_empty_avl_tree(tree))
        return NULL;

    return find_max_node_to_avl_tree(tree->root);
}


inline
avl_tree_iterator_t*    
find_to_avl_tree(avl_tree_t* tree, avl_tree_value_t val)
{
    if (!is_empty_avl_tree(tree))
        return find_node_to_avl_tree(tree, tree->root, val);

    return NULL;
}



void                    
insert_to_avl_tree(avl_tree_t* tree, avl_tree_value_t val)
{
    avl_tree_node_t* new_node = make_avl_tree_node(tree->allocate, val);
    
    if (is_empty_avl_tree(tree))
    {
        tree->root          = new_node;
        tree->root->parent  = new_node;
    }else
    {
        insert_node_to_avl_tree(tree, &(tree->root), &new_node);
    }

    printf("main\t");
    fix_tree_balance(tree->root);
    tree->size_tree++;
}


void                    
remove_to_avl_tree(avl_tree_t* tree, avl_tree_iterator_t* node)
{
    if (node->left_node == NULL && node->right_node == NULL)
        free_avl_node(tree->deallocate, node);
    
    else if (node->left_node == NULL && node->right_node != NULL)
    {
        avl_tree_node_t* parent = node->parent;

        if (node == parent->left_node)
        {
            parent->left_node = node->right_node;
        }
        else
        {
            parent->right_node = node->right_node;
        }
    }
    else if (node->left_node != NULL && node->right_node == NULL)
    {
        avl_tree_node_t* parent = node->parent;

        if (node == parent->left_node)
        {
            parent->left_node = node->left_node;
        }
        else
        {
            parent->right_node = node->left_node;
        }
    }
    else
    {
      avl_tree_node_t* local_max_node = find_max_node_to_avl_tree(node->left_node);
      node->data = local_max_node->data;
      remove_to_avl_tree(tree, local_max_node);

      //fix_tree_balance(node);
      return;  
    }
    
    //printf("insert root->data = %d\n", *(GET_ATK(int, node)));
    //fix_tree_balance(node);
    tree->size_tree--;
}


inline
void                    
for_each_avl_tree(avl_tree_t* tree, tree_func_t do_something,void** data)
{
    for_each_node_to_avl_tree(tree, &(tree->root), do_something, data);
}




struct avl_tree*            
make_std_avl_tree(compare_t is_eq, compare_t is_lt, compare_t is_gt)
{
    avl_tree_t* new_tree = malloc(SIZE_AVL_TREE_STRCUT);

    new_tree->root          = NULL;
    new_tree->allocate      = malloc;
    new_tree->deallocate    = free;
    new_tree->is_eq         = is_eq;
    new_tree->is_less       = is_lt;
    new_tree->is_more       = is_gt;

    return new_tree;
}


struct avl_tree*            
make_avl_tree(allocator_t allocate, deallocator_t deallocate, 
                compare_t is_eq, compare_t is_lt, compare_t is_gt)
{
    avl_tree_t* new_tree = malloc(SIZE_AVL_TREE_STRCUT);

    new_tree->root          = NULL;
    new_tree->allocate      = allocate;
    new_tree->deallocate    = deallocate;
    new_tree->is_eq         = is_eq;
    new_tree->is_less       = is_lt;
    new_tree->is_more       = is_gt;

    return new_tree; 
}




void                    
free_avl_tree(avl_tree_t* tree)
{

}





unsigned char           
is_eqi_avl(const avl_tree_value_t root, const avl_tree_value_t other)
{
    return *(int*)root == *(int*)other;
}


unsigned char           
is_lessi_avl(const  avl_tree_value_t root, const avl_tree_value_t other)
{
    return *(int*)root < *(int*)other;
}

unsigned char           
is_morei_avl(const avl_tree_value_t root, const avl_tree_value_t other)
{
    return *(int*)root > *(int*)other;
}
