#define _CRT_SECURE_WARNINGS
#include "DoublyLinkedList.h"
#include <stdlib.h>
#include <stdio.h>
#include <threads.h>
#include <errno.h>
 
// Internal data structure for the doubly linked list

/**
 * 双向链表节点结构体定义
 * 该结构体用于构建双向链表，每个节点包含数据域和两个指针域
 */
struct DListNode
{
    void *data;    // 数据域，使用void指针以支持任意数据类型
    struct DListNode *next;  // 指向后继节点的指针
    struct DListNode *prev;  // 指向前驱节点的指针
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
    MemoryPool* pool = (MemoryPool*)malloc(sizeof(MemoryPool)); //  为内存池结构体分配内存
    if(!pool){
        perror("Failed to allocate memory for memory pool");
        return NULL;
    }

    pool->pool_memory=(DListNode*)malloc(initial_capacity*sizeof(DListNode)); //  为内存池中的节点数组分配内存
    if(!pool->pool_memory){
        perror("Failed to allocate memory for pool nodes");
        free(pool);
        return NULL;
    }

    pool->free_list_head=pool->pool_memory; //  初始化空闲链表头指针，指向内存池的起始地址
    for(size_t i=0;i<initial_capacity-1;++i) //  遍历内存池，将每个内存块的next指针指向下一个内存块，形成空闲链表
    {
        pool->pool_memory[i].next=&pool->pool_memory[i+1];
    }
    pool->pool_memory[initial_capacity-1].next=NULL; //  设置最后一个内存块的next指针为NULL，表示链表结束

    return pool;
}

static void MemoryPool_Destroy(MemoryPool* pool)
{
    if(!pool)   return ;
    free(pool->pool_memory);
    free(pool);
}

static DListNode* MemoryPool_AllocateNode(MemoryPool* pool)
{
    if(!pool || !pool->free_list_head) //  检查内存池指针或空闲链表头是否为空
    {
        return NULL;
    }

    DListNode* node = pool->free_list_head; //  从空闲链表头获取一个节点
    pool->free_list_head = node->next; //  将空闲链表的头指针更新为下一节点

    return node;
}

// 将洗干净的盘子放回盘子堆
// 将一个不再使用的节点归还给内存池  O(1)
static void MemoryPool_FreeNode(MemoryPool* pool, DListNode* node)
{
    if(!pool || !node)  return ;
    // 将节点添加回空闲列表
    // 将要释放的节点的 next 指向当前空闲列表的头结点
    node->next = pool->free_list_head; 
    // 更新空闲列表的头结点为当前释放的节点
    pool->free_list_head = node; 
}

// 实例的工厂函数（设计模式）
/*
通过在 `List_Create` 时传入 `free_func`，
这个函数指针被存储在 `DoublyLinkedList` 结构体内部（即 `list->user_free_func`），

*/
DoublyLinkedList* List_Create(size_t initial_capacity, FreeFunc free_func)
{
    if(initial_capacity == 0)
    {
        perror("Invalid initial capacity for doubly linked list");
        return NULL;
    }

    DoublyLinkedList* list = (DoublyLinkedList*)malloc(sizeof(DoublyLinkedList));
    if(!list)
    {
        perror("Failed to allocate memory for doubly linked list");
        return NULL;
    }

    list->pool = MemoryPool_Create(initial_capacity); //  创建指定初始容量的内存池
    if(!list->pool) //  检查内存池是否创建成功
    {
        free(list);
        return NULL;
    }

    list->size = 0;
    list->head = NULL;
    list->tail = NULL;
    list->user_free_func = free_func; //  设置用户自定义的内存释放函数

    // 安全的初始化互斥锁
    if(mtx_init(&list->lock, mtx_plain) != thrd_success) //  尝试初始化互斥锁，如果失败则进入错误处理
    {
        perror("Failed to initialize mutex");
        MemoryPool_Destroy(list->pool);
        free(list);
        return NULL;
    }

    return list; //  返回初始化完成的链表结构体指针
}

