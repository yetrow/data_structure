//打印一个列表，递归方式
#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* head;

Node* Insert(Node*head,int x)
{
    //头插法
    // struct Node*temp=(Node*)malloc(sizeof(Node));
    // temp->data=x;
    // temp->next=head;
    // head=temp;
    // return head;

    //尾插法
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
    if(p==NULL) return;
    print(p->next);
    printf(" %d",p->data);
}

int main(void)
{
    head=NULL;
    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    head=Insert(head,5);
    print(head);


    return 0;
}