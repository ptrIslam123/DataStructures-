#ifndef _TEST_H_
#define _TEST_H_

#include "list.h"

void test_main();

void test_push_back(int* data, int size);
void test_push_front(int* data, int size);
void test_free_list();
void test_pop_front();
void test_pop_back();

void test_print_node(node_t* );
void test_print_list(list_t* );

#endif // !_TEST_H_
