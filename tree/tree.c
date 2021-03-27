#include "heder/tree.h"
#include "heder/private_tree_ip.h"
#include <stdio.h>


tree_t*             
init_tree(tree_t* tree, struct init_list* init)
{
    const size_t size       = init->size_data;
    const size_t size_type  = init->size_dataa_type;
    init_list_value_t data  = init->data;

    for (int i = 0; i < size; ++i)
    {
        insert_to_tree(tree, data);
        data += size_type;
    }

    return tree;
}


inline
unsigned char   
is_empty_tree(tree_t* tree)
{
    if (!tree->root)
        return IS_EMPTY_TREE;

    return IS_NOT_EMPTY_TREE;
}



inline
tree_iterator_t*    
get_min_to_tree(tree_t* tree)
{
    return find_min_node_to_tree(tree->root);
}


inline
tree_iterator_t*    
get_max_to_tree(tree_t* tree)
{
    return find_max_node_to_tree(tree->root);
}


tree_iterator_t*    
find_to_tree(tree_t* tree, tree_value_t data)
{
    return find_node_to_tree(tree, tree->root, data);
}


void            
insert_to_tree(tree_t* tree, tree_value_t data)
{
     tree_node_t* new_node = make_tree_node(tree->allocate, data);

    if (is_empty_tree(tree))
    {
        tree->root = new_node;
        tree->root->parent = new_node;
    }
    else
    {
        insert_node_to_tree(tree, &(tree->root), &new_node);   
    }

    tree->size_tree++;
}




void                
remove_to_tree(tree_t* tree, tree_iterator_t* root)
{
    tree_node_t* target = root;
    tree_node_t* parent = target->parent;

    if (target->left_node != NULL && target->right_node != NULL)
    {
        tree_node_t* local_max_node = find_max_node_to_tree(target->left_node);
        target->data = local_max_node->data;
        remove_to_tree(tree, local_max_node);
        return;
    }
    else if (target->left_node != NULL && target->right_node == NULL)
    {
        if (target == parent->left_node)
        {
            parent->left_node = target->left_node;
        }
        else
        {
            parent->right_node = target->left_node;
        }
    }
    else if (target->right_node != NULL && target->left_node == NULL)
    {
        if (target == parent->right_node)
        {
            parent->right_node = target->right_node;
        }
        else
        {
            parent->left_node = target->right_node;
        }
    }
    else
    {
        if (target == parent->left_node)
        {
            parent->left_node = NULL;
        }   
        else
        {
            parent->right_node = NULL;
        }
    }
    free_tree_node(tree->deallocate, &target);
    tree->size_tree--;
}




void                
for_each_tree(tree_t* tree, tree_func_t do_something, void** data)
{
    if (tree != NULL)
    {
        for_each_node_to_tree(tree, tree->root, do_something, data);
    }
}


struct tree* 
make_std_tree(compare_t is_eq, compare_t is_lt, compare_t is_gt)
{
    struct tree* new_tree = malloc(SIZE_TREE_STRCUT);

    new_tree->root          = NULL;
    new_tree->allocate      = malloc;
    new_tree->deallocate    = free;
    new_tree->size_tree     = 0;

    new_tree->is_eq         = is_eq;
    new_tree->is_less       = is_lt;
    new_tree->is_more       = is_gt;

    return new_tree;
}



struct tree*    
make_tree(allocator_t allocate, deallocator_t deallocate,
            compare_t is_eq, compare_t is_lt, compare_t is_gt)
{
    struct tree* new_tree = malloc(SIZE_TREE_STRCUT);

    new_tree->root          = NULL;
    new_tree->allocate      = allocate;
    new_tree->deallocate    = deallocate;
    new_tree->size_tree     = 0;

    new_tree->is_eq         = is_eq;
    new_tree->is_less       = is_lt;
    new_tree->is_more       = is_gt;

    return new_tree;
}


void            
free_tree(tree_t* tree)
{
    if (is_empty_tree(tree))
        return;

    _free_tree(tree, tree->root);
    free(tree);
    tree = NULL;
}




unsigned char 
is_eqi(const tree_value_t root, const tree_value_t other)
{
    return *(int*)root == *(int*)other;
}

unsigned char 
is_lessi(const  tree_value_t root, const tree_value_t other)
{
    return *(int*)root < *(int*)other;
}

unsigned char 
is_morei(const tree_value_t root, const tree_value_t other)
{
    return *(int*)root > *(int*)other;
}