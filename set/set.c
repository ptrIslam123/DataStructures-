#include "heder/set.h"
#include "heder/private_set_ip.h"
#include <stdio.h>


set_t*                    
init_set(set_t* set, struct init_list* init)
{
    const size_t size       = init->size_data;
    const size_t size_type  = init->size_dataa_type;
    init_list_value_t data  = init->data;

    for (int i = 0; i < size; ++i)
    {
        push_to_set(set, data);
        data += size_type;
    }

    return set;
}

inline
unsigned char       
is_empty_set(set_t* set)
{
    return is_empty_list(set->container);
}


/* проверяет принадлежит ли элемент данному множеству */
inline
unsigned char       
in_here(set_t* set, set_value_t val)
{   
    if (find_item_to_list(set, val) != NULL)
        return 1;
    return 0;
}


inline
size_t              
set_size(set_t* set)
{
    return set->container->size_list;
}


/* 
    операция проверки на то 
    ялвяется ли одно множество подмножеством другого множества 
    A c B = {x | x з B}, где э - знак принадлежит
*/
unsigned char       
is_sub_set(set_t* sA, set_t* sB)
{
    list_t* A = sA->container;

    for (
        list_iterator_t* a = begin_list(A);
        a != end_list(A);
        incr_list_itr(&a)
    )
    {
        if (!in_here(sB, a->key))
            return 0;
    }
    return 1;
}



/* 
    операция для проверку  пересекаемости двух множеств
    A ^ B = {x | x э A && x э B}
*/
set_t*              
intersection_set(set_t* sA, set_t* sB, set_t* new_set)
{
    list_t* C = max_set(sA, sB);

    for (
        list_iterator_t* c = begin_list(C);
        c != end_list(C);
        incr_list_itr(&c)
    )
    {
        if (in_here(sA, c->key) && in_here(sB, c->key))
            push_to_set(new_set, c->key);
    }
    return new_set;
}



/* 
    операция обьединения двух множеств 
    A u B = {x | x э A || x э B}
*/
set_t*              
union_set(set_t* sA, set_t* sB, set_t* new_set)
{
    list_t* A = sA->container;
    list_t* B = sB->container;

    for (
        list_iterator_t* a = begin_list(A);
        a != end_list(A);
        incr_list_itr(&a)
    )
    {
        push_to_set(new_set, a->key);
    }


    for (
        list_iterator_t* b = begin_list(B);
        b != end_list(B);
        incr_list_itr(&b)
    )
    {
        push_to_set(new_set, b->key);
    }

    return new_set;
}



/* 
    операция разности для множеств 
    A \ B = {x | x э A && x ^э B}, где ^э - не принадлежит
*/
set_t*              
difference_set(set_t* sA, set_t* sB, set_t* new_set)
{
    list_t* C = max_set(sA, sB);

    for (
        list_iterator_t* c = begin_list(C);
        c != end_list(C);
        incr_list_itr(&c)
    )
    {
        if (in_here(sA, c->key) && !in_here(sB, c->key))
            push_to_set(new_set, c->key);
    }

    return new_set;
}


void                
push_to_set(set_t* set, set_value_t val)
{
    if (find_item_to_list(set, val) == NULL)
        push_back_to_list(set->container, val);
}


set_value_t*                
pop_from_set(set_t* set, size_t indx)
{
    list_t* list = set->container;
    size_t j = 0;

    if (indx >= list->size_list)
        out_of_range(indx);

    for (
        list_iterator_t* i = begin_list(list);
        i != end_list(list);
        incr_list_itr(&i)
    )
    {
        if (j == indx)
            return (i->key);
        j++;
    }
    return NULL;
}


void                
remove_from_set(set_t* set, size_t indx)
{
    list_t* list = set->container;
    size_t j = 0;

    if (indx >= list->size_list)
        out_of_range(indx);

    for (
        list_iterator_t* i = begin_list(list);
        i != end_list(list);
        incr_list_itr(&i)
    )
    {
        if (j == indx)
            remove_from_list(list, i);
        j++;
    }
}


struct set*         
make_std_set(
    set_compare_t is_eq, 
    set_compare_t is_less, 
    set_compare_t is_more)
{
    set_t* new_set = malloc(SIZE_SET_STRCUT);

    new_set->container  = make_std_list();
    new_set->is_eq      = is_eq;
    new_set->is_less    = is_less;
    new_set->is_more    = is_more;
    
    return new_set;
}


struct set*         
make_set(
    set_compare_t is_eq,
    set_compare_t is_less,
    set_compare_t is_more,
    allocator_t allocate, 
    deallocator_t deallocate
)
{
    set_t* new_set = malloc(SIZE_SET_STRCUT);

    new_set->container  = make_list(allocate,  deallocate);
    new_set->is_eq      = is_eq;
    new_set->is_less    = is_less;
    new_set->is_more    = is_more;

    return new_set;
}


void                
free_set(struct set* set)
{
    free_list(set->container);
    free(set);
    set = NULL;
}



unsigned char           
is_eqi_set(const set_value_t root, const set_value_t other)
{
    return *(int*)root == *(int*)other;
}


unsigned char           
is_lessi_set(const  set_value_t root, const set_value_t other)
{
    return *(int*)root < *(int*)other;
}

unsigned char           
is_morei_set(const set_value_t root, const set_value_t other)
{
    return *(int*)root > *(int*)other;
}

