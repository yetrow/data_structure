#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* head;

Node* Insert(Node* head,int x)
{
    Node* temp=(Node* )malloc(sizeof(Node));
    temp->data=x;
    temp->next=NULL;
    if(head==NULL)  return;
    else{
        Node* temp1=head;
        while(temp->next!=NULL) temp1=temp1->next;
        temp1->next=temp;
    }
    return head;
}

void Print(Node* head)
{
    if(head==NULL)  return ;
    Print(head->next);
    printf(" %d",head->data);
}

Node* Reverse(Node* head)
{
    Node* pre=NULL;
    Node* current=head;
    Node* next=NULL;
    while(current!=NULL)
    {
        next=current->next;
        current->next=pre;
        pre=current;
        current=next;
    }
    return head=pre;
}

int main(void)
{
    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    Print(head);
    head=Reverse(head);
    Print(head);

    return 0;
}