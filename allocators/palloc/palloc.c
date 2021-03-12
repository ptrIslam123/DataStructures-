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
   void* mem = get_ptr_on_mem_block_by_ptr_data(pobj);
   set_status_mem_block(mem, FREE_BLOCK);
}