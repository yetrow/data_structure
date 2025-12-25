//反转列表递归实现
#include<stdio.h>
#include<stdlib.h>


typedef struct Node{
    int data;          
    struct Node* next; 
}Node;

Node* head;

Node* Insert(Node* head,int n)
{
    
    Node* temp1=(Node*)malloc(sizeof(Node)); 
    temp1->data=n;
    temp1->next=head; 
    head=temp1;      
    return head;     
}

void print(Node* head)
{
    while(head!=NULL)
    {
        printf(" %d",head->data); 
        head=head->next;         
    }
}


Node* reverse(Node* head)
{
    Node* current=head; 
    Node* prev=NULL;    
    Node* next;        

    while(current!=NULL)
    {
        next=current->next;   
        current->next=prev;   // 将当前节点的next指向前一个节点（实现反转）
        prev=current;         // 前一个节点移动到当前节点
        current=next;         // 当前节点移动到下一个节点
    }
    head=prev; // 循环结束后，prev指向原链表的最后一个节点，即反转后链表的头节点
    return head; // 返回反转后链表的头指针
}


int main(void)
{
    head=NULL; // 初始化空链表

    head=Insert(head,1);
    head=Insert(head,2);
    head=Insert(head,3);
    head=Insert(head,4);
    head=Insert(head,5);

    // 打印原始链表
    printf("Original list:");
    print(head);
    puts("\n");

    // 反转链表
    head=reverse(head);

    // 打印反转后的链表
    printf("Reversed list:");
    print(head);
    puts("\n");
    return 0;
}
