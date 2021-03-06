#include "heder/list.h"
#include "heder/private_list_ip.h"
#include <stdio.h>


range_list_itr_t*   
make_range_list_itr(list_t* list, size_t beg)
{
    range_list_itr_t* itr = list->allocate(sizeof(range_list_itr_t));
    itr->list           = list;
    itr->cur_list_node  = begin_list(list);
    itr->counter        = 0;
    
    advance_list(&(itr->cur_list_node), beg);

    return itr;
}



list_t*             
init_list(list_t* list, init_list_t* init)
{
    const size_t size       = init->size_data;
    const size_t size_type  = init->size_dataa_type;
    init_list_value_t data  = init->data;

    for (int i = 0; i < size; ++i)
    {
        push_back_to_list(list, data);
        data += size_type;
    }

    return list;
}

void            
swap_list(list_t* first, list_t* second)
{
    list_iterator_t* fbeg   = first->begin;
    first->begin            = second->begin;
    second->begin           = fbeg;
}




void                
swap_element_list(list_iterator_t** left, list_iterator_t** right)
{
    void* tmp = (*left)->key;
    (*left)->key = (*right)->key;
    (*right)->key = tmp;
}


void                
selection_sort_to_list(list_t* list, list_compare_t is_less)
{
    list_iterator_t* min = NULL;

    for (
        list_iterator_t* i = begin_list(list);
        i != end_list(list);
        incr_list_itr(&i)
    )
    {
        min = min_to_list(is_less, i, end_list(list));
        swap_element_list(&min, &i);
    }
}



list_iterator_t*    
min_to_list(list_compare_t is_less, list_iterator_t* beg, list_iterator_t* end)
{
    list_iterator_t* min = beg;
    incr_list_itr(&beg);

    for (
        list_iterator_t* i = beg;
        i != end;
        incr_list_itr(&i)
    )
        if (is_less(i->key, min->key))
            min = i;
            
    return min;
}



list_iterator_t*    
max_to_list(list_compare_t is_more, list_iterator_t* beg, list_iterator_t* end)
{
    list_iterator_t* max = beg;
    incr_list_itr(&beg);

    for (
        list_iterator_t* i = beg;
        i != end;
        incr_list_itr(&i)
    )
        if (is_more(i->key, max->key))
            max = i;
            
    return max;
}


unsigned char       
range_list(
    range_list_itr_t** itr,
    size_t end,
    size_t step
)
{
    if ((*itr)->counter >= end - 1)
    {
        (*itr)->counter = 0;
        return 0;
    }

    advance_list(
        &(*itr)->cur_list_node,
        step
    );
    (*itr)->counter++;
    return 1;
}



inline
void                
advance_list(list_iterator_t** itr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        incr_list_itr(itr);
    }
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




inline
size_t          
list_size(list_t* list)
{
    return list->size_list;
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








unsigned char           
is_eqi_list(const value_t root, const value_t other)
{
    return *(int*)root == *(int*)other;
}


unsigned char           
is_lessi_list(const  value_t root, const value_t other)
{
    return *(int*)root < *(int*)other;
}

unsigned char           
is_morei_list(const value_t root, const value_t other)
{
    return *(int*)root > *(int*)other;
}