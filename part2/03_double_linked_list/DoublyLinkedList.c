#define _CRT_SECURE_NO_WARNINGS

#include "DoublyLinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <errno.h>

/*
 * 创建一个节点并才初始化
 * 这是一个内部函数，不应该被外部调用
 */
static Node *createNode(Song songData)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode)
    {
        perror("Failed to allocate memory for new node.");
        return NULL;
    }
    // 初始化节点数据，为节点分配内存
    // 因为songData中的字符串成员是char*类型
    // 直接赋值会导致多个节点指向同一内存地址
    // 所以需要使用strcpy函数将字符串复制到新分配的内存中
    newNode->data.title = (char *)malloc(strlen(songData.title) + 1);
    newNode->data.artist = (char *)malloc(strlen(songData.artist) + 1);
    // +1的原因：字符串的结束标志'\0'也需要占用一个字节
    // "hello"和整数 99 在内存中
    // [h] [e] [l] [l] [o] [0]  [\0] [99的二进制数]...
    // 空字符'\0'是字符串的结束标志
    // strlen 计算的是字符串的可见字符数，所以分配的内存大小需要+1

    if (!newNode->data.title || !newNode->data.artist)
    {
        perror("failed to allocate memory for song data.");
        free(newNode->data.title);
        free(newNode->data.artist);
        free(newNode);
        return NULL;
    }

    // strcpy 会把字符串从源复制到目标，包括结束标志'\0'
    strcpy(newNode->data.title, songData.title);
    strcpy(newNode->data.artist, songData.artist);
    newNode->data.duration = songData.duration;

    // 确保新节点的next和prev指针初始化为NULL
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

DoublyLinkedList *createList()
{
    DoublyLinkedList *list = (DoublyLinkedList *)malloc(sizeof(DoublyLinkedList));
    if (!list)
    {
        perror("Failed to allocate memory for the list.");
        return NULL;
    }

    // 初始化链表
    list->head = NULL;
    list->tail = NULL;
    list->size = 0;
    return list;
}

void freeList(DoublyLinkedList *list)
{
    if (!list)
    {
        perror("List is NULL,nothing to free.");
        return;
    }

    // 遍历链表并释放每个节点
    //  current是一个临时指针，指向链表的头结点
    Node *current = list->head;
    while (current != NULL)
    {
        Node *nextNode = current->next; // 临时的nextNode
        free(current->data.title);
        free(current->data.artist);
        free(current);
        current = nextNode;
    }
    free(list); // 释放链表器本身的内存
}

// 末尾追加
bool append(DoublyLinkedList *list, Song songData)
{
    if (!list)
    {
        perror("List is NULL, cannot append.");
        return false;
    }

    Node *newNode = createNode(songData);
    if (!newNode)
    {
        return false;
    }

    if (list->head == NULL)
    {
        // 链表为空时，设置头结点和尾结点
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        // 链表非空时，将新节点添加到尾部
        list->tail->next = newNode;
        newNode->prev = list->tail;
        list->tail = newNode;
    }
    list->size++;
    return true;
}

// 头部追加
bool prepend(DoublyLinkedList *list, Song songData)
{
    if (!list)
    {
        perror("List is NULL, can not prepend.");
        return false;
    }

    Node *newNode = createNode(songData);
    if (!newNode)
    {
        return false;
    }
    if (list->head == NULL)
    {
        // 链表为空时，设置头结点和尾结点
        list->head = newNode;
        list->tail = newNode;
    }
    else
    {
        // 链表非空时，将新节点添加到尾部
        newNode->next = list->head; // 新节点的next指向当前头结点
        // newNode->prev = NULL;
        list->head->prev = newNode; // 当前头节点的prev指向新节点
        list->head = newNode;       // 更新头结点为新节点
    }
    list->size++;
    return true;
}

bool insertAfter(DoublyLinkedList *list, Node *targetNode, Song songData)
{
    // 1. 错误处理和边界情况：检查链表和目标节点是否为空
    if (!list || !targetNode)
    {
        perror("Error: List or target node is NULL. Cannot insert after.");
        return false;
    }

    // 2. 创建新节点
    Node *newNode = createNode(songData);
    if (!newNode)
    {
        perror("Error: Failed to create new node. Memory allocation failed.");
        return false;
    }

    // 3. 链接新节点
    // 将新节点的next指向目标节点的next
    newNode->next = targetNode->next;
    // 将新节点的prev指向目标节点
    newNode->prev = targetNode;

    // 4. 更新相邻节点的链接
    // 如果目标节点不是尾节点，更新目标节点下一个节点的prev指针
    if (targetNode->next != NULL)
    {
        targetNode->next->prev = newNode;
    }
    else
    {
        // 如果目标节点是尾节点，新节点将成为新的尾节点
        list->tail = newNode;
    }

    // 更新目标节点的next指针，使其指向新节点
    targetNode->next = newNode;

    // 5. 更新链表大小
    list->size++;

    // 6. 返回成功
    return true;
}

// list 是指向链表的指针，nodeToDelete是指向要删除节点的指针
bool deleteNode(DoublyLinkedList *list, Node *nodeToDelete)
{
    if (!list || !nodeToDelete)
    {
        perror("List or node to delete is NULL.");
        return false;
    }

    if (nodeToDelete->prev != NULL)
    {
        // 要删除节点的前一个节点的next = 要删除节点的next
        nodeToDelete->prev->next = nodeToDelete->next;
    }
    else
    {
        list->head = nodeToDelete->next;
    }

    if (nodeToDelete->next != NULL)
    {
        // 更新后节点的prev指针为要删除节点的前一个节点
        nodeToDelete->next->prev = nodeToDelete->prev;
    }
    else
    {
        list->tail = nodeToDelete->prev;
    }

    free(nodeToDelete->data.title);
    free(nodeToDelete->data.artist);
    free(nodeToDelete);
    list->size--;
    return true;
}

Node *findByTitle(const DoublyLinkedList *list, const char *title)
{
    if (!list || !title)
    {
        perror("List or title is NULL.");
        return NULL;
    }

    Node *current = list->head;

    while (current != NULL)
    {
        if (strcmp(current->data.title, title) == 0)
        {
            return current; // 找到匹配节点
        }
        current = current->next;
    }
    return NULL;
}

void printListForward(const DoublyLinkedList *list)
{
    if (!list || !list->head)
    {
        printf("list is empty.\n");
        return; // 链表为空
    }

    printf("---Playlist (Size: %d, Forword) ---\n", list->size);
    Node *current = list->head;
    int index = 1;

    while (current != NULL)
    {
        printf("%d. Title: %s, Artist: %s, Duration: %d seconds\n",
               index++, current->data.title, current->data.artist, current->data.duration);
        current = current->next;
    }
    printf("---End of Playlist---\n");
}

void printListBackward(const DoublyLinkedList *list)
{
    if (!list || !list->tail)
    {
        printf("list is empty.\n");
        return; // 链表为空
    }

    printf("---Playlist (Size: %d, Forword) ---\n", list->size);
    Node *current = list->tail;
    int index = list->size;

    while (current != NULL)
    {
        printf("%d. Title: %s, Artist: %s, Duration: %d seconds\n",
               index--, current->data.title, current->data.artist, current->data.duration);
        current = current->prev;
    }
    printf("---End of Playlist---\n");
}
