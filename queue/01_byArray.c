#include<stdio.h>
#include<stdbool.h>

#define MAX_SIZE 101

typedef struct Queue{
    int a[MAX_SIZE];
    int front,rear;
}Queue;

void Initialize(Queue* q)
{
    q->front=-1;
    q->rear=-1;
}

bool Isempty(Queue* q)
{
    return(q->front ==-1&&q->rear==-1);
}

bool Isfull(Queue* q)
{
    return((q->rear+1)%MAX_SIZE==q->front);
}

void Enqueue(Queue* q,int x)
{
    if(Isfull(q))
    {
        printf("error:queue is full\n");
        return;
    }
    if(Isempty(q)) q->front=q->rear=0;
    else q->rear=(q->rear+1)%MAX_SIZE;

    q->a[q->rear]=x;
}

void Dequeue(Queue* q)
{
    if(Isempty(q))
    {
        printf("error\n");
        return;
    }
    else if(q->front==q->rear)
    {
        q->front=q->rear=-1;
    }
    else{
        q->front=(q->front+1)%MAX_SIZE;
    }
}
int front(Queue* q){
    if(Isempty(q)){
        printf("Error: Queue is Empty\n");
        return -1;
    }
    return(q -> a[q -> front]);//返回当前队列的第一个元素
}

void Print(Queue* q)
{
    if(Isempty(q)){
        printf("Queue is Empty\n");
        return;
    }
    int count = (q -> rear + MAX_SIZE - q -> front) % MAX_SIZE + 1;//+MAX计算相对距离避免出现负数，%MAX环形结构映射位置，+1补偿索引从0开始
    printf("Queue: ");
    for(int i = 0; i < count; i++){
        int index = (q -> front + i) % MAX_SIZE;
        printf("%d ", q -> a[index]);
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