#include "heder/private_palloc_ip.h"



mem_block_t*        
get_free_mem_block_to_poll_frame(size_t size)
{
    poll_frame_t* poll = get_poll_frame();

    for (
        list_iterator_t* i = begin_list(poll);
        i != end_list(poll);
        incr_list_itr(&i)
    )
    {
        mem_frame_t* frame = (mem_frame_t*)i->key;
        mem_block_t* mem = find_fisrt_suitable_mem_block_to_frame(frame, size);

        if (mem != NULL)
            return mem;
    }

    mem_frame_t* new_frame =  make_mem_frame(poll, size);
    return make_mem_block_to_frame(new_frame, size);
}


mem_block_t*        
find_fisrt_suitable_mem_block_to_frame(mem_frame_t* frame, size_t size)
{
    return NULL;
}




void                
unit_two_free_mem_block(mem_block_t* cur_block)
{

}


struct mem_block*   
make_mem_block_to_frame(mem_frame_t* frame, size_t siz)
{
    return NULL;
}




struct mem_frame*   
make_mem_frame(poll_frame_t* poll, size_t size_mem)
{
    return NULL;
}





poll_frame_t*       
get_poll_frame()
{
    static status_t is_init = 0;
    static poll_frame_t* poll = NULL;

    if (!is_init)
        poll = make_std_list();

    return poll;
}