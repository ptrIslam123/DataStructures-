#include "heder/list.h"



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




void            
insert_to_list(list_t* list, list_iterator_t* itr, void* k)
{
    node_t* new_node = make_node(list->allocate, k);

    new_node->next_node = itr->next_node;
    itr->prev_node      = new_node;

    itr->next_node      = new_node;
    new_node->prev_node = itr;

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




struct node*    
make_node(allocator_t allocate, value_t k)
{
    struct node* new_node = allocate(SIZE_STRUCT_NODE);

    new_node->next_node = NULL;
    new_node->next_node = NULL;
    new_node->key       = k;

    return new_node;
}



inline
void            
free_node(deallocator_t deallocate, struct node* in)
{
    deallocate(in);
    in = NULL;
}


inline
void            
free_list_struct(struct list* list)
{
    list->deallocate(list);
    list = NULL;
}



void            
clear_list(struct list* list)
{
    while (list->begin != NULL)
    {
        pop_front_from_list(list);
    }
}


inline
void            
delete_list_struct(struct list* list)
{
    clear_list(list);
    free_list_struct(list);
}