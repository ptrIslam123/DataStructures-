#ifndef _TREE_H_
#define _TREE_H_

#include <stdlib.h>

#define SIZE_TREE_NODE      (sizeof(struct tree_node))
#define SIZE_TREE_STRCUT    (sizeof(struct tree))
#define IS_EMPTY_TREE       (1)
#define IS_NOT_EMPTY_TREE   (0)



struct tree;
struct tree_node;


typedef void* tree_value_t;
typedef struct tree_node tree_iterator_t;
typedef void* (*allocator_t)(size_t );
typedef void (*deallocator_t)(void* );
typedef unsigned char (*compare_t)(const tree_value_t , const tree_value_t );

typedef void (*tree_func_t)(struct tree* , tree_iterator_t** , void** );



typedef struct tree
{
    struct tree_node*   root;
    allocator_t         allocate;
    deallocator_t       deallocate;
    size_t              size_tree;

    compare_t           is_eq;
    compare_t           is_less;
    compare_t           is_more;
    
} tree_t;


typedef struct tree_node
{
    struct tree_node*   left_node;
    struct tree_node*   right_node;
    struct tree_node*   parent;
    tree_value_t        data;

} tree_node_t;



//      GET_TREE_KEY | KEY <-> DATA
#define GET_TK(T, tree_itr) ((T*)tree_itr->data)


unsigned char       is_empty_tree(tree_t* );

tree_iterator_t*    get_min_to_tree(tree_t* );
tree_iterator_t*    get_max_to_tree(tree_t* );
tree_iterator_t*    find_to_tree(tree_t* , tree_value_t );
void                insert_to_tree(tree_t* , tree_value_t );

void                remove_by_ptr_to_tree(tree_t* , tree_iterator_t* );


void                for_each_tree(tree_t* , tree_func_t ,void** );

struct tree*        make_std_tree(compare_t is_eq, compare_t is_lt, compare_t is_gt);
struct tree*        make_tree(allocator_t, deallocator_t , 
                        compare_t is_eq, compare_t is_lt, compare_t is_gt);

void                free_tree_struct(tree_t* );




unsigned char       is_eqi(const tree_value_t root, const tree_value_t other);
unsigned char       is_lessi(const  tree_value_t root, const tree_value_t other);
unsigned char       is_morei(const tree_value_t root, const tree_value_t other);



#endif // !_TREE_H_
