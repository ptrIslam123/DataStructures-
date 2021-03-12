#ifndef _TEST_P_ALLOC_H_
#define _TEST_P_ALLOC_H_
#include "../heder/palloc.h"
#include "../heder/private_palloc_ip.h"


void test_main(const size_t size_iteration);

void print_array(int* arr, size_t size);
void init_array(int* arr, size_t size);
void test_palloc(const size_t size);

void test_print_mem_block(void* mem);
void test_print_mem_frame(mem_frame_t* frame);

#endif // !_TEST_P_ALLOC_H_
