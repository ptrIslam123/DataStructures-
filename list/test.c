#include <stdio.h>

#include "heder/test.h"

#include "heder/test.h"

/* 

void 
test_main(int* data, int size)
{
    test_push_back(data, size);
    test_push_front(data, size);
    test_free_list();
    test_pop_back(data, size);
    test_pop_front(data, size);
}

void 
test_push_back(int* data, int size)
{
    list_t* list = make_list();

    for (int i = 0; i < size; ++i)
    {
        push_back(list, &data[i]);
    }

    test_print_list(list);

    delete_list_struct(list);
    printf("\t\tDelete list struct\n");
}


void test_push_front(int* data, int size)
{
    list_t* list = make_list();

    for (int i = 0; i < size; ++i)
    {
        push_front(list, &data[i]);
    }

    test_print_list(list);

    delete_list_struct(list);
    printf("\t\tDelete list struct\n");
}


void test_free_list()
{
    const int size = 100;
    list_t* list = make_list();

    for (int i = 0; i < size; ++i)
    {
        int* v = malloc(sizeof(int));
        *v = i *(i + i * 100);
        push_back(list, v);
    }

    test_print_list(list);

    clear_list(list);
    free_list_struct(list);

    printf("[DEBUG_INF]this is list strcut free!\n");
}




void 
test_pop_front(int* data, int size)
{
    list_t* list = make_list();

    for (int i = 0; i < size; ++i)
    {
        push_back(list, &data[i]);
    }

    printf("\t\tbefore pop_front\n\n");
    test_print_list(list);

    pop_front(list);

    printf("\t\tafter pop_font\n\n");
    test_print_list(list);

    delete_list_struct(list);
    printf("\t\tDelete list struct\n");
}


void 
test_pop_back(int* data, int size)
{
    list_t* list = make_list();

    for (int i = 0; i < size; ++i)
    {
        push_back(list, &data[i]);
    }

    printf("\t\tbefore pop_back\n\n");
    test_print_list(list);

    pop_back(list);

    printf("\t\tafter pop_back\n\n");
    test_print_list(list);

    delete_list_struct(list);
    printf("\t\tDelete list struct\n");
}



void 
test_print_node(node_t* n)
{
    printf("key = %d\n", 
        *(int*)n->key);
}


void 
test_print_list(list_t* list)
{
    node_t* item = list->begin;

    while ( item != NULL)
    {
        printf("item->key = %d\n", 
            *(int*)item->key);
        item = item->next_node;
    }
}

*/