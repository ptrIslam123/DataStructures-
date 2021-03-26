#include "heder/palloc.h"
#include "heder/private_palloc_ip.h"


inline
void*   
palloc(size_t size)
{
    mem_block_t* free_block = get_free_mem_block(size);
    return (void*)free_block + SIZE_META_DATA;
}


inline
void    
pfree(void* mem)
{
    mem_block_t* mblcok = GET_PTR_ON_MEM_BLCOK(mem);
   free_mem_blcok(&mblcok);
}


inline
void    
free_pallocator(void)
{
    free_frames_struct();
}