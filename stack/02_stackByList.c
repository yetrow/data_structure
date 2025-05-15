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
    if(top==NULL)
    {
        printf("Stack Underflow\n");
        return;
    }
    Node* temp=top;
    top=top->link;
    free(temp);
}

int Top()
{
    if(top == NULL)
    {
        printf("Stack is empty\n");
        return -1; // 或者其他表示错误的值
    }
    return top->data;
}

void Print()
{
    Node* temp = top;
    printf("Stack: ");
    while(temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->link;
    }
    printf("\n");
}

int main()
{
    Push(10);
    Print();
    Push(20);
    Print();
    Pop();
    Print();
    Push(30);
    Print();
    Push(40);
    Print();

    printf("Top element is: %d\n", Top());
    Pop();
    Print();
    printf("Top element is: %d\n", Top());
    Pop();
    Print();
    Pop();
    Print();
    Pop(); // Should print Stack Underflow
    Print();

    return 0;
}