#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* head=NULL;

int top=-1;

Node* Insert(Node* head,int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=head;
    head=temp;
    return head;
}

void print(Node* head)
{
    Node* temp=head;
    while(temp!=NULL)
    {
        printf(" %d ",temp->data);
        temp=temp->next;
    }
    puts("\n");
}

Node* reverse(Node* head)
{
    if(head == NULL) return NULL;
    
    Node** stack=(Node**)malloc(100*sizeof(Node*));
    Node* temp=head;
    int top=-1;
    
    while(temp!=NULL)
    {
        stack[++top]=temp;
        temp=temp->next;
    }

    head=stack[top--];
    temp=head;
    
    while(top >= 0)
    {
        temp->next=stack[top--];
        temp=temp->next;
    }
    temp->next=NULL;

    free(stack);
    return head;
}

int main(void)
{
    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    head=Insert(head,5);
    print(head);
    head=reverse(head);
    print(head);

    return 0;
}

