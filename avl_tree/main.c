#include <stdio.h>
#include "heder/avl_tree.h"
#include "../clib/heder/clib.h"
#include "test/test_avl_tree.h"

void print_t(avl_tree_t* tree, avl_tree_iterator_t** itr, void** data)
{
    avl_tree_iterator_t* i = *itr;
    printf("avl tree node->key = %d\n", *(GET_ATK(int, i)));
}



int main()
{
    avl_tree_t* tree = make_std_avl_tree(
        is_eqi_avl,
        is_lessi_avl,
        is_morei_avl
    );

    int arr[] = {4, 5, 3, 8};
    const int size = sizeof(arr)/ sizeof(arr[0]);

    for (int i = 0; i < size; ++i)
    {
        int* v = make_int(arr[i]);
        insert_to_avl_tree(tree, v);
    }
    
    printf("print tree values\n");
    for_each_avl_tree(tree, print_t, NULL);
    printf("\n\n");
/
    test_tree(tree, tree->root);
    test_balance_tree(tree);

    int* v = make_int(3);
    printf("search value = %d\n", *v);
    avl_tree_iterator_t* i = find_to_avl_tree(tree, v);
    printf("find node->key = %d\n", *(GET_ATK(int, i)));

    remove_by_ptr_to_avl_tree(tree, i);
    printf("remove by pointer->key = %d\n\n", *v);


    printf("print tree values\n");
    for_each_avl_tree(tree, print_t, NULL);
    printf("\n\n");

    free_avl_tree(tree);

    return 0;
}