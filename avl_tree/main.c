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
    
    for_each_avl_tree(tree, print_t, NULL);

    test_tree(tree, tree->root);
    test_balance_tree(tree);

    printf("size tree = %d\n", tree->size_tree);

    free_avl_tree(tree);

    //printf("size avl tree after free tree = %d\n", tree->size_tree);
    

    return 0;
}