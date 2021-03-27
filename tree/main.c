
#include <stdio.h>

#include "heder/tree.h"



int count_m = 0;

void print_tree_node(tree_t* tree, tree_iterator_t** itr, void** data)
{
    tree_iterator_t* i = *itr;
    int v = *GET_TK(int, i);

    printf("%d\n", v);
}


int main()
{

    
    

    return 0;
}