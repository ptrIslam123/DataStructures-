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
    if (size > frame->size_frame)
        return NULL;

    const size_t count  = frame->count_blocks;
    void* block         = frame->begin;

    for (size_t i = 0; i < count; ++i)
    {
        if (get_status_mem_block(block) == FREE_BLOCK && 
            get_size_cur_mem_block(block) >= size)
                return get_block(block);
        
        incr_mem_iter(&block);
    }

    return get_block(
        alloc_block_to_frame(frame, size)
    );
}



void*           
alloc_block_to_frame(mem_frame_t* frame, size_t size)
{
    if (frame->size_free_mem <= 0 || frame->size_free_mem < size)
        return NULL;

    frame->size_free_mem -= size;
    frame->count_blocks++;
    return make_mem_block(frame, size);
}




inline
void*           
make_new_mem_frame_and_alloc_in_it(poll_frame_t* frames, size_t size)
{
    push_back_to_list(
        frames, 
        make_mem_frame(eval_new_size_for_mem_frame(frames, size))
    );

    mem_frame_t* new_frame = GET_LK(mem_frame_t, get_back_from_list(frames));

    return get_block(
        alloc_block_to_frame(new_frame, size)
    );
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
make_mem_block(mem_frame_t* frame, size_t size)
{
    void* mem = frame->cur_free_space;

    set_size_cur_mem_block(mem, size);
    set_status_mem_block(mem, NOT_FREE_BLOCK);
    set_size_prev_mem_block(mem, size);
   
    return mem;
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





void*           
get_block(void* mem)
{
    if (mem == NULL)
        return NULL;

    return get_ptr_on_data(mem);
}



inline
void*           
get_ptr_on_mem_block_by_ptr_data(void* data)
{
    return data - SIZE_STATUS_TYPE - sizeof(size_t);
}



inline
size_t          
eval_new_size_for_mem_frame(poll_frame_t* frames, size_t size)
{
    mem_frame_t* back = GET_LK(mem_frame_t, get_back_from_list(frames));

    return (size + back->size_frame) * 2;
}


void            
incr_mem_iter(void** cur_block)
{
    size_t size_cur_block_data = get_size_cur_mem_block(*cur_block);

    (*cur_block) += ((sizeof(size_t) * 2) + SIZE_STATUS_TYPE + size_cur_block_data);
}   




inline
void*           
get_ptr_on_prev_mem_block(void* mem)
{
    size_t size_prev_block_data = *(size_t*)(mem - sizeof(size_t));

    return  (mem - 
            (sizeof(size_t) * 2) - 
            size_prev_block_data - 
            SIZE_STATUS_TYPE);
}




inline
void*           
get_ptr_on_data(void* mem)
{
    return mem + sizeof(size_t) + SIZE_STATUS_TYPE;
}


inline
size_t          
get_size_cur_mem_block(void* mem)
{
    return *(size_t*)(mem);
}


inline
size_t          
get_size_prev_mem_block(void* mem)
{
    size_t size_data = get_size_cur_mem_block(mem);

    return *(size_t*)(mem + sizeof(size_t) + SIZE_STATUS_TYPE + size_data);
}



inline
size_t          
get_status_mem_block(void* mem)
{
    return *(status_t*)(mem + sizeof(size_t));
}


inline
void            
set_size_cur_mem_block(void* mem, size_t size)
{
    *(size_t*)(mem) = size;
}


inline
void            
set_size_prev_mem_block(void* mem, size_t size)
{
    size_t size_data = get_size_cur_mem_block(mem);

    *(size_t*)(mem + sizeof(size_t) + SIZE_STATUS_TYPE + size_data) = size;
}


inline
void            
set_status_mem_block(void* mem, status_t status)
{
    *(status_t*)(mem + sizeof(size_t)) = status;
}




inline
status_t        
is_empty_mem_frame(const mem_frame_t* frame)
{
    return frame->begin == frame->cur_free_space;
}