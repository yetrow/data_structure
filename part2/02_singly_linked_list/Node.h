#pragma once

typedef struct Student
{
    int id;
    char name[50];
    int age;
} Student;

typedef Student Data;

typedef struct Node
{
    Data data; // 一定是一个嵌套的结构体
    struct Node *next;
} Node;

Node* createNode(Data data);

// appendNode,当链表为空的时候，head是NULL时，appendNode需要将head指向新创建的节点
// 这涉及head指针本身
void appendNode(Node** headRef, Data data);

void prepenNode(Node** headRef, Data data);

void printNode(Node* head, void (*print_func)(const void *data));

// 这个啊函数执行完毕后，会返回一个指向Node结构体的指针。Node*
// 第三个参数，意味着，第三个参数传递过来的是一个函数的地址，这个函数必须满足
//  1.返回int类型    2.这个函数必须是const void* 类型的参数
// node->data
// 这个回调函数无法知道可变参数
// findNode函数
// 1.他正在遍历的是当前节点的数据
// 2.你一开始传递给他的目标函数
Node *findNode(Node *head /*指向链表头结点，不涉及修改,所以一级指针*/,
               const void *target_data, 
               int (*compare_func)(const void *a, const void *b,void* context),
               void* context);

void deleteNode(
    Node** headRef,
    const void* target_data,
    int(*compare_func)(const void* a,const void* b,void* context),
    void* context
);

/**
 * @brief 更新链表中匹配特定数据的节点。
 *
 * 该函数遍历链表，使用提供的比较函数查找与 target_data 匹配的节点。
 * 如果找到匹配的节点，则将其数据更新为 newData。
 *
 * @param headRef 指向链表头指针的指针。允许函数修改头指针（例如，如果头节点被更新）。
 * @param target_data 指向要查找的目标数据的指针。
 * @param newData 要更新到匹配节点的新数据。
 * @param compare_func 用于比较链表节点数据和 target_data 的回调函数。
 *                     如果两个数据相等，则返回 0；否则返回非零值。
 * @param context 传递给 compare_func 的可选上下文指针。
 */
void updateNode(
    Node* head,
    const void* target_data,
    Data newData,
    int(*compare_func)(const void* a,const void* b,void* context),
    void* context
);

void freeList(Node** headRef,void (*free_data_func)(void* data));
