#ifndef _CLIB_H_
#define _CLIB_H_

#include <stdlib.h>

struct part;

typedef void* value_part_t;


typedef struct part
{
    value_part_t    first;
    value_part_t    second;

} part_t;


#define GET_FIRST_PART(T, P) (T*)(P->first)
#define GET_SECOND_PART(T, P) (T*)(P->second)
struct part*    make_part(value_part_t , value_part_t );
void            free_part_struct(part_t* );




int*            make_int(int );
char*           make_char(char );
float*          make_float(float );
double*         make_double(double );

#endif // !_CLIB_H_