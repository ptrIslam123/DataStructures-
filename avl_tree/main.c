#include <stdio.h>
#include "heder/avl_tree.h"
#include "../clib/heder/clib.h"

int main()
{
    const int size = 10;
    avl_tree_t* tree = make_std_avl_tree(is_eqi_avl, is_lessi_avl, is_morei_avl);

    for (int i = 0; i < size; ++i)
    {
        printf("insert to tree %d\n", i);
        insert_to_avl_tree(tree, make_int(i));
    }

    printf("\n\n");

    printf("max = %d\n", *(GET_ATK(int, get_max_to_avl_tree(tree))));
    printf("min = %d\n", *(GET_ATK(int, get_min_to_avl_tree(tree))));

    int v = 5;
    printf("find = %d\n", *(GET_ATK(int, find_to_avl_tree(tree, &v))));
    //printf("size tree = %d\n", tree->size_tree);


    return 0;
}