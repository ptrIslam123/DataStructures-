#include "../list/heder/list.h"
#include "heder/queue.h"


typedef struct queue
{
    struct list* container;
} queue_t;





queue_t*            
init_queue(queue_t* queue, struct init_list* init)
{
    const size_t size       = init->size_data;
    const size_t size_type  = init->size_dataa_type;
    init_list_value_t data  = init->data;

    for (int i = 0; i < size; ++i)
    {
        push_to_queue(queue, data);
        data += size_type;
    }

    return queue;
}

inline
unsigned char       
is_empty_queue(queue_t* queue)
{
    return is_empty_list(queue->container);   
}



inline
void                
swap_queue(queue_t* l, queue_t* r)
{
    swap_list(l->container, r->container);
}


inline
void                
push_to_queue(queue_t* queue, queue_value_t val)
{
    push_back_to_list(queue->container, val);
}



inline
queue_value_t       
pop_from_queue(queue_t* queue)
{
    if (is_empty_list(queue->container))
        return NULL;

    list_iterator_t* front = get_front_from_list(queue->container);
    queue_value_t front_val = front->key;
    remove_from_list(queue->container, front);

    return front_val;
}


inline
queue_value_t       
get_top_to_queue(queue_t* queue)
{
    return get_front_from_list(queue->container)->key;
}



struct queue*       
make_std_queue()
{
    struct queue* new_queue = malloc(SIZE_QUEUE_STRCUT);
    new_queue->container    = make_std_list();

    return new_queue;
}


struct queue*       
make_queue(allocator_t allocate, deallocator_t deallocate)
{
    struct queue* new_queue = malloc(SIZE_QUEUE_STRCUT);
    new_queue->container    = make_list(allocate, deallocate);

    return new_queue;
}


inline
void                
free_queue(struct queue* pqueue)
{
    free_list(pqueue->container);
    free(pqueue);

    pqueue = NULL;
}
