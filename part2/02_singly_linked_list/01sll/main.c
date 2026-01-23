#define _CRT_SECURE_WARNINGS_
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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

// 末尾追加函数
// headRef是指向head指针的指针
// 这样我们才能在链表为空的时候修改head
// 函数参数永远是值传递
// 如果你想在函数中修改某个变量，就必须把“那个变量的地址”传进去

// 某个指针 = 新地址;
// ✔   有 ，参数必须是             二级指针
// ❌ 没有，只是 指针->成员 = ... → 一级指针
void list_append(Node **headRef, int data) 
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

// 头结点追加函数
void prepenNode(Node **headRef, int data) 
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

// 按位查找函数 (1-based index)
Node *findNodeByIndex(Node *head, int index)
{
    Node *current = head;
    int count = 1; // 1-based index
    while (current != NULL)
    {
        if (count == index)
        {
            return current;
        }
        current = current->next;
        count++;
    }
    return NULL; // 未找到或索引超出范围
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

// 时间复杂度是 O(n)
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

// 按位删除
bool deleteAt(Node **headRef, int pos)
{
    if (*headRef == NULL || pos <= 0)
        return false;

    Node *temp = *headRef;

    // 删除头结点
    if (pos == 1)
    {
        *headRef = temp->next;
        free(temp);
        return true;
    }

    Node *prev = NULL;
    int index = 1;

    while (temp != NULL && index < pos)
    {
        prev = temp;
        temp = temp->next;
        index++;
    }

    if (temp == NULL)
        return false;

    prev->next = temp->next;
    free(temp);
    return true;
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