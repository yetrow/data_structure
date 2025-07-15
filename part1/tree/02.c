#include<stdio.h>
#include<stdlib.h>

typedef struct Node{
    char data;
    struct Node* left;
    struct Node* right;
}Node;

typedef struct Queue{
    Node* nodes[100];
    int front,rear;
}Queue;

void initQueue(Queue* q)
{
    q->front=-1;
    q->rear=-1;
}

int isQueueEmpty(Queue* q)
{
    return q->front==-1;
}

void enqueue(Queue*q,Node*node)
{
    if(q->rear==99)
    {
        printf("queue is full\n");
        return ;
    }
    if(q->front==-1)    q->front=0;
    
    q->nodes[++q->rear]=node;
}

Node* dequeue(Queue* q)
{
    if(isQueueEmpty(q))
    {
        printf("queue is empty\n");
        return NULL;
    }

    Node* node=q->nodes[q->front];

    if(q->front==q->rear)   q->front=q->rear=-1;
    else    q->front++;
    return node;
}

Node* Insert(Node* root,int data)
{
    if(root==NULL)
    {
        Node* temp=(Node*)malloc(sizeof(Node));
        temp->data=data;
        temp->left=temp->right=NULL;
        root=temp;
    }
    else if(data<root->left)   root->left=Insert(root->left,data);
    else root->right=Insert(root->right,data);
    return root;
}

void LevelOrder(Node* root)
{
    if(root==NULL)  return;
    Queue q;
    initQueue(&q);
    enqueue(&q,root);

    while(!isQueueEmpty(&q))
    {
        Node* current=dequeue(&q);
        printf("%c ",current->data);

        if(current->left!=NULL) enqueue(&q,current->left);
        if(current->right!=NULL) enqueue(&q,current->right);
    }
}

int main(void)
{
    Node* root=NULL;
    root=Insert(root,'M');
    root=Insert(root,'B');
    root=Insert(root,'Q');
    root=Insert(root,'Z');
    root=Insert(root,'A');
    root=Insert(root,'C');

    LevelOrder(root);
    return 0;
}