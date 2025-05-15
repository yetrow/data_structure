
#include<stdio.h>
#include<stdlib.h>

// 定义链表节点结构体
typedef struct Node{
    int data;          // 节点存储的数据
    struct Node* next; // 指向下一个节点的指针
}Node;

// 定义链表头指针
Node* head;

// 在链表头部插入新节点
// 参数: head - 当前链表的头指针, n - 要插入的数据
// 返回值: 新的链表头指针
Node* Insert(Node* head,int n)
{
    // 创建新的节点
    Node* temp1=(Node*)malloc(sizeof(Node)); // 注意: 这里应该是 sizeof(Node) 而不是 sizeof(Node*)
    temp1->data=n;
    temp1->next=head; // 新节点的next指向原来的头节点
    head=temp1;       // 更新头指针为新节点
    return head;      // 返回新的头指针
}

// 打印链表中的所有节点数据
// 参数: head - 要打印的链表的头指针
void print(Node* head)
{
    // 遍历链表直到末尾
    while(head!=NULL)
    {
        printf(" %d",head->data); // 打印当前节点数据
        head=head->next;         // 移动到下一个节点
    }
}

// 反转链表（迭代方法）
// 参数: head - 要反转的链表的头指针
// 返回值: 反转后链表的头指针
Node* reverse(Node* head)
{
    Node* current=head; // 当前节点，初始为头节点
    Node* prev=NULL;    // 前一个节点，初始为NULL
    Node* next;         // 临时存储下一个节点

    // 遍历链表
    while(current!=NULL)
    {
        next=current->next;   // 存储下一个节点
        current->next=prev;   // 将当前节点的next指向前一个节点（实现反转）
        prev=current;         // 前一个节点移动到当前节点
        current=next;         // 当前节点移动到下一个节点
    }
    head=prev; // 循环结束后，prev指向原链表的最后一个节点，即反转后链表的头节点
    return head; // 返回反转后链表的头指针
}

// 主函数
int main(void)
{
    head=NULL; // 初始化空链表

    // 在链表头部插入元素
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
    puts("\n"); // 添加一个换行符以保持输出整洁

    return 0;
}
