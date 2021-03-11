#include "heder/private_palloc_ip.h"



void*           
get_mem(size_t size)
{
    poll_frame_t* frames    = get_poll_frame_struct();
    void* mem               = NULL;

    for (
        list_iterator_t* i  = begin_list(frames);
        i                   != end_list(frames);
        incr_list_itr(&i)
    )
    {
        mem_frame_t* frame  = GET_LK(mem_frame_t, i);
        mem                 = find_first_suitable_to_frame(frame, size);

        if (mem != NULL)
            return mem;
    }

    return make_new_mem_frame_and_alloc_in_it(frames, size);
}




void*           
find_first_suitable_to_frame(mem_frame_t* frame, size_t size)
{
    const size_t count  = frame->count_blocks;
    void* block         = frame->begin;

    for (size_t i = 0; i < count; ++i)
    {
        if (get_status_to_mem(block) == FREE_BLOCK && 
            get_size_to_mem(block) >= size)
                return block;
        
        incr_mem_iter(&block);
    }

    return alloc_block_to_frame(frame, size);
}



void*           
alloc_block_to_frame(mem_frame_t* frame, size_t size)
{
    if (frame->size_free_mem > 0 && frame->size_free_mem < size)
        return NULL;

    frame->size_free_mem -= size;
    return make_mem_block(frame->cur_free_space, size);
}




inline
void*           
make_new_mem_frame_and_alloc_in_it(poll_frame_t* frames, size_t size)
{
    push_back_to_list(
        frames, 
        make_mem_frame(eval_new_size_for_mem_frame(frames))
    );

    mem_frame_t* new_frame = GET_LK(mem_frame_t, get_back_from_list(frames));

    return alloc_block_to_frame(new_frame, size);
}


mem_frame_t*    
make_mem_frame(size_t size_frame)
{
    mem_frame_t* new_frame      = malloc(SIZE_MEM_FRAME_STRCUT);
    new_frame->begin            = malloc(size_frame);

    new_frame->end              = new_frame->begin + size_frame;
    new_frame->cur_free_space   = new_frame->begin;
    new_frame->size_frame       = size_frame;
    new_frame->size_free_mem    = size_frame;

    return new_frame;
}


void*           
make_mem_block(void* mem, size_t size)
{
    set_size_to_mem(mem, size);
    set_status_to_mem(mem, NOT_FREE_BLOCK);
    return get_ptr_on_data(mem);
}





poll_frame_t*   
get_poll_frame_struct()
{
    static list_t* poll = NULL;

    if (poll == NULL)
        poll = init_poll_frame();

    return poll;
}



poll_frame_t*            
init_poll_frame()
{
    poll_frame_t* frames = make_std_list();
    push_back_to_list(frames, make_mem_frame(SIZE_FIRST_MEM_FRAME));

    return frames;
}



inline
size_t          
eval_new_size_for_mem_frame(poll_frame_t* frames)
{
    mem_frame_t* back = GET_LK(mem_frame_t, get_back_from_list(frames));

    return back->size_frame * 2;
}


void            
incr_mem_iter(void** mem)
{
    const size_t size_block = get_size_to_mem(*mem);
    *mem += size_block + SIZE_HEDER_MEM;
}


inline
void        
set_size_to_mem(void* mem, size_t size)
{
    *(size_t*)mem = size;
}


inline
void        
set_status_to_mem(void* mem, status_t status)
{
    *(status_t*)(mem + sizeof(size_t)) = status;
}



inline
size_t          
get_size_to_mem(void* mem)
{
    return *(size_t*)mem;
}


inline
status_t        
get_status_to_mem(void* mem)
{
    return *(status_t*)(mem + sizeof(size_t));
}


inline
void*       
get_ptr_on_data(void* mem)
{
    return mem + SIZE_HEDER_MEM;
}


