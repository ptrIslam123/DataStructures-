#include "heder/list.h"



inline
list_iterator_t 
begin_itr_list(list_t* list)
{
    return list->begin;
}


inline
list_iterator_t 
end_itr_list(list_t* list)
{
    return list->end->next_node;
}


inline
list_iterator_t            
incr_list_itr(list_iterator_t itr)
{
    itr = itr->next_node;
    return itr;
}



inline
void 
decr_list_itr(list_iterator_t itr)
{
    itr = itr->prev_node;
}



unsigned char   
is_empty_list(list_t* list)
{
    if (!list->size_list)   // true -> is not empty (1)
        return 1; 
    return 0;               // false -> is empty    (0)
}

void            
push_back(list_t* list, void* k)
{
    node_t* new_node = make_node(k);

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
push_front(list_t* list, value_t k)
{
    node_t* new_node = make_node(k);

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
pop_back(list_t* list)
{
    if (is_empty_list(list) == IS_NOT_EMPTY)
        return;

    node_t* tmp = list->end;
    list->end   = tmp->prev_node;
    list->end->next_node = NULL;

    free_node(tmp);
    list->size_list--;
}


void           
pop_front(list_t* list)
{
    if (is_empty_list(list) == IS_NOT_EMPTY)
        return;

    node_t* tmp = list->begin;
    list->begin = tmp->next_node;

    free_node(tmp);
    list->size_list--;
}



struct list*    
make_list()
{
    struct list* new_list = malloc(SIZE_STRCUT_LIST);

    new_list->begin     = NULL;
    new_list->end       = NULL;
    new_list->size_list = 0;

    return new_list;
}


struct node*    
make_node(value_t k)
{
    struct node* new_node = malloc(SIZE_STRUCT_NODE);

    new_node->next_node = NULL;
    new_node->next_node = NULL;
    new_node->key       = k;

    return new_node;
}



inline
void            
free_node(struct node* in)
{
    free(in);
    in = NULL;
}


inline
void            
free_list_struct(struct list* list)
{
    free(list);
    list = NULL;
}



void            
clear_list(struct list* list)
{
    while (list->begin != NULL)
    {
        pop_front(list);
    }
}


inline
void            
delete_list_struct(struct list* list)
{
    clear_list(list);
    free_list_struct(list);
}