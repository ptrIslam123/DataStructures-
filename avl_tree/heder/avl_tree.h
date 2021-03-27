#ifndef _AVL_TREE_STRUCT_H_
#define _AVL_TREE_STRUCT_H_

#include <stdlib.h>
#include "../../clib/heder/clib.h"


#define SIZE_AVL_TREE_NODE      (sizeof(struct avl_tree_node))
#define SIZE_AVL_TREE_STRCUT    (sizeof(struct avl_tree))
#define IS_EMPTY_TREE       (1)
#define IS_NOT_EMPTY_TREE   (0)

struct avl_tree;
struct avl_tree_node;


typedef void*   avl_tree_value_t;
typedef struct  avl_tree_node avl_tree_iterator_t;
typedef void*   (*allocator_t)(size_t );
typedef void    (*deallocator_t)(void* );
typedef unsigned char (*compare_t)(const avl_tree_value_t , const avl_tree_value_t );

typedef void (*tree_func_t)(struct avl_tree* , avl_tree_iterator_t** , void** );
typedef size_t  height_t;
typedef short   balance_t;


typedef struct avl_tree
{
    struct avl_tree_node*   root;
    allocator_t             allocate;
    deallocator_t           deallocate;
    size_t                  size_tree;

    compare_t               is_eq;
    compare_t               is_less;
    compare_t               is_more;

} avl_tree_t;


typedef struct avl_tree_node
{
    struct avl_tree_node*   left_node;
    struct avl_tree_node*   right_node;
    struct avl_tree_node*   parent;
    height_t                height;
    avl_tree_value_t        data;

} avl_tree_node_t;




//      GET_AVL_TREE_KEY | KEY <-> DATA
#define GET_ATK(T, avl_tree_itr) ((T*)avl_tree_itr->data)


avl_tree_t*             init_avl_tree(avl_tree_t* tree, struct init_list* init);

unsigned char           is_empty_avl_tree(avl_tree_t* );


height_t                get_height_avl_tree(avl_tree_t* );
balance_t               balance_check_to_avl_tree(avl_tree_t* );


avl_tree_iterator_t*    get_min_to_avl_tree(avl_tree_t* );
avl_tree_iterator_t*    get_max_to_avl_tree(avl_tree_t* );
avl_tree_iterator_t*    find_to_avl_tree(
                            avl_tree_t* , 
                            avl_tree_value_t 
);
void                    insert_to_avl_tree(
                            avl_tree_t* , 
                            avl_tree_value_t 
);

void                    remove_to_avl_tree(
                            avl_tree_t* , 
                            avl_tree_value_t 
);


void                    remove_by_ptr_to_avl_tree(
                            avl_tree_t* ,
                            avl_tree_iterator_t* 
);

void                    for_each_avl_tree(
                            avl_tree_t* , 
                            tree_func_t ,
                            void** 
);

struct avl_tree*         make_std_avl_tree(
                            compare_t is_eq, 
                            compare_t is_lt, 
                            compare_t is_gt
);
struct avl_tree*         make_avl_tree(
                            allocator_t, 
                            deallocator_t , 
                            compare_t is_eq, 
                            compare_t is_lt, 
                            compare_t is_gt
);

void                    free_avl_tree(avl_tree_t* );




unsigned char           is_eqi_avl(
                            const avl_tree_value_t root, 
                            const avl_tree_value_t other
);
unsigned char           is_lessi_avl(
                            const  avl_tree_value_t root, 
                            const avl_tree_value_t other
);
unsigned char           is_morei_avl(
                            const avl_tree_value_t root, 
                            const avl_tree_value_t other
);




#endif // !_AVL_TREE_STRUCT_H_
