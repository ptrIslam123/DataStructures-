#include <stdio.h>
#include "heder/queue.h"
#include "../clib/heder/clib.h"

int main()
{
    const int size = 10;
    queue_t* queue = make_std_queue();

    for (int i = 0; i < size; ++i)
    {   
        printf("push %d\n", i);
        push_to_queue(queue, make_int(i));
    }

    printf("\n\n");

    for (int i = 0; i < size; ++i)
    {
        queue_value_t v = pop_from_queue(queue);
        printf("pop %d\n", *GET_QV(int, v));
    }


   
    

    free_queue(queue);

    return 0;
}