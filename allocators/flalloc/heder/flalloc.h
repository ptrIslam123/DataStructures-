#ifndef _FREE_LIST_ALLOCATOR_H_
#define _FREE_LIST_ALLOCATOR_H_

#include <stdlib.h>
#include <stdio.h>


void*   flalloc(size_t );
void    flfree(void* );

void    free_free_list_struct();

#endif // !_FREE_LIST_ALLOCATOR_H_
