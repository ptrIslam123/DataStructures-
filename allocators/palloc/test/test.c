#include "test.h"

#include <stdio.h>




void 
test_main(const size_t size_iteration)
{
   for (size_t i = 0; i < size_iteration; ++i)
   {
       size_t size = rand() % 1000;
       int* arr = palloc(sizeof(int)*size);
        if (arr == NULL)
        {
            printf("|| BAD ALLOC = %d ||\n\n", size);
            return;
        }
       init_array(arr, size_iteration);
       print_array(arr, size_iteration);
       pfree(arr);
   }
}


void 
print_array(int* arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        printf("arr[%d] = %d\n", i, arr[i]);
    }
    printf("========================================\n");
}

void 
init_array(int* arr, size_t size)
{
    for (size_t i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100;
    }
}


void 
test_palloc(const size_t size)
{
    size_t size_array = 0; 

    for (size_t i = 0; i < size; ++i)
    {
        size_array = rand() % 100;
        int* arr = palloc(sizeof(int) * size_array);
        init_array(arr, size_array);
        printf("\t\t%d\n", i);
        print_array(arr, size_array);
        pfree(arr);
    }
}




void 
test_print_mem_block(void* mem)
{
    size_t size_block = get_size_cur_mem_block(mem);
    status_t status = get_status_mem_block(mem);
    size_t size_prev_block = get_size_prev_mem_block(mem);

    printf("{\nsize_block = %d\nstatus_block = %d\nsize_prev_block = %d\n}\n\n",
        size_block, status, size_prev_block);
}



void 
test_print_mem_frame(mem_frame_t* frame)
{
    void* mem = frame->begin;
    size_t count = frame->count_blocks;

    for (size_t i = 0; i < count; ++i)
    {
        test_print_mem_block(mem);
        incr_mem_iter(&mem);
    }
}