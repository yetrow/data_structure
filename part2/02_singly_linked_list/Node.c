#define _CRT_SECURE_NO_WARNINGS_
#include "Node.h"
#include <stdio.h>
#include <stdlib.h>

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

Node *createNode(Data data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL)
    {
        perror("创建节点失败\n");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

// appendNode,当链表为空的时候，head是NULL时，appendNode需要将head指向新创建的节点
// 这涉及head指针本身
void appendNode(Node **headRef, Data data)
{
    Node *newNode = createNode(data);
    if (newNode == NULL)
        return;
    if (*headRef == NULL)
    {
        *headRef = newNode;
        return;
    }

    Node *last = *headRef;
    while (last->next != NULL)
    {
        last = last->next;
    }
    last->next = newNode;
}

void prepenNode(Node **headRef, Data data)
{
    Node *newNode = createNode(data);

    if (newNode == NULL)
        return;
    newNode->next = *headRef;
    *headRef = newNode;
}

void printNode(Node *head, void (*print_func)(const void *data))
{
    if (print_func == NULL)
    {
        printf("错误：未提供打印函数\n");
        return;
    }

    printf("列表内容：\n");
    Node *current = head;
    while (current != NULL)
    {
        print_func(&(current->data));
        printf(" -> ");
        current = current->next;
    }
    printf("NULL\n");
}

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
               int (*compare_func)(const void *a, const void *b, void *context),
               void *context)
{
    if (compare_func == NULL)
    {
        printf("错误：未提供比较函数\n");
        return NULL;
    }

    Node *current = head;
    while (current != NULL)
    {
        // 调用回调
        if (compare_func(&(current->data), target_data, context) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void deleteNode(
    Node **headRef,
    const void *target_data,
    int (*compare_func)(const void *a, const void *b, void *context),
    void *context)
{
    if (compare_func == NULL)
    {
        printf("错误：无效参数\n");
        return;
    }

    Node *temp = *headRef;
    Node *prev = NULL;

    // 检查头结点是否是目标
    if (compare_func(&(temp->data), target_data, context) == 0)
    {
        *headRef = temp->next;
        free(temp);
        printf("信息：头结点已经删除！\n");
        return;
    }

    while (temp != NULL && compare_func(&temp->data, target_data, context) != 0)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        printf("警告：未找到目标节点，无法删除\n");
        return;
    }

    if (prev != NULL)
    {
        prev->next = temp->next;
    }
    free(temp);
    printf("信息：节点已经删除\n");
}

void updateNode(
    Node *head,
    const void *target_data,
    Data newData,
    int (*compare_func)(const void *a, const void *b, void *context),
    void *context)
{
    Node *nodeToUpdate = findNode(head, target_data, compare_func, context);
    if (nodeToUpdate != NULL)
    {
        nodeToUpdate->data = newData;
        printf("信息：节点已经更新成功\n");
    }
    else
    {
        printf("警告：未找到目标节点，无法更新\n");
    }
}

/**
 * @brief 释放整个链表及其节点数据。
 *
 * 该函数遍历链表，依次释放每个节点及其内部可能动态分配的数据。
 * 如果提供了 free_data_func，它将用于释放每个节点中存储的数据。
 * 最后，链表头指针将被设置为 NULL，以避免悬空指针。
 *
 * @param headRef 指向链表头指针的指针。允许函数修改头指针，将其设置为 NULL。
 * @param free_data_func 一个回调函数，用于释放节点中存储的数据。
 *                         如果数据不需要额外释放（例如，它是基本类型或静态分配的结构体），
 *                         则可以传递 NULL。该函数接收一个 void* 参数，指向要释放的数据。
 */
void freeList(Node **headRef, void (*free_data_func)(void *data))
{
    // 1. 错误处理和边缘情况：检查头指针的引用是否为 NULL。
    // 如果 headRef 为 NULL，表示没有链表可以操作，直接返回。
    if (headRef == NULL || *headRef == NULL)
    {
        return;
    }

    Node *current = *headRef;
    Node *nextNode;

    // 遍历链表，逐个释放节点
    while (current != NULL)
    {
        nextNode = current->next; // 在释放当前节点之前保存下一个节点的地址

        // 3. 最佳实践和模式：如果提供了数据释放函数，则调用它来释放节点内部的数据。
        // 注意：这里传递的是 current->data 的地址，因为 free_data_func 期望一个 void* 指针。
        // 这对于释放 Data 结构体内部的动态内存是正确的。
        if (free_data_func != NULL)
        {
            free_data_func(&(current->data));
        }

        free(current); // 释放当前节点
        current = nextNode; // 移动到下一个节点
    }

    // 3. 最佳实践和模式：将头指针设置为 NULL，防止悬空指针，并明确表示链表已空。
    *headRef = NULL;
}
