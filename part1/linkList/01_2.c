#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* insert(Node*head,int x)
{
    struct Node*temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=NULL;
    if(head!=NULL) temp->next=head;
    head=temp;
    return head;
}

void print(Node*head)
{
    printf("list is\n");
    while(head!=NULL)
    {
        printf(" %d",head->data);
        head=head->next;
    }
    puts("\n");
}

int main(void)
{
    Node*head=NULL;
    int n,x,i;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("%d",&x);
        head=insert(head,x);
        print(head);
    }
}