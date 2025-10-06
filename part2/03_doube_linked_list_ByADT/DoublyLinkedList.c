#define _CRT_SECURE_WARNINGS
#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <errno.h>
 
// Internal data structure for the doubly linked list

struct DListNode
{
    void *data;
    struct DListNode *next;
    struct DListNode *prev;
};

// 内存池：用于高效地管理链表节点 DListNode
typedef struct MemoryPool
{
    DListNode *pool_memory;     // 指向memory pool的起始地址
    DListNode *free_list_head;  // 指向内存池中第一个可用（空闲）节点的指针
} MemoryPool;

/**
 * 双向链表结构体定义
 * 包含链表的基本信息和内存池管理
 */
struct DoublyLinkedList{
    DListNode* head;            // 指向链表的头节点
    DListNode* tail;            // 指向链表的尾节点
    size_t size;                // 链表中当前节点的数量
    mtx_t lock;                 // 用于线程同步的互斥锁  确保多线程环境下的安全访问
    MemoryPool* pool;           // 指向关联的内存池
    FreeFunc user_free_func;    // 用户自定义的内存释放函数指针
} ;

// Function to create to a new memory pool

static MemoryPool* MemoryPool_Create(size_t initial_capacity)
{
    if(initial_capacity==0){
        perror("Invalid initial capacity for memory pool");
        return NULL;
    }
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool));
    if(!pool){
        perror("Failed to allocate memory for memory pool");
        return NULL;
    }

    pool->pool_memory=(DListNode*)malloc(initial_capacity*sizeof(DListNode));
    if(!pool->pool_memory){
        perror("Failed to allocate memory for pool nodes");
        free(pool);
        return NULL;
    }

    pool->free_list_head=pool->pool_memory;
    for(size_t i=0;i<initial_capacity-1;++i)
    {
        pool->pool_memory[i].next=&pool->pool_memory[i+1];
    }
    pool->pool_memory[initial_capacity-1].next=NULL;

    return pool;
}