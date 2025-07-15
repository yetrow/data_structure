#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* front=NULL;
Node* rear=NULL;

void Enqueue(int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=NULL;

    if(front==NULL&&rear==NULL)
    {
        front=rear=temp;
        return;
    }
    rear->next=temp;
    rear=temp;
}

void Dequeue()
{
    Node* temp=front;
    if(front==NULL)
    {
        printf("queue is empty\n");
        return;
    }
    if(front==rear) front=rear=NULL;
    else front=front->next;

    free(temp);
}

int Front()
{
    if(front == NULL){
        printf("The queue is empty\n");
        return -1;
    }
    return front -> data;
}

void Print()
{
    struct Node* temp = front;
    while(temp != NULL)
    {
        printf("%d ", temp -> data);
        temp = temp -> next;
    }
    printf("\n");
}
int main(void)
{
    Enqueue(1);Print();
    Enqueue(2);Print();
    Enqueue(3);Print();
    Dequeue();Print();
    Enqueue(4);Print();
    printf("Front element is: %d\n", Front());

    return 0;
}