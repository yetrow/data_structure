#pragma once 
#include<stdbool.h>
#include<stddef.h>
// 双向链表 模拟音乐播放器

/*
DoublyLinkedList
 ├── head ──> Node <──> Node <──> Node <── tail
 │               │        │        │
 │               ▼        ▼        ▼
 │             Song     Song     Song
 │
 └── size (节点数量)
*/


// 模拟节点存储数据
typedef struct{
    // char title[100]; 之前的是const的，一旦定义了就不能修改
    // 而现在是char* title，动态内存分配，可以修改
    char* title;
    char* artist;
    int duration; // 单位是秒
}Song;

// // 前向声明 Node 结构体，以便在自身定义中引用
// struct Node;

// 双向链表
typedef struct Node{
    Song data;
    struct Node* next;
    struct Node* prev;
}Node;

// 定义一个管理器
typedef struct{
    Node* head;
    Node* tail;
    size_t size;
}DoublyLinkedList;

DoublyLinkedList* createList();

void freeList(DoublyLinkedList* list);

// 末尾追加
bool append(DoublyLinkedList* list,Song songData);

// 头部追加
bool prepend(DoublyLinkedList* list,Song songData);

bool insertAfter(DoublyLinkedList* list,Node* targetNode,Song songData);

// list 是指向链表的指针，nodeToDelete是指向要删除节点的指针
bool deleteNode(DoublyLinkedList* list,Node* nodeToDelete);

Node* findByTitle(const DoublyLinkedList* list,const char* title);

void printListForward(const DoublyLinkedList* list);

void printListBackward(const DoublyLinkedList* list);
