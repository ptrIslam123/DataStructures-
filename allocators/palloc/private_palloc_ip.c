#include "heder/private_palloc_ip.h"
#include "test/test.h"


mem_block_t*    
get_free_mem_block(size_t size)
{
    frames_t* frames = get_frames_struct();

    for (
        list_iterator_t* i = begin_list(frames);
        i != end_list(frames);
        incr_list_itr(&i)
    )
    {
        frame_t* frame = GET_LK(frame_t, i);
        
        mem_block_t* found_block = get_firts_suitable_mem_block(&frame, size);

        if (found_block != NULL)
            return found_block;


        incr_list_itr(&i);
    }

    return make_new_frame_and_alloc_in_it(&frames, size);
}




mem_block_t*    
get_firts_suitable_mem_block(frame_t** frame, size_t size)
{
    frame_t* p_frame    = *frame;
    size_t count        = p_frame->count_blocks;
    mem_block_t* block  = p_frame->begin;

    for (size_t i = 0; i < count; ++i)
    {
        if (is_free_mem_blcok(block) && block->size_block >= size)
        {
            block->status = NOT_FREE_BLOCK;
            return block;
        }

        inc_mem_blcok_itr(&block);
    }

    return alloc_mem_block_inside_frame(frame, size);
}


void            
inc_mem_blcok_itr(mem_block_t** itr)
{
    size_t size_data = (*itr)->size_block;
    void* i = (*itr);
    i += (size_data + SIZE_META_DATA);
}


mem_block_t*    
alloc_mem_block_inside_frame(frame_t** frame, size_t size)
{
    frame_t* pf = *frame;

    if (pf->size_free_mem <= 0 || pf->size_free_mem < size + SIZE_META_DATA)
        return NULL;

    return make_mem_block(frame, size);
}




mem_block_t*    
make_mem_block(frame_t** frame, size_t size)
{
    mem_block_t* free_block     = (mem_block_t*)((*frame)->cur_free_space);

    free_block->size_block      = size;
    free_block->status          = NOT_FREE_BLOCK;
    free_block->p_frame         = *frame;


    (*frame)->size_free_mem     -= size + SIZE_META_DATA;
    (*frame)->cur_free_space    += size + SIZE_META_DATA;
    (*frame)->count_blocks++;

    return free_block;
}



frame_t*        
make_frame(size_t size_frame)
{
    frame_t* new_frame          = malloc(SIZE_FRAME_STRUCT);

    new_frame->begin            = malloc(size_frame);
    new_frame->end              = new_frame->begin + size_frame;
    new_frame->cur_free_space   = new_frame->begin;

    new_frame->size_frame       = size_frame;
    new_frame->size_free_mem    = size_frame;
    new_frame->count_blocks     = 0;

    return new_frame;
}



mem_block_t*    
make_new_frame_and_alloc_in_it(frames_t** frames, size_t size)
{
    frame_t* new_frame = make_frame(
        eval_size_new_frame(*frames, size)
    );

    push_back_to_list(*frames, new_frame);

    return alloc_mem_block_inside_frame(&new_frame, size);
}


void
free_mem_blcok(mem_block_t** block)
{
    (*block)->status = FREE_BLOCK;
    /* usint two free blocks */
}


void            
free_frames_struct(void)
{
    frames_t* frames = get_frames_struct();
    free_list(frames);
}




frames_t*       
get_frames_struct(void)
{
    frames_t* frames = NULL;

    if (frames == NULL)
        init_frames_struct(&frames);

    return frames;
}



void            
init_frames_struct(frames_t** frames)
{
    (*frames) = make_std_list();
    push_back_to_list(*frames, make_frame(START_SIZE_FRAME));
}



size_t          
eval_size_new_frame(frames_t* frames, size_t size)
{
    list_iterator_t* p_frame = get_back_from_list(frames);    
    frame_t* back = *GET_LK(frame_t*, p_frame);

    return (back->size_frame + size) * 2;
}



inline
status_t        
is_free_mem_blcok(mem_block_t* block)
{
    return block->status == FREE_BLOCK;
}