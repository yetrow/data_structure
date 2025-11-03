#include "Deque.h"
#include <stdlib.h>
#include <string.h>

struct Deque
{
    void* data;
    size_t capacity;
    size_t element_size;
    size_t size;
    int front;
    int rear;
} ;

Deque* deque_create(size_t capacity, size_t element_size)
{
    if(capacity ==  0 || element_size == 0) return NULL;
    Deque* dq = (Deque*)malloc(sizeof(Deque));
    if(!dq) return NULL;

    dq->data = malloc(capacity * element_size);
    if(!dq->data)
    {
        free(dq);
        return NULL;
    }
    dq->capacity = capacity;
    dq->element_size = element_size;
    dq->size = 0;
    dq->front = 0;
    dq->rear = 0;

    return dq;
}

void deque_destory(Deque** deque_p)
{
    if(*deque_p && deque_p)
    {
        free((*deque_p)->data);
        free(*deque_p);
        *deque_p = NULL;
    }
}

bool deque_push_back(Deque* dq, const void* element_data)
{
    if(!dq || !element_data || deque_is_full(dq))   return false;

    void* address = (char*)dq->data + (dq->rear * dq->element_size);
    memcpy(address, element_data, dq->element_size);
    dq->rear = (dq->rear + 1) % dq->capacity;
    dq->size++;
    return true;
}

bool deque_push_front(Deque* dq, const void* element_data)
{
    if(!dq || !element_data || deque_is_full(dq))   return false;
    //现在问题来了，如果 `front` 已经指向了数组的最后一个位置（比如索引是 `capacity - 1`），这时再 `+ 1`，索引就会变成 `capacity`，
    //这会超出数组的边界，导致程序错误（数组越界）。
    //这就是 `% capacity` 发挥作用的地方了。它保证了 `+ 1` 之后的结果永远不会越界，而是能平滑地“绕回”到数组的开头。
    dq->front = (dq->front - 1 + dq->capacity) % dq->capacity;
    void* address = (char*)dq->data + (dq->front * dq->element_size);
    memcpy(address, element_data, dq->element_size);

    dq->size++;
    return true;
}

bool deque_pop_back(Deque* dq, void* output_buffer)
{
    if(!dq || !output_buffer || deque_is_empty(dq)) return false;
    dq->rear = (dq->rear - 1 + dq->capacity) % dq->capacity; 
    void* address = (char*)dq->data + dq->rear * dq->element_size;

    memcpy(output_buffer, address, dq->element_size);
    dq->size--;
    return true;
}

bool deque_pop_front(Deque* dq, void* output_buffer)
{
    if(!dq || !output_buffer || deque_is_empty(dq)) return false;
    void* address = (char*)dq->data + dq->front * dq->element_size;

    memcpy(output_buffer, address, dq->element_size);
    dq->front = (dq->front + 1) % dq->capacity;
    dq->size--;
    return true;
}

bool deque_peek_front(Deque* dq, void* output_buffer)
{
    if(!dq || !output_buffer || deque_is_empty(dq)) return false;

    void* address = (char*)dq->data + dq->front * dq->element_size;

    memcpy(output_buffer, address, dq->element_size);

    return true;    
}

bool deque_peek_back(Deque* dq, void* output_buffer)
{
    if(!dq || !output_buffer || deque_is_empty(dq)) return false;

    int last_index = (dq->rear - 1 + dq->capacity) % dq->capacity;
    void* address = (char*)dq->data + last_index * dq->element_size;

    memcpy(output_buffer, address, dq->element_size);

    return true;
}


bool deque_is_empty(Deque* dq)
{
    return !dq || dq->size == 0;
}

bool deque_is_full(Deque* dq)
{
    return !dq || dq->size == dq->capacity;
}

size_t deque_get_size(Deque* dq)
{
    return dq ? dq->size : 0;
}
