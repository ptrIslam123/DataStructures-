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
typedef struct node* list_iterator_t;




typedef struct list
{
    struct node*    begin;
    struct node*    end;
    size_t          size_list;

} list_t;


typedef struct node
{
    struct node*    next_node;
    struct node*    prev_node;
    value_t         key;

} node_t;



list_iterator_t begin_itr_list(list_t* );
list_iterator_t end_itr_list(list_t* );
list_iterator_t            incr_list_itr(list_iterator_t );
void            decr_list_itr(list_iterator_t );


unsigned char   is_empty_list(list_t* );    // true -> 1; false -> 0
void            push_back(list_t* , void* );
void            push_front(list_t* , void* );
void            pop_back(list_t* );
void            pop_front(list_t* );

struct list*    make_list();
struct node*    make_node(value_t );

void            free_node(struct node* );
void            free_list_struct(struct list* );
void            clear_list(struct list* );
void            delete_list_struct(struct list* );



#endif // !_LIST_H_
