#include <stdio.h>

#include "heder/clib.h"


void foo(void* arg)
{
    printf("num = %d\n", *(int*)arg);
}

#define TYPE short

int main()
{
    
    TYPE arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t size_data = sizeof(arr)/sizeof(arr[0]);
    size_t size_type = sizeof(TYPE);


    init_list_t* list = make_init_list(&size_data, &size_type,
        arr[0], arr[1], arr[2], arr[3], arr[4], arr[5]);

   

    PRINT_INIT_LIST(TYPE, list,"%d\n")

    return 0;
}