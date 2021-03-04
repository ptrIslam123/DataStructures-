#ifndef _PRIVATE_AVL_TREE_STRUCT_H_
#define _PRIVATE_AVL_TREE_STRUCT_H_

#include "avl_tree.h"

typedef struct avl_tree         tree;
typedef avl_tree_t              tree_t;
typedef struct avl_tree_node    tree_node;
typedef avl_tree_node_t         tree_node_t;
typedef avl_tree_iterator_t     tree_iterator_t;
typedef avl_tree_value_t        tree_value_t;


tree_node_t*            fix_tree_balance(tree_node_t* );

height_t                get_height_node(tree_node_t* );
void                    eval_height(tree_node_t* );

balance_t               balance_check_to_node(tree_node_t* );

tree_node_t*            smal_left_rotation(tree_node_t* );
tree_node_t*            smal_right_rotation(tree_node_t* );

tree_node_t*            big_left_rotation(tree_node_t* );
tree_node_t*            big_right_rotation(tree_node_t* );



void                    for_each_node_to_avl_tree(
                            tree_t* , tree_node_t** ,
                            tree_func_t , 
                            void** 
);

tree_iterator_t*        find_node_to_avl_tree(
                            tree_t* , tree_node_t* root, 
                            tree_value_t val
);

tree_iterator_t*        find_min_node_to_avl_tree(tree_node_t* );
tree_iterator_t*        find_max_node_to_avl_tree(tree_node_t* );

tree_node_t*            insert_node_to_avl_tree(
                            tree_t* ,
                            tree_node_t** , 
                            tree_node_t** 
);


tree_node_t*            remove_node_to_avl_tree(
                            tree_t* , 
                            tree_node_t* , 
                            tree_value_t
);

tree_node_t*            remove_node_by_ptr_to_avl_tree(
                            tree_t* ,
                            tree_node_t* ,
                            tree_iterator_t*
);

tree_node_t*            remove_min_node_to_avl_tree(tree_node_t* );


struct avl_tree_node*   make_avl_tree_node(allocator_t , avl_tree_value_t );


void                    free_tree(tree_t* , tree_node_t* );
void                    free_avl_node(deallocator_t , tree_node_t* );


#endif // !_PRIVATE_AVL_TREE_STRUCT_H_
