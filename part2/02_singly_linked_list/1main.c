#define _CRT_SECURE_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data)
{
    Node *newNode = (Node *)malloc(sizeof(Node));

    if (newNode == NULL)
    {
        printf("错误：分配失败\n");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;
}

// headRef是指向head指针的指针
// 这样我们才能在链表为空的时候修改head
void list_append(Node **headRef, int data) // 末尾追加函数
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

void prepenNode(Node **headRef, int data) // 头结点追加
{
    Node *newNode = createNode(data);
    newNode->next = *headRef;
    *headRef = newNode;
}

void printList(Node *head)
{
    Node *current = head;
    printf("当前列表:\n");
    while (current != NULL)
    {
        printf(" %d --> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

Node *findNode(Node *head, int data)
{
    Node *current = head;
    while (current != NULL)
    {
        if (current->data == data)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void updateNode(Node *head, int oldData, int newData)
{
    Node *temp = findNode(head, oldData);
    if (temp != NULL)
    {
        temp->data = newData;
        printf("数据%d已经成功更新至%d.\n", oldData, newData);
    }
    else
    {
        printf("未找到\n");
    }
}

void deleteNode(Node **headRef, int data)
{
    Node *temp = *headRef;
    Node *prev = NULL;
    // 删除头结点
    if (temp != NULL && temp->data == data)
    {
        *headRef = temp->next;
        free(temp);
        return;
    }
    // head-->[10|next]-->[20|next]-->[30|next]-->[40|next]-->NULL;

    // 尾部或中间节点
    while (temp != NULL && temp->data != data)
    {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL)
    {
        return;
    }
    prev->next = temp->next;
    free(temp);
}

void list_free(Node **headRef)
{
    if (headRef == NULL)
        return;
    Node *current = *headRef;

    Node *nextNode;

    while (current != NULL)
    {
        nextNode = current->next;
        free(current);
        current = nextNode;
    }
    *headRef = NULL;
}

int main(void)
{
    Node *head = NULL;
    list_append(&head, 10);
    list_append(&head, 20);
    list_append(&head, 30);

    printList(head);

    list_append(&head,40);
    printList(head);

    prepenNode(&head,50);
    printList(head);

    deleteNode(&head,50);
    printList(head);

    list_free(&head);
    printList(head);


    return 0;
}