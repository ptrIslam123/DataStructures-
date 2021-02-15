#include <stdio.h>
#include "heder/list.h"
#include "heder/test.h"




int main()
{
    int size = 10;
    list_t* list = make_list();


    for (int i = 0; i < size; ++i)
    {
        int *v = malloc(sizeof(int));
        *v = i;

        push_back(list, v);
    }

    list_iterator_t i = list->begin;
    test_print_node(i);

    list_iterator_t j = incr_list_itr(i);

    test_print_node(i);
    test_print_node(j);

    return 0;
}