#include "heder/palloc.h"
#include "heder/private_palloc_ip.h"


inline
void*   
palloc(size_t size)
{
    mem_block_t* free_block = get_free_mem_block(size);
    return get_ptr_on_data(free_block);
}


inline
void    
pfree(void* mem)
{
    if (mem != NULL)
    {
        mem_block_t* mblcok = get_ptr_on_mem_block(mem);
        free_mem_blcok(&mblcok);
    }
}


inline
void    
free_pallocator(void)
{
    free_frames_struct();
}