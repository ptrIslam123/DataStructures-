#include <stdio.h>
#include "heder/avl_tree.h"
#include "heder/private_avl_tree_ip.h"



avl_tree_t*             
init_avl_tree(avl_tree_t* tree, struct init_list* init)
{
    const size_t size       = init->size_data;
    const size_t size_type  = init->size_dataa_type;
    init_list_value_t data  = init->data;

    for (int i = 0; i < size; ++i)
    {
        insert_to_avl_tree(tree, data);
        data += size_type;
    }

    return tree;
}

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

    tree->root = insert_node_to_avl_tree(
        tree,
        &(tree->root), 
        &new_node    
    );

    tree->size_tree++;
}


void                    
remove_to_avl_tree(avl_tree_t* tree, avl_tree_value_t val)
{
    if (is_empty_avl_tree(tree))
        return;
        
    tree->root = remove_node_to_avl_tree(tree, tree->root, val);
    tree->size_tree--;
}



void                    
remove_by_ptr_to_avl_tree(
    avl_tree_t* tree,
    avl_tree_iterator_t* itr 
)
{
    if (is_empty_avl_tree(tree))
        return;

    tree->root = remove_node_by_ptr_to_avl_tree(tree, tree->root, itr);
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
    if (is_empty_avl_tree(tree))
        return;

    free_tree(tree, tree->root);
    free(tree);
    tree = NULL;
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
