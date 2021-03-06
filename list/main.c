#include <stdio.h>
#include "heder/list.h"
#include "heder/test.h"
#include "../clib/heder/clib.h"



void print_list(list_t* list)
{
    for (
        list_iterator_t* i = begin_list(list);
        i != end_list(list);
        incr_list_itr(&i)
    )
    {
        printf("item = %d\n", *(GET_LK(int, i)));
    }
    printf("\n");
}

void check_sort_list(list_t* list)
{
    for (
        list_iterator_t* i = list->begin->next_node;
        i != end_list(list);
        incr_list_itr(&i)
    )
    {
        list_iterator_t* cur = i;
        list_iterator_t* prev = i->prev_node;

        if (is_morei_list(prev->key, cur->key))
        {
            printf("%d > %d\n", *(GET_LK(int, cur)), *(GET_LK(int, prev)) 
                );
            exit(-1);
        }
    }
}

int main()
{
    for (int i = 0; i < 100; ++i)
    {
        list_t* list = make_std_list();

        for (int j = 0; j < 10; ++j)
        {
            push_back_to_list(list, make_int(rand() % 1000));
        }

        selection_sort_to_list(list, is_lessi_list);
        check_sort_list(list);

        free_list(list);
    }
    
    
    return 0;
}

