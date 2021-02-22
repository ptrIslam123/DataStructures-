
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


void print_tree_node(tree_iterator_t* itr)
{
    int v = *GET_TK(int, itr);

    printf("%d\n", v);
}


int main()
{
    const int size = 10;
    

    tree_t* tree = make_std_tree(cmp_eq, cmp_lt, cmp_gt);

    for (int i = 0; i < size; ++i)
    {
        int* v = malloc(sizeof(int));
        *v = i;
        insert_to_tree(tree, v);
    }

   
    
   for_each_tree(tree, print_tree_node);
    


    

    

    free_tree_struct(tree);

    return 0;
}