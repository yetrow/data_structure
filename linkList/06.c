#include<stdio.h>
#include<stdlib.h>
//翻转链表（迭代实现）


typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* head=NULL;

Node* Insert(Node* head,int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=NULL;
    if(head==NULL) head=temp;
    else
    {
        Node* temp1=head;
        while(temp1->next!=NULL) temp1=temp1->next;
        temp1->next=temp;
    }
    return head;
}

void print(Node* p)
{
    while(p!=NULL)
    {
        printf(" %d",p->data);
        p=p->next;
    }
}

void reverse(Node* p)
{
    if(p->next==NULL)
    {
        head=p;
        return;
    }
    reverse(p->next);
    Node* temp=p->next;
    temp->next=p;
    p->next=NULL;
 }

int main(void)
{

    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    head=Insert(head,5);
    print(head);
    printf("\nReversed list:"); // 添加提示信息
    reverse(head);
    print(head); // 打印反转后的链表
}
