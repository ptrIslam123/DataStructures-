#include "heder/palloc.h"
#include "heder/private_palloc_ip.h"


inline
void*   
palloc(size_t size)
{
    return get_mem(size);
}


inline
void    
pfree(void* pobj)
{
   set_status_to_mem(pobj, FREE_BLOCK);
}