#ifndef _POLL_ALLOCATOR_H_
#define _POLL_ALLOCATOR_H_

#include <stdlib.h>

void*   palloc(size_t size);
void    pfree(void* pobj);
void    free_pallocator(void);

#endif // !_POLL_ALLOCATOR_H_