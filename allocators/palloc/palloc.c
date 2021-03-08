#include "heder/palloc.h"
#include "heder/private_palloc_ip.h"


void*   
palloc(size_t size)
{
    mem_block_t* mem = get_free_mem_block_to_poll_frame(size);
    return mem + SIZE_MEM_BLOCK_STRUCT;
}


void    
pfree(void* pobj)
{
    mem_block_t* mem = pobj - SIZE_MEM_BLOCK_STRUCT;
    mem->status_block = FREE_BLOCK;

    unit_two_free_mem_block(mem);
}