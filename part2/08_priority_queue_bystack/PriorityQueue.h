#pragma once
#include <stdbool.h>
#include <stddef.h>

// 优先队列的抽象数据类型
typedef struct PriorityQueue PQueue;

// 比较函数指针类型
// 如果 data1 的优先级高于 data2，返回负值
// 如果 data1 的优先级低于 data2，返回正值
// 如果优先级相等，返回 0
typedef int (*CompareFunc)(const void* data1, const void* data2);

// 创建优先队列
PQueue* pqueue_create(size_t element_size, CompareFunc compare_func);

// 销毁优先队列
void pqueue_destroy(PQueue** pqueue_p);

// 入队
bool pqueue_enqueue(PQueue* pqueue, const void* element_data);

// 出队
bool pqueue_dequeue(PQueue* pqueue, void* output_buffer);

// 查看队首元素
bool pqueue_peek(PQueue* pqueue, void* output_buffer);

// 检查队列是否为空
bool pqueue_is_empty(PQueue* pqueue);

// 获取队列大小
size_t pqueue_get_size(PQueue* pqueue);
