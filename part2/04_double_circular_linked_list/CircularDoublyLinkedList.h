#pragma once 

#include <stdbool.h>
#include <stddef.h>

typedef struct CircularDoublyLinkedList CircularDoublyLinkedList;
typedef struct CDListNode CDListNode;

typedef int (*CompareFunc)(const void* a, const void* b);
typedef void (*FreeFunc)(void* data);
typedef void (*ActionFunc)(void* data, void* context);

CircularDoublyLinkedList* List_Create(size_t initial_capacity, FreeFunc free_func);

void List_Destory(CircularDoublyLinkedList** list_ptr);     // 指向要销毁的链表的指针的指针

bool List_Append(CircularDoublyLinkedList* list, void* data);

bool List_Prepend(CircularDoublyLinkedList* list, void* data);

void List_DeleteNode(CircularDoublyLinkedList** list_ptr, CDListNode* node);

CDListNode* List_Find(CircularDoublyLinkedList* list, const void* data_to_find, CompareFunc compare_func);

// 顺时针旋转链表，使得下一个节点成为新的头结点
void List_RotateForward(CircularDoublyLinkedList* list);

// 逆时针旋转链表，使得上一个节点成为新的头结点
void List_RotateBackward(CircularDoublyLinkedList* list);

size_t List_GetSize(const CircularDoublyLinkedList* list);

void List_ForEach(CircularDoublyLinkedList* list, ActionFunc action_func, void* context);

void* CDListNode_GetData(const CDListNode* node);