#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* link;
}Node;

Node* top=NULL;

void Push(int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->link=top;
    top=temp;
}
void Pop()
{
    Node* temp=top;
    if(temp==NULL)
    {
        printf("ERROR\n");
        return;
    }
    top=temp->link;
    free(temp);
}

int Top()
{
    if(top==NULL) return -1;
    return top->data;
}

void Print()
{
    Node*temp=top;
    while(temp!=NULL)
    {
        printf(" %d",temp->data);
        temp=temp->link;
    }
    puts("\n");
}

int main(void)
{
    Push(1);
    Push(2);
    Push(3);
    Print();
    Pop();
    Print();
    
    return 0;
}