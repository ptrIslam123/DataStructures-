#ifndef _PRIVATE_POLL_ALLOCATOR_H_
#define _PRIVATE_POLL_ALLOCATOR_H_

#include <stdlib.h>
#include <stdio.h>
#include "../../../list/heder/list.h"

#define START_SIZE_FRAME          (4000)
#define SIZE_FRAME_STRUCT         (sizeof(struct frame))
#define SIZE_MEM_BLOCK_STRUCT     (sizeof(struct mem_block))
#define SIZE_META_DATA            (SIZE_MEM_BLOCK_STRUCT)
#define FREE_BLOCK                (1)
#define NOT_FREE_BLOCK            (0)

#define GET_PTR_ON_DATA(block)    ((void*)blcok + SIZE_META_DATA)
#define GET_PTR_ON_MEM_BLCOK(mem) (mem_block_t*)(mem - SIZE_META_DATA)


typedef unsigned char     status_t;
typedef struct mem_block  mem_block_t;
typedef struct frame      frame_t;
typedef list_t            frames_t;


typedef struct frame
{
  void*               begin;
  mem_block_t*        end;
  void*               cur_free_space;
  mem_block_t*        prev_mem_block;

  size_t              size_frame;
  size_t              size_free_mem;
  size_t              count_blocks;

} frame_t;


typedef struct mem_block
{
   size_t             size_block;
   status_t           status;
   frame_t*           p_frame;

   struct mem_block*  prev_block;
   struct mem_block*  next_block; 

} mem_block_t;


void            preventing_fragmentation_of_memory(mem_block_t** centr_block); 

void            unit_two_blocks_into_one(mem_block_t** lblock, mem_block_t** rblock);

mem_block_t*    get_free_mem_block(size_t size);
mem_block_t*    get_firts_suitable_mem_block(frame_t** frame, size_t size);

void            incr_mem_blcok_itr(mem_block_t** itr);

mem_block_t*    alloc_mem_block_inside_frame(frame_t** frame, size_t size);

mem_block_t*    make_mem_block(frame_t** frame, size_t size);

frame_t*        make_frame(size_t size_frame);

mem_block_t*    make_new_frame_and_alloc_in_it(frames_t** frames, size_t size);

void            free_mem_blcok(mem_block_t** block);
void            free_frames_struct(void);


mem_block_t*    get_ptr_on_prev_mem_block(mem_block_t* block);
mem_block_t*    get_ptr_on_next_mem_block(mem_block_t* block);

void            set_ptr_on_prev_mem_block(mem_block_t* block, mem_block_t* prev_block);
void            set_ptr_on_next_mem_block(mem_block_t* block);

void*           get_ptr_on_data(mem_block_t* block);
mem_block_t*    get_ptr_on_mem_block(void* ptr);

frames_t*       get_frames_struct(void);
void            init_frames_struct(frames_t** frames);
size_t          eval_size_new_frame(frames_t* frames, size_t size);

status_t        is_free_mem_blcok(mem_block_t* block);
status_t        is_empty_frame(frame_t* frame);
status_t        is_last_mem_block_into_frame(mem_block_t* block);
status_t        is_first_mem_block_into_frame(mem_block_t* block);
status_t        is_one_element_into_frame(frame_t* frame);
/*******************************************************************
 
struct frame      |-------|-----------|-----|---------|---------|
                  |       |mem_block_t|     |  ....   |         |
                  |-------|-----------|-----|---------|---------|
                  0       1                                     n -1

                            
                  -------------
struct mem_block  | size_data |
                  -------------
                  |   status  |
                  -------------
                  | ptr_frame |
                  -------------
                  |    DATA   |
                  -------------


*******************************************************************/

#endif // !_PRIVATE_POLL_ALLOCATOR_H_


