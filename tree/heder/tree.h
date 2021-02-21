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
typedef void* (*allocator_t)(size_t );
typedef void (*deallocator_t)(void* );
typedef unsigned char (*compare_t)(tree_value_t , tree_value_t );


typedef struct tree
{
    struct tree_node*   root;
    allocator_t         allocate;
    deallocator_t       deallocate;

    compare_t           is_eq;
    compare_t           is_lt;
    compare_t           is_gt;
    
} tree_t;


typedef struct tree_node
{
    struct tree_node*   left_node;
    struct tree_node*   right_node;
    struct tree_node*   parent;
    tree_value_t        data;

} tree_node_t;


unsigned char   is_empty_tree(tree_t* );
void            insert_to_tree(tree_t* , tree_value_t );

struct tree*    make_std_tree(compare_t is_eq, compare_t is_lt, compare_t is_gt);
struct tree*    make_tree(allocator_t, deallocator_t , 
                    compare_t is_eq, compare_t is_lt, compare_t is_gt);

void            free_tree(tree_t* );

#endif // !_TREE_H_
