#include <stdio.h>
#include "heder/list.h"
#include "heder/test.h"
#include "../clib/heder/clib.h"

int main()
{
    list_t* list = init_list(
        make_std_list(),
        make_init_list(
            5, 0, 1, 2, 3, 4 
        )
    );

    const size_t len = list_size(list);;

    range_list_itr_t* i = make_range_list_itr(list, 0);

    while (1)
    {
        list_iterator_t* itr = i->cur_list_node;
        printf("i = %d\n", *(GET_LK(int, itr)));
        if (range_list(&i, len, 1) == 0)
            break;
        printf("loop\n");
    }
    

    return 0;
}

