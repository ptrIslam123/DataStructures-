#include <stdio.h>
#include "heder/stack.h"
#include "../clib/heder/clib.h"

int main()
{
    const int size = 10;
    stack_t* s = make_std_stack();

    for (int i = 0; i < size; ++i)
    {
        printf("push %d\n", i);
        push_to_stack(s, make_int(i));
    }

    printf("\n\n");

    for (int i = 0; i < size; ++i)
    {
        stack_value_t v= pop_from_stack(s);
        printf("pop %d\n", *GET_SV(int, v));
    }

    free_stack(s);

    return 0;
}