#include "test/test.h"
#include "heder/flalloc.h"

int* 
test_make_array(int size)
{
    int* arr = flalloc(sizeof(int) * size);

    for (int i = 0; i < size; ++i)
    {
        arr[i] = rand() % 100;
    }

    return arr;
}


void 
test_array_sum(int* arr1, int* arr2, int size)
{
    for (int i = 0; i <  size; ++i)
    {
        arr1[i] += arr2[i] + arr1[i]; 
    }
}