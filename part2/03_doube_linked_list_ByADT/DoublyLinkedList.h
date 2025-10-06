#pragma once
#include <stdbool.h>
#include <stddef.h>

// --- Opaque Pointer Type ---
// 用户只能看到这些类型的指针，不能访问其内部结构 —— OPP封装

typedef struct DoublyLinkedList DoublyLinkedList;
typedef struct DListNode DListNode;

// --- Callback Function Pointer Typedefs ---
// 定义用户需要提供的回调函数类型，增强代码的可读性

typedef int (*CompareFunc)(const void *data1, const void *data2);
typedef void (*PrintFunc)(const void *data);
typedef void (*FreeFunc)(void *data);
typedef void (*ActionFunc)(void *data, void *arg);

/// API FUNCTION DECLARATIONS
/*
 * 创建一个新的双向链表
 * initial_capacity 内存池初始容量（可用于分配节点或内部结构）
 * free_func 用户自定义的释放数据的回调函数，链表销毁或节点删除时调用
 * DoublyLinkedList* 新创建的链表指针，失败时返回NULL
*/

// MemoryPool 相关函数指针类型
// 内存池结构。它预先分配一块内存，用于存储链表节点，减少频繁的内纯分配和释放操作。
// 并且将其划分为多个固定大小的块，以便快速分配和释放。内部通过一个单项链表来管理这些内存块。

DoublyLinkedList *List_Create(size_t initial_capacity, FreeFunc free_func);

bool List_Destory(DoublyLinkedList *list);

bool List_Append(DoublyLinkedList *list, const void *data);

bool List_Prepend(DoublyLinkedList *list, const void *data);

bool List_InsertAfter(DoublyLinkedList *list, DListNode *node, const void *data);

bool List_DeleteNode(DoublyLinkedList *list, DListNode *node);

bool List_Find(DoublyLinkedList *list, const void *data_to_find, CompareFunc compare_func);

size_t List_GetList(const DoublyLinkedList *list);

void List_ForEach(const DoublyLinkedList *list, ActionFunc action_func, void *context);
