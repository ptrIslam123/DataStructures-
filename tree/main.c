
#include <stdio.h>

#include "heder/tree.h"

unsigned char cmp_eq(tree_value_t l, tree_value_t r)
{
    return *(int*)l == *(int*)r;
}

unsigned char cmp_lt(tree_value_t l, tree_value_t r)
{
    return *(int*)l < *(int*)r;
}

unsigned char cmp_gt(tree_value_t l, tree_value_t r)
{
    return *(int*)l > *(int*)r;
}



int main()
{
   
    tree_t* tree = make_std_tree(cmp_eq, cmp_lt, cmp_gt);

    free_tree(tree);

    return 0;
}