#include <stdio.h>
#include "heder/list.h"
#include "heder/test.h"


void* alloc(size_t s)
{
    printf("allocate %d bytes\n", s);
    return malloc(s);
}

void dealloc(void* p)
{
    printf("deallocate\n");
    free(p);
}

int main()
{
    list_t* list = make_list(alloc, dealloc);

    for (int i = 0; i < 10; ++i)
    {
        int* v = malloc(sizeof(int));
        *v =i;

        push_back_to_list(list, v);
    }


    for (list_iterator_t* i = list->begin; i != NULL; incr_list_itr(&i))
    {
        printf("key = %d\n", GET_LK(int, i));
    }
    

    delete_list_struct(list);

    return 0;
}