#ifndef _PRIVATE_SET_STRUCT_H_
#define _PRIVATE_SET_STRUCT_H_

#include "../../list/heder/list.h"
#include "set.h"

typedef list_t          container_t;
typedef list_iterator_t set_iterator_t;


typedef struct set
{
    container_t*        container;
    set_compare_t       is_eq;
    set_compare_t       is_less;
    set_compare_t       is_more;

} set_t;


set_iterator_t*         find_item_to_list(set_t* , set_value_t );
list_t*                 max_set(set_t* , set_t* );

void                    out_of_range(size_t indx);


#endif // !_PRIVATE_SET_STRUCT_H_