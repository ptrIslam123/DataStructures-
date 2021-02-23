#include <stdio.h>

#include "heder/clib.h"

int main()
{

    part_t* p = make_part(
        make_int(10), make_char('h')
    );

    int f = *GET_FIRST_PART(int, p);
    char s = *GET_SECOND_PART(char, p);
    printf("f = %d\ns = %c\n", f, s);

    free_part_struct(p);

    return 0;
}