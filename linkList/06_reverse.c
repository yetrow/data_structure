#include<stdio.h>
#include<stdlib.h>
//翻转链表（迭代实现）


typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* head=NULL;

Node* Insert(Node* head,int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    temp->next=NULL;
    if(head==NULL) head=temp;
    else
    {
        Node* temp1=head;
        while(temp1->next!=NULL) temp1=temp1->next;
        temp1->next=temp;
    }
    return head;
}

void print(Node* p)
{
    while(p!=NULL)
    {
        printf(" %d",p->data);
        p=p->next;
    }
}

void reverse(Node* p)
{
    if(p->next==NULL)
    {
        head=p;
        return;
    }
/*  调用到了 reverse(5) 时
    p 是指向节点 5 的指针。
    p->next 是 NULL。
    满足基本情况： if(p->next == NULL).
    执行 head = p;：将全局 head 指针更新为指向节点 5。这是反转后链表的新的头部。
    执行 return;：函数返回。*/
    reverse(p->next);

/*  reverse(4) 返回后执行
    reverse(5) 调用已经返回。现在回到 reverse(4) 的执行点。
    在 reverse(4) 中，p 仍然指向节点 4。
    代码继续执行 Node* q = p->next;。p->next 原来指向 5，所以 q 指向节点 5。
    执行 q->next = p;：这行代码是核心。它将节点 5 的 next 指针从 NULL 改为指向节点 4。链表片段变成了 4 <- 5。
    执行 p->next = NULL;：这行代码也很重要。它将节点 4 的 next 指针从指向 5 改为指向 NULL。这断开了 4 -> 5 的原始链接，并确保节点 4 成为当前处理的子链表的尾部。*/
    Node* temp=p->next;
    temp->next=p;
    p->next=NULL;
 }

int main(void)
{

    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    head=Insert(head,5);
    print(head);
    printf("\nReversed list:"); // 添加提示信息
    reverse(head); 
    print(head); // 打印反转后的链表
}
