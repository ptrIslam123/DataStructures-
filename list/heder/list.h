#ifndef _LIST_H_
#define _LIST_H_

#include <stdlib.h>

#define SIZE_STRUCT_NODE (sizeof(struct node))
#define SIZE_STRCUT_LIST (sizeof(struct list))
#define NULL_VALUE       (NULL)
#define IS_NOT_EMPTY        (1)
#define IS_EMPTY            (0)


struct list;
struct node;
struct list_iterator;

typedef void* value_t;
typedef struct node list_iterator_t;

typedef void* (*allocator_t)(size_t);
typedef void (*deallocator_t)(void*);



typedef struct list
{
    struct node*    begin;
    struct node*    end;
    size_t          size_list;

    allocator_t     allocate;
    deallocator_t   deallocate;

} list_t;


typedef struct node
{
    struct node*    next_node;
    struct node*    prev_node;
    value_t         key;

} node_t;


//      GET_LIST_KEY
#define GET_LK(T, list_itr) (*(T*)list_itr->key) 


void            incr_list_itr(list_iterator_t** );
void            decr_list_itr(list_iterator_t** );


unsigned char   is_empty_list(list_t* );    // true -> 1; false -> 0
void            push_back_to_list(list_t* , void* );
void            push_front_to_list(list_t* , void* );
void            pop_back_from_list(list_t* );
void            pop_front_from_list(list_t* );

void            insert_to_list(list_t* , list_iterator_t* , void* );
void            remove_from_list(list_t* , list_iterator_t* );


struct list*    make_std_list();
struct list*    make_list(allocator_t , deallocator_t );
struct node*    make_node(allocator_t , value_t );

void            free_node(deallocator_t , struct node* );
void            free_list_struct(struct list* );
void            clear_list(struct list* );
void            delete_list_struct(struct list* );



#endif // !_LIST_H_
