#define _CRT_SECURE_WARNINGS_
#include"Node.h"
#include<stdio.h>
#include<stdlib.h>


typedef struct Student
{
    int id;
    char name[50];
} Student;

typedef Student Data;

typedef struct Node
{
    Data data; // 一定是一个嵌套的结构体
    struct Node *next;
} Node;

Node* createNode(Data data)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    if(newNode==NULL)
    {
        perror("创建节点失败\n");
        return NULL;
    }
    
    newNode->data=data;
    newNode->next=NULL;
    return newNode;
}

// appendNode,当链表为空的时候，head是NULL时，appendNode需要将head指向新创建的节点
// 这涉及head指针本身
void appendNode(Node** headRef, Data data)
{
    Node* newNode=createNode(data);
    if(newNode==NULL)   return;
    if(*headRef==NULL)
    {
        *headRef=newNode;
        return;
    }

    Node* last=*headRef;
    while(last->next!=NULL)
    {
        last=last->next;
    }
    last->next=newNode;
    return *headRef;
}

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
Node *findNode_with_context(Node *head /*指向链表头结点，不涉及修改,所以一级指针*/,
               const void *target_data, 
               int (*compare_func)(const void *a, const void *b,void* context));

void deleteNode(
    Node** headRef,
    const void* target_data,
    int(*compare_func)(const void* a,const void* b,void* context),
    void* context
);

void updateNode(
    Node** headRef,
    const void* target_data,
    int(*compare_func)(const void* a,const void* b,void* context),
    void* context
);

void updateNode(
    Node** headRef,
    const void* target_data,
    Data newData,
    int(*compare_func)(const void* a,const void* b,void* context),
    void* context
);

void freeList(Node** headRef,void (*free_data_func)(void* data));