void List_Destroy(DoublyLinkedList** list_ptr)
{
    if(!list_ptr || !*list_ptr)   return ;

    DoublyLinkedList* list = *list_ptr;

    mtx_lock(&list->lock); //  获取链表的互斥锁，确保线程安全

    DListNode* current = list->head;
    while(current != NULL)
    {
        DListNode* next_node = current->next; //  保存当前节点的下一个节点指针，防止后续操作导致链表断裂
        if(list->user_free_func && current->data) //  如果用户定义了释放函数且当前节点有数据，则调用释放函数
        {
            list->user_free_func(current->data);
        }
        
        current = next_node;
    }

    MemoryPool_Destroy(list->pool);
    mtx_unlock(&list->lock);
    mtx_destroy(&list->lock);
    free(list);
    *list_ptr = NULL;
}

// 内部辅助函数：创建一个新的节点
static DListNode* _internal_Create(DoublyLinkedList* list, const void* data)
{
    if(!list || !list->pool)    return NULL;

    DListNode* new_node = MemoryPool_AllocateNode(list->pool); //  从内存池中分配一个新的节点
    if(!new_node)
    {
        perror("Failed to allocate node from memory pool");
    }

    new_node->data = (void*)data; //  设置新节点的数据为传入的数据，并将前后指针初始化为NULL
    // 将新节点链接到其他节点的操作由调用者完成
    new_node->next = NULL;
    new_node->prev = NULL;
    
    return new_node;
}

bool List_Append(DoublyLinkedList* list, const void* data)
{
    if(!list || !data)  return false;

    mtx_lock(&list->lock);
    
    DListNode* new_node = _internal_Create(list, data);
    if(!new_node)
    {
        mtx_unlock(&list->lock);
        return false;
    }

    if(list->tail == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        new_node->prev = list->tail;
        list->tail = new_node;
    }
    list->size++;
    mtx_unlock(&list->lock);
    return true;
}

bool List_Prepend(DoublyLinkedList* list, const void* data)
{
    if (!list || !data) return false;

    mtx_lock(&list->lock);
    DListNode* new_node = _internal_Create(list, data);

    if(!new_node)
    {
        mtx_unlock(&list->lock);
        return false;
    }

    if(list->head == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        new_node->next = list->head;
        list->head->prev = new_node;
        list->head = new_node;
    }
    list->size++;
    mtx_unlock(&list->lock);

    return true;
}

void List_DeleteNode(DoublyLinkedList* list, DListNode* node)
{
    if(!list || !node)  return ;

    mtx_lock(&list->lock);

    if(node->prev)
    {
        node->prev->next = node->next;
    }
    else
    {
        list->head = node->next;
    }

    if(node->next)
    {
        node->next->prev = node->prev;
    }
    else
    {
        list->tail = node->prev;
    }

    if(list->user_free_func && node->data)
    {
        list->user_free_func(node->data);
    }

    MemoryPool_FreeNode(list->pool, node);
    list->size--;
    mtx_unlock(&list->lock);
}

DListNode* List_Find(DoublyLinkedList* list, const void* data, CompareFunc compare_func)
{
    if(!list || !data || !compare_func)  return NULL;

    mtx_lock(&list->lock);

    DListNode* current = list->head;
    while(current != NULL)
    {
        if(compare_func(current->data, data) == 0)
        {
            mtx_unlock(&list->lock);
            return current;
        }  
        current = current->next;
    }

    mtx_unlock(&list->lock);
    return NULL;
}

size_t List_GetSize(const DoublyLinkedList* list)
{
    if(!list)  return 0;

    mtx_lock((mtx_t*)&list->lock);
    size_t size = list->size;
    mtx_unlock((mtx_t*)&list->lock);

    return size;
}

void List_ForEach(const DoublyLinkedList* list, ActionFunc action_func, void* context)
{
    if(!list || !action_func)  return ;

    mtx_lock((mtx_t*)&list->lock);

    DListNode* current = list->head;
    while(current != NULL)
    {
        action_func(current->data, context);
        current = current->next;
    }

    mtx_unlock((mtx_t*)&list->lock);
}

void*  List_GetData(const DListNode* node)
{
    return node ? node->data : NULL;
}

bool List_InsertAfter(DoublyLinkedList* list, DListNode* node, const void* data)
{
    if(!list || !node || !data)  return false;

    mtx_lock(&list->lock);

    DListNode* new_node = _internal_Create(list, data);
    if(!new_node)
    {
        mtx_unlock(&list->lock);
        return false;
    }

    new_node->next = node->next;
    new_node->prev = node;
    if(node->next)
    {
        node->next->prev = new_node;
    }
    else
    {
        list->tail = new_node;
    }

    node->next = new_node;
    list->size++;
    mtx_unlock(&list->lock);
    return true;
}
