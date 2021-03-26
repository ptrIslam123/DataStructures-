#ifndef _TEST_P_ALLOC_H_
#define _TEST_P_ALLOC_H_
#include "../heder/palloc.h"
#include "../heder/private_palloc_ip.h"

void    test_main(const int size_itreration);

void    test_print_mem_block(mem_block_t* blcok);
void    test_print_frame(frame_t* frame);
void    test_print_frame_inf(frame_t* frame);

void    test_init_array(int* arr, int size);
void    test_print_array(int* arr, int size); 
int*    test_do_something_with_arrays(int* arr1, int* arr2, int size);

#endif // !_TEST_P_ALLOC_H_
