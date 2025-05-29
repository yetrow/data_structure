#include<stdio.h>
#include<stdbool.h>
#define SIZE 101

typedef struct Queue{
    int a[SIZE];
    int front,rear;
}Queue;

void Initialize(Queue*q)
{
    q->front=q->rear=-1;
}

bool Isempty(Queue*q)
{
    return (q->front==-1&&q->rear==-1);
}
bool Isfull(Queue* q)
{
    return ((q->rear+1)%SIZE==q->front);
}

void Enqueue(Queue* q,int x)
{
    if(Isfull(q))  return;
    if(Isempty(q))  q->front=q->rear=0;
    else q->rear=(q->rear+1)%SIZE;
    
    q->a[q->rear]=x;
}

void Dequeue(Queue* q)
{
    if(Isempty(q))  return;
    else if(q->front==q->rear)  q->front=q->rear=-1;
    else    q->front=(q->front+1)%SIZE;

}

int front(Queue* q)
{
    if(Isempty(q))  return -1 ;
    else    return q->a[q->front];
}

void Print(Queue* q)
{
    if(Isempty(q))  return;
    int count=(q->rear+SIZE-q->front)%SIZE+1;
    for(int i=0;i<count;i++)
    {
        int index=(q->front+i)%SIZE;
        printf("%d ",q->a[index]);
    }
    printf("\n");
}

int main(){
    Queue q;
    Initialize(&q);

    Enqueue(&q, 2); Print(&q);
    Enqueue(&q, 4); Print(&q);
    Enqueue(&q, 6); Print(&q);
    Dequeue(&q); Print(&q);
    Enqueue(&q, 8); Print(&q);

    return 0;
}