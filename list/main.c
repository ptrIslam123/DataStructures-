#include <stdio.h>
#include "heder/list.h"
#include "heder/test.h"


#define print_list(T, L)                                    \
            for (list_iterator_t*   i = begin_list(L);      \
                            i != end_list(L);               \
                            incr_list_itr(&i))              \
            {                                               \
                printf("k = %c\n", *GET_LK(T, i));           \
            }                                                         




typedef struct point
{
    int x,y;
} point_t;

point_t* make_point(int _x, int _y)
{
    point_t* new_point = malloc(sizeof(point_t));

    new_point->x = _x;
    new_point->y = _y;

    return new_point;
}

char* make_char(char c)
{
    char* nc = malloc(sizeof(char));
    *nc = c;

    return nc;
}

int main()
{
    const int size = 10;
    list_t* listc = make_std_list();
    list_t* listp = make_std_list();

    for (int i = 0; i < size; ++i)
    {
        point_t*    p = make_point(i, i + 10);
        char*       c = make_char('$');

        push_back_to_list(listp, p);
        push_back_to_list(listc, c);
    }


    for (list_iterator_t* i = rbegin_list(listp); i != rend_list(listp); rincr_list_itr(&i))
    {
       
        int vx = (GET_LK(point_t, i))->x;

        int vy = ((point_t*)i->key)->y;
        printf("x = %d\t\ty = %d\n", vx, vy);
    }


    swap_list(listc, listp);

    

    return 0;
}