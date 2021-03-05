#include "heder/private_set_ip.h"
#include <stdio.h>

set_iterator_t*         
find_item_to_list(set_t* set, set_value_t val)
{
    list_t* list = set->container;

    for (
        list_iterator_t* i = begin_list(list); 
        i != end_list(list); 
        incr_list_itr(&i)
    )
    {
        if (set->is_eq(val, i->key))
            return i;
    }

    return NULL;
}




list_t*                 
max_set(set_t* sl, set_t* sr)
{
    list_t* ll = sl->container;
    list_t* lr = sr->container;

    if (ll->size_list > lr->size_list)
        return ll;
    return lr;
}


inline
void                    
out_of_range(size_t indx)
{
    fprintf(stdout, "ERROR: out of range to list => index[%d]\n", indx);
    exit(-1);
}