#ifndef _PRIVATE_POLL_ALLOCATOR_H_
#define _PRIVATE_POLL_ALLOCATOR_H_

#include <stdlib.h>
#include "../../../list/heder/list.h"

#define FREE_BLOCK              (1)
#define NOT_FREE_BLOCK          (0)
#define SIZE_FIRST_POLL_FRAME   (1024) 
#define SIZE_MEM_FRAME_STRCUT   (sizeof(struct mem_frame))
#define SIZE_MEM_BLOCK_STRUCT   (sizeof(struct mem_block))



typedef unsigned char   status_t;
typedef list_t          poll_frame_t;

typedef struct mem_frame
{
    void*       mem;
    void*       cur_free_place;
    size_t      size_frame;
    status_t    status_frame;

} mem_frame_t;


typedef struct mem_block
{
    size_t      size_block;
    status_t    status_block;

} mem_block_t;



mem_block_t*        get_free_mem_block_to_poll_frame(size_t size);
mem_block_t*        find_fisrt_suitable_mem_block_to_frame(mem_frame_t* , size_t size);

void                unit_two_free_mem_block(mem_block_t* );

struct mem_block*   make_mem_block_to_frame(mem_frame_t* frame, size_t siz);
struct mem_frame*   make_mem_frame(poll_frame_t* , size_t size_frame);


poll_frame_t*       get_poll_frame();


#endif // !_PRIVATE_POLL_ALLOCATOR_H_
#define typedef unsigned char status_t;

