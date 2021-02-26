#include <stdio.h>
#include "heder/avl_tree.h"
#include "../clib/heder/clib.h"

void print(avl_tree_t* tree, avl_tree_iterator_t** it, void** data)
{
    avl_tree_iterator_t* i = *it;
    printf("tree->key = %d\n", *(GET_ATK(int, i)));
}

int main()
{
    int arr[] = {1, 4, 7, 8, 2};
    const int size = sizeof(arr) / sizeof(arr[0]);
    avl_tree_t* tree = make_std_avl_tree(is_eqi_avl, is_lessi_avl, is_morei_avl);

    for (int i = 0; i < size; ++i)
    {
        printf("insert to tree %d\n", i);
        insert_to_avl_tree(tree, make_int(arr[i]));
    }

    printf("\n\n");


    for_each_avl_tree(tree, print, NULL);

    printf("\n\n");
   
    printf("heigth tree = %d\n", get_height_avl_tree(tree));


    printf("balance = %d\n", 
        balance_check_to_avl_tree(tree));

    return 0;
}