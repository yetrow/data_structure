#include "GenericCircularQueue.h"
#include <stdlib.h>
#include <string.h>

struct CircularQueue 
{
    void* data;
    size_t capacity;
    size_t element_size;
    size_t size;
    int front;
    int rear;
} ;


Queue* queue_create(size_t capacity, size_t element_size)
{
    if(capacity ==0 || element_size == 0)   return NULL;

    Queue* q =(Queue*)malloc(sizeof(Queue));
    if(!q) return NULL;

    q->data = malloc(capacity * element_size);
    if(!q->data)
    {
        free(q);
        return NULL;
    }

    q->capacity = capacity;
    q->element_size = element_size;
    q->size = 0;
    q->front = 0;
    q->rear = 0;

    return q;
}


void queue_destroy(Queue** queue_p)
{
    if(queue_p && *queue_p)
    {
        free((*queue_p)->data);
        free(*queue_p);
        // 防止悬空指针
        *queue_p = NULL;    
    }
}

bool queue_enqueue(Queue* queue, const void* element_data)
{
    if(!queue || !element_data)     return false;
    // 检查队列是否已满
    if(queue->size == queue->capacity)  return false;
    // 计算要插入元素的物理地址
    void* address = (char*)queue->data + (queue->rear * queue->element_size);
    memcpy(address, element_data, queue->element_size);
    // 更新队尾 rear 指针，实现循环
    // 模运算 % ，是循环队列的灵魂
    // 比如 rear为0
    // 新的 rear = (0 + 1) % 4 = 1;
    // rear 指针指向了下一个空位，索引1
    queue->rear = (queue->rear + 1) % queue->capacity;

    // 更新队列的大小
    queue->size++;
    return true;
}

bool queue_dequeue(Queue* queue, void* output_buffer)
{
    if(!queue || !output_buffer)    return false;

    if(queue->size == 0)    return false;
    // 计算头元素的物理内存地址
    void* address = (char*)queue->data + (queue->front * queue->element_size);
    memcpy(output_buffer, address, queue->element_size);

    queue->front = (queue->front + 1) % queue->capacity;

    queue->size--;
    return true;
}

bool queue_peek(const Queue* queue, void* output_buffer)
{
    if(!queue || !output_buffer)    return false;

    if(queue->size == 0)    return false;

    void* address = (char*)queue->data + (queue->front * queue->element_size);
    memcpy(output_buffer, address, queue->element_size);

    return true;
}

bool queue_is_empty(const Queue* queue)
{
    // 一个不存在的队列可以视为空
    if(!queue)    return true;
    return queue->size == 0;
}

bool queue_is_full(const Queue* queue)
{
    // 一个不存在的队列可以视为满，以防止错误地对其进行操作
    if(!queue)    return true;
    return queue->size == queue->capacity;
}

size_t queue_get_size(const Queue* queue)
{
    if(!queue)  return 0;
    return queue->size;
}

size_t  queue_get_capacity(const Queue* queue)
{
    if(!queue)    return 0;

    return queue->capacity;
}