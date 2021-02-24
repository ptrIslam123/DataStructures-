#ifndef _QUEUE_STRUCT_H_
#define _QUEUE_STRUCT_H_


#include <stdlib.h>

struct queue;
typedef struct queue queue_t;
typedef void* (*allocator_t)(size_t );
typedef void (*deallocator_t)(void* );
typedef void* queue_value_t;

#define SIZE_QUEUE_STRCUT   (sizeof(struct queue))
#define GET_QV(T,V)         ((T*)V)


unsigned char       is_empty_queue(queue_t* );

void                swap_queue(queue_t* , queue_t* );

void                push_to_queue(queue_t* , queue_value_t );
queue_value_t       pop_from_queue(queue_t* );

queue_value_t       get_top_to_queue(queue_t* );

struct queue*       make_std_queue();
struct queue*       make_queue(allocator_t , deallocator_t );

void                free_queue(struct queue* );



#endif // !_QUEUE_STRUCT_H_
