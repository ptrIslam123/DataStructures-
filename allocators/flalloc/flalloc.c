#include "../../list/heder/list.h"
#include "heder/flalloc.h"


#define SIZE_MEM_BLOCK  (sizeof(struct mem_block))
#define FREE_BLOCK      (1)
#define NOT_FREE_BLOCK  (0)

typedef list_t          free_list_t;
typedef unsigned char   status_t;


typedef struct mem_block
{
    size_t      size_block;
    status_t    status;

} mem_block_t;




free_list_t*        get_free_list_struct();
void*               get_memory(size_t );
mem_block_t*        find_free_block(size_t );
void                add_mem_block_to_free_list(mem_block_t* );
mem_block_t*        make_mem_block(size_t );
unsigned char       is_less_mem_block(value_t , value_t );




void* 
flalloc(size_t size)
{
    void* mem = get_memory(size);
    return mem + SIZE_MEM_BLOCK;
}


void 
flfree(void* pobj)
{
    mem_block_t* free_block = (mem_block_t*)(pobj - SIZE_MEM_BLOCK);
    free_block->status      = FREE_BLOCK;

    add_mem_block_to_free_list(free_block);
}




free_list_t*        
get_free_list_struct()
{
    static status_t is_init     = 0;
    static free_list_t* list    = NULL;

    if (!is_init)
    {
        is_init = 1;
        list    = make_std_list();
    }

    return list;
}


void*               
get_memory(size_t size)
{
    mem_block_t* free_block = find_free_block(size);

    if (free_block != NULL)
    {
        printf("[DEBUG_INF]reused mem_block->size = %d\n", size);
        return free_block;
    }
    
    return make_mem_block(size);
}


/*
        В данном методе мы ищем блок подходящего размера.
    Для этого мы проходим список свободных блоков от начала до конца,
    до тех пор, пока не встретим первый блок подходящего размера.
    Нам нужно найти первый подходящий блок, так как список отсортирован
    по возрастанию, а значит что после первого подходящего блока идут
    блоки еще большего размера брать которые нам не выгодно, так как 
    это увеличит фрагментацию памяти. За счет того что список отсортирован по возрастанию
    нам нет необходимости просматривать весь список что лучше сказывается на 
    производительности в среднем, но наихудший случай все же будет O(n).
*/
mem_block_t*        
find_free_block(size_t need_size_block)
{
    free_list_t* list = get_free_list_struct();

    for (
        list_iterator_t* i = begin_list(list);
        i != end_list(list);
        incr_list_itr(&i)
    )
    {
        mem_block_t* block = (GET_LK(mem_block_t, i));
        if (block->size_block >= need_size_block)
            return block;
    }

    return NULL;
}


/*
    Данный метод добавляет очередной освободившийся блок памяти и 
    добовляет его в список свободных к остальным, после чего весь 
    список сортируется.
*/
void                
add_mem_block_to_free_list(mem_block_t* free_block)
{
    free_list_t* list = get_free_list_struct();

    push_back_to_list(list, free_block);
    selection_sort_to_list(list, is_less_mem_block);
}



unsigned char       
is_less_mem_block(value_t first, value_t second)
{
    mem_block_t* fblock = (mem_block_t*)first;
    mem_block_t* sblock = (mem_block_t*)second;

    return (fblock->size_block < sblock->size_block);
}

/*
    Данный метод преднозначен для аллоцирования на куче 
    структуры данных mem_block_t.
    Функция выделения аллоцирует и распределяет память немного странно
    на первый взгляд. Принцип тут в том, что мы аллоцируем сырую
    память размеров сумму и струтктуры mem_blcok_t и размера запрашиваемой
    памяти, затем эту сырую память распределяют так что бы, первую часть
    отдать под саму структуру mem_block_t а вторую под поле data в самой структуре.
    Данный способ позволяет компактнее пакавать данные, что положительно скажется на 
    кеширований данных. 
*/
mem_block_t*        
make_mem_block(size_t size_block)
{
    const size_t total_size = SIZE_MEM_BLOCK + size_block;

    mem_block_t* new_blcok  = malloc(total_size);
    
    new_blcok->size_block   = size_block;
    new_blcok->status       = FREE_BLOCK;

    return new_blcok;
}



inline
void    
free_free_list_struct()
{
    free_list(get_free_list_struct());
}