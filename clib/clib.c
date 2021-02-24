#include "heder/clib.h"
#include <stdio.h>

#define _TEST_


struct part*    
make_part(value_part_t first, value_part_t second)
{
    struct part* new_part = malloc(sizeof(struct part));

    new_part->first     = first;
    new_part->second    = second;

    return new_part;
}




void            
free_part_struct(part_t* p)
{
    free(p->first);
    free(p->second);
    free(p);
    p = NULL;
}





/** struct init_list **/

struct init_list* make_init_list(size_t size, int arg, ... )
{   
    int* arr = malloc(sizeof(int) * size);
    int* itr = &arg;

    for (int i = 0; i < size; ++i, ++itr)
    {
        arr[i] = *itr;
    }

    struct init_list* list  = malloc(sizeof(init_list_t));

    list->data              = arr;
    list->size_data         = size;
    list->size_dataa_type   = sizeof(int);

    return list;
}

#ifndef _TEST_

struct 
init_list* make_init_list(void* args, ... )
{
    size_t size_data = *(size_t*)args;
    args = args + sizeof(size_t);

    size_t size_type = *(size_t*)args;
    args = args + sizeof(size_t);

    args = args + size_type;

    struct init_list* list  = malloc(sizeof(init_list_t));
    list->data              = malloc(size_data * size_type);
    list->size_data         = size_data;
    list->size_dataa_type   = size_type;

    for (size_t i = 0; i < size_data; i++)
    {
        args = args + size_type;
        //double v = *(double*)args;
        //printf("v = %f\n", v);
        list->data[i] = args;
    }
    
    return list;
}

#endif // !_TEST_


int* 
make_int(int v)
{
    int* nv = malloc(sizeof(int));
    *nv = v;

    return nv;
}


char* 
make_char(char v)
{
    char* nc = malloc(sizeof(char));
    *nc = v;

    return nc;
}


float* 
make_float(float v)
{
    float* nf = malloc(sizeof(float));
    *nf = v;

    return nf;
}


double* 
make_double(double v)
{
    double* nd = malloc(sizeof(double));
    *nd = v;

    return nd;
}