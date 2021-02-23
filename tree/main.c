
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

    
    int arr[] = {5, 2 , 3, 4, 8, 6, 9, 1};
    const int size = sizeof(arr)/sizeof(arr[0]);

    tree_t* tree = make_std_tree(is_eqi, is_lessi, is_morei);

    for (int i = 0; i < size; ++i)
    {
        int* v = malloc(sizeof(int));
        *v = arr[i];
        insert_to_tree(tree, v);
    }


    for_each_tree(tree, print_tree_node, NULL);
    
    


    
    

    return 0;
}