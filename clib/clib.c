#include "heder/clib.h"



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