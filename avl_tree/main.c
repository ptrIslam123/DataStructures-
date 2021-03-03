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

    
    

    return 0;
}