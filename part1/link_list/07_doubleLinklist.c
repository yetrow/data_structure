#include<stdio.h>
#include<stdlib.h>
//双向链表介绍

typedef struct Node{
    int data;
    struct Node* next;
    struct Node* prev;
}Node; 

Node* head;

Node* GetNewNode(int x);
/*当一个函数（例如 InsertAtHead）调用另一个函数（例如 GetNewNode）时，
如果被调用的函数定义在调用它的函数之后，编译器在处理调用时需要知道被调用函数的返回类型和参数类型，
以便正确生成代码。函数原型就是用来提供这些信息的。
在我之前的修改中，我在 InsertAtHead 函数之前添加了 GetNewNode 的函数原型 Node* GetNewNode(int x);
这是为了解决 InsertAtHead 中调用 GetNewNode 时，GetNewNode 还没有被定义的问题。*/
void InsertAtHead(int x)
{
    //头插法
    // Node* temp=GetNewNode(x);
    // if(head==NULL)
    // {
    //     head=temp;
    //     return;
    // }
    // head->prev=temp;
    // temp->next=head;
    // head=temp;

    //尾插法
    Node* temp = GetNewNode(x);
    if (head == NULL)
    {
        head = temp;
        return;
    }
    Node* current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = temp;
    temp->prev = current;
}

Node* GetNewNode(int x)
{
    Node* newNode=(Node*)malloc(sizeof(Node));
    newNode->data=x;
    newNode->next=NULL;
    newNode->prev=NULL;
    return newNode;
}

void print()
{
    Node* temp=head;
    printf("Forward: ");
    while(temp!=NULL)
    {
        printf("%d ",temp->data); 
        temp=temp->next;
    }
    puts("\n");
}

void reversePrint()
{
    Node*temp=head;
    if(temp==NULL)return;
    while(temp->next!=NULL)
    {
        temp=temp->next;
    }
    printf("Reverse: ");
    while(temp!=NULL)
    {
        printf("%d ",temp->data);
        temp=temp->prev;
    }
    puts("\n");
}

int main(void)
{
    InsertAtHead(2);print();reversePrint();
    InsertAtHead(4);print();reversePrint();
    InsertAtHead(6);print();reversePrint();
    InsertAtHead(8);print();reversePrint();
    InsertAtHead(10);print();reversePrint();



    return 0;
}