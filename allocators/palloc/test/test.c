#include "test.h"
#include <stdio.h>



void    
test_main(const int size_itreration)
{
    int size = 10;

    for (int i = 0; i < size_itreration; ++i)
    {
        size = rand() % 100;

        int* arr1 = palloc(sizeof(int) * size);
        int* arr2 = palloc(sizeof(int) * size);

        test_init_array(arr1, size);
        test_init_array(arr2, size);

        test_print_array(arr1, size);
        test_print_array(arr2, size);


        int* arr = test_do_something_with_arrays(arr1, arr2, size);

        test_print_array(arr, size);

        pfree(arr1);
        pfree(arr2);

        printf("\t\t\titerable := %d\n\n", i + 1);
    }
}


void    
test_print_mem_block(const char* msg, mem_block_t* blcok)
{
    printf("{\n");
    printf("\t&(%s) = %p\n", msg, blcok);
    printf("\tsize_blcok = %d\n\tstatus_block = %d\n\tframe_addr = %p\n",
        blcok->size_block, blcok->status, blcok->p_frame);
    printf("}\n");
}


void    
test_print_frame(frame_t** frame)
{
    size_t size = (*frame)->count_blocks;
    mem_block_t* it = (*frame)->begin;

    for (size_t i = 0; i < size; ++i)
    {
        test_print_mem_block("", it);

        incr_mem_blcok_itr(&it);
    }
}


void    
test_print_frame_inf(frame_t* frame)
{
    printf("frame->size = %d\n", frame->size_frame);
    printf("frame->size_free_mem = %d\n", frame->size_free_mem);
    printf("frame->count_blocks = %d\n", frame->count_blocks);
    printf("\n");
}



void     
test_init_array(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100;
    }
}



void    
test_print_array(int* arr, int size)
{
    for (int i = 0; i < size; ++i)
    {
        printf("arr[%d] = %d\n", i , arr[i]);
    }
    printf("\n");
}


int*    
test_do_something_with_arrays(int* arr1, int* arr2, int size)
{
    int* arr = palloc(sizeof(int) * size);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = arr1[i] * (arr2[i] + arr2[i]);
    }

    return arr;
}