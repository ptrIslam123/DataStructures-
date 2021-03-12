#ifndef _PRIVATE_POLL_ALLOCATOR_H_
#define _PRIVATE_POLL_ALLOCATOR_H_

#include <stdlib.h>
#include "../../../list/heder/list.h"

#define FREE_BLOCK              (1)
#define NOT_FREE_BLOCK          (0)
#define SIZE_FIRST_MEM_FRAME   (1024) 
#define SIZE_STATUS_TYPE        (sizeof(status_t))
#define SIZE_MEM_FRAME_STRCUT   (sizeof(struct mem_frame))
#define SIZE_HEDER_MEM          (sizeof(size_t) * 2 + SIZE_STATUS_TYPE)

typedef unsigned char   status_t;
typedef list_t          poll_frame_t;

typedef struct mem_frame
{
    void*       begin;
    void*       end;
    void*       cur_free_space;

    size_t      size_frame;
    size_t      size_free_mem;
    size_t      count_blocks;

} mem_frame_t;





/*****************************************************
          struct mem_block
        
        -------------------
        | size_cur_block  |     : size_t
        -------------------
        |    status       |     : unsigned char
        -------------------
        |        D        |
        |        A        |     : void*
        |        T        |
        |        A        |  
        -------------------
        | size_prev_block |     : size_t
        -------------------
        |       .         |
        |       .         |
        |       .         |  
*****************************************************/


void*           get_mem(size_t size);

void*           find_first_suitable_to_frame(mem_frame_t* frame, size_t size);

void*           alloc_block_to_frame(mem_frame_t* frame, size_t size);

void*           make_new_mem_frame_and_alloc_in_it(poll_frame_t* frames, size_t size);

mem_frame_t*    make_mem_frame(size_t size_frame);
void*           make_mem_block(mem_frame_t* frame, size_t size);

poll_frame_t*   get_poll_frame_struct();
poll_frame_t*   init_poll_frame();

size_t          eval_new_size_for_mem_frame(poll_frame_t* frames, size_t size);

void            incr_mem_iter(void** mem);

void*           get_block(void* mem);

void*           get_ptr_on_mem_block_by_ptr_data(void* data);
void*           get_ptr_on_prev_mem_block(void* mem);
void*           get_ptr_on_data(void* mem);
size_t          get_size_cur_mem_block(void* mem);
size_t          get_size_prev_mem_block(void* mem);
size_t          get_status_mem_block(void* mem);

void            set_size_cur_mem_block(void* mem, size_t size);
void            set_size_prev_mem_block(void* mem, size_t size);
void            set_status_mem_block(void* mem, status_t status);

status_t        is_empty_mem_frame(const mem_frame_t* frame);

#endif // !_PRIVATE_POLL_ALLOCATOR_H_


