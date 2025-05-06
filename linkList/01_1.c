#include<stdio.h>
#include<stdlib.h>
//创建链表


typedef struct Node {
    int data;
    struct Node* next;
}Node;
/*当编译器读到结构体内部的 struct Node* next; 这一行时：
它正处于 { ... } 的内部，整个 typedef 语句还没有结束。
因此，由 typedef 创建的别名 Node 此时还不存在，编译器还不认识它。如果你只写 Node* next;
编译器会说：“我不认识这个叫 Node 的类型是什么东西。” 
但是，因为你在 struct 关键字后面写了标签名 Node 编译器已经知道了存在一个叫做 Node 的 结构体标签。
所以，当你写 struct Node* next; 时，编译器能够理解：“哦，这里的 struct Node 指的就是我们当前正在定义的这个带有 Node 标签的结构体。next 是一个指向这种结构体类型的指针。” 
这对于创建链表（一个节点指向同类型的下一个节点）是至关重要的。*/
Node* head=NULL;

void Insert(int x)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=x;
    // temp->next=NULL;
    // if(head!=NULL)
    // {
    //     temp->next=head;
    // }
    temp->next=head;
    head=temp;
}
void print()
{
    Node* temp=head;
    while(temp!=NULL)
    {
        printf(" %d",temp->data);
        temp=temp->next;
    }
    puts("\n");
}

int main(void)
{
    head=NULL;
    puts("how many numbers?\n");
    int n,i,x;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        puts("enter the numbers\n");
        scanf("%d",&x);
        Insert(x);
        print();
    }
}