#include "heder/list.h"
#include "heder/private_list_ip.h"
#include <stdio.h>

void            
swap_list(list_t* first, list_t* second)
{
    list_iterator_t* fbeg   = first->begin;
    first->begin            = second->begin;
    second->begin           = fbeg;
}





inline
list_iterator_t*    
rbegin_list(list_t* list)
{
    return list->end;
}


inline
list_iterator_t*    
rend_list(list_t* list)
{
    return NULL;    // list->begin->prev_node <-> NULL
}


inline
list_iterator_t*    
begin_list(list_t* list)
{
    return list->begin;
}


inline
list_iterator_t*    
end_list(list_t* list)
{
    return NULL;    // list->end->next_node <-> NULL;
}




inline
void            
rincr_list_itr(rlist_iterator_t** ritr)
{
    decr_list_itr(ritr);
}

inline
void            
rdecr_list_itr(rlist_iterator_t** ritr)
{
    incr_list_itr(ritr);
}


inline
void            
incr_list_itr(list_iterator_t** itr)
{
    *itr = (*itr)->next_node;
}


inline
void            
decr_list_itr(list_iterator_t** itr)
{
    *itr = (*itr)->prev_node;
}





unsigned char   
is_empty_list(list_t* list)
{
    if (!list->size_list)   // true -> is not empty (1)
        return 1; 
    return 0;               // false -> is empty    (0)
}

void            
push_back_to_list(list_t* list, void* k)
{
    node_t* new_node = make_node(list->allocate, k);

    if (is_empty_list(list) == IS_NOT_EMPTY)
    {
        list->begin = new_node;
        list->end   = new_node;
    }
    else
    {
        list->end->next_node    = new_node;
        new_node->prev_node     = list->end;
        list->end               = new_node;
    }
    list->size_list++;
}


void            
push_front_to_list(list_t* list, value_t k)
{
    node_t* new_node = make_node(list->allocate, k);

    if (is_empty_list(list) == IS_NOT_EMPTY)
    {
        list->begin = new_node;
        list->end   = new_node;
    }
    else
    {
        new_node->next_node     = list->begin;
        list->begin->prev_node  = new_node;
        list->begin             = new_node;
    }
    list->size_list++;
}


void           
pop_back_from_list(list_t* list)
{
    if (is_empty_list(list) == IS_NOT_EMPTY)
        return;

    node_t* tmp = list->end;
    list->end   = tmp->prev_node;
    list->end->next_node = NULL;

    free_node(list->deallocate, tmp);
    list->size_list--;
}


void           
pop_front_from_list(list_t* list)
{
    if (is_empty_list(list) == IS_NOT_EMPTY)
        return;

    node_t* tmp = list->begin;
    list->begin = tmp->next_node;

    free_node(list->deallocate, tmp);
    list->size_list--;
}




inline
list_iterator_t*         
get_front_from_list(list_t* list)
{
    if (!list->size_list)
        return NULL;

    return list->begin;
}


inline
list_iterator_t*         
get_back_from_list(list_t* list)
{
    if (!list->size_list)
        return NULL;

    return list->end;
}




void            
insert_to_list(list_t* list, list_iterator_t* itr, void* k)
{
    node_t* new_node = make_node(list->allocate, k);

    if (itr != list->begin)
    {
        node_t* prev        = itr->prev_node;

        prev->next_node     = new_node;
        new_node->prev_node = prev;

        new_node->next_node = itr;
        itr->prev_node      = new_node;
    }
    else
    {
        new_node->next_node = itr;
        itr->prev_node      = new_node;
        list->begin         = new_node;    
    }

    list->size_list++;
}


void            
remove_from_list(list_t* list, list_iterator_t* itr)
{
    if (!list->size_list)
        return;
    
    if (itr == list->begin)
    {
        pop_front_from_list(list);
    }
    else if (itr == list->end)
    {
        pop_back_from_list(list);
    }
    else
    {
        (itr->prev_node)->next_node = itr->next_node;
        (itr->next_node)->prev_node = itr->prev_node;

        free_node(list->deallocate, itr);

        list->size_list--;  
    }
}



struct list*    
make_std_list()
{
    struct list* new_list = malloc(SIZE_STRCUT_LIST);

    new_list->begin     = NULL;
    new_list->end       = NULL;
    new_list->size_list = 0;

    new_list->allocate      = malloc;
    new_list->deallocate    = free;

    return new_list;
}


struct list*    
make_list(allocator_t alloc, deallocator_t dealloc)
{
    struct list* new_list = malloc(SIZE_STRCUT_LIST);

    new_list->begin     = NULL;
    new_list->end       = NULL;
    new_list->size_list = 0;

    new_list->allocate      = alloc;
    new_list->deallocate    =  dealloc;

    return new_list;
}




inline
void            
free_list(struct list* list)
{
    clear_list(list);
    free_list_struct(list);
}