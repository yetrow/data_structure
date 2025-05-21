#include <stdio.h>
#include <stdlib.h>


// 定义链表节点
typedef struct Node {
    int data;
    struct Node* next;
}Node;
int top=-1;

// 全局变量，表示链表的头结点
struct Node* head = NULL;

Node* reverse(Node* head)
{
    if(head==NULL) return NULL;
    Node** stack=(Node**)malloc(100*sizeof(Node*));
    Node* temp=head;
    
    while(temp!=NULL)
    {
        stack[++top]=temp;
        temp=temp->next;
    }
    head=stack[top--];
    temp=head;

    while(top>=0)
    {
        temp->next=stack[top--];
        temp=temp->next;
    }
    temp->next=NULL;
    
    free(stack);
    return head;
}

Node* Insert(Node* head,int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=head;
    head=temp;

    return temp;
}

void print(Node* head)
{
    Node* temp=head;
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->next;
    }
    puts("\n");
}


int main() {

    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    head=Insert(head,5);
    print(head);

    head = reverse(head);
    print(head);

    return 0;
}