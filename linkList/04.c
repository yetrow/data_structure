#include<stdio.h>
#include<stdlib.h>
//反转链表（使用迭代）

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* head;
Node* Insert(Node* head,int n)
{
    Node* temp1=(Node*)malloc(sizeof(Node*));
    temp1->data=n;
    temp1->next=head;
    head=temp1;
    return head;
}

void print(Node* head)
{
    while(head!=NULL)
    {
        printf(" %d",head->data);
        head=head->next;
    }
}

Node* reverse(Node* head)
{
    Node* current=head,*temp=NULL,*next;
    while(current!=NULL)
    {
        next=current->next;
        current->next=temp;
        temp=current;
        current=next;
    }
    head=temp;
    return head;
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
    puts("\n");
    head=reverse(head);
    print(head);
    return 0;
}
