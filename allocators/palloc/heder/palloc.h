#ifndef _POLL_ALLOCATOR_H_
#define _POLL_ALLOCATOR_H_

#include <stdlib.h>

void*   palloc(size_t size);
void    pfree(void* pobj);

#endif // !_POLL_ALLOCATOR_H_