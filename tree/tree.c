#include "heder/tree.h"
#include "heder/private_tree_ip.h"

inline
unsigned char   
is_empty_tree(tree_t* tree)
{
    if (!tree->root)
        return IS_EMPTY_TREE;

    return IS_NOT_EMPTY_TREE;
}




tree_iterator_t*    
find_to_tree(tree_t* tree, tree_value_t data)
{
    return find_node_to_tree(tree, tree->root, data);
}


void            
insert_to_tree(tree_t* tree, tree_value_t data)
{
    insert_node_to_tree(tree, &(tree->root), 
        make_tree_node(tree->allocate, data)
    );
}





void                
for_each_tree(tree_t* tree, tree_func_t do_something)
{
    for_each_node_to_tree(tree->root, do_something);
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
    new_tree->is_lt         = is_lt;
    new_tree->is_gt         = is_gt;

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
    new_tree->is_lt         = is_lt;
    new_tree->is_gt         = is_gt;

    return new_tree;
}


void            
free_tree_struct(tree_t* tree)
{
    tree->deallocate(tree);
    tree = NULL;
}