#include <stdio.h>
#include <stdlib.h>
// 删除链表任意位置元素

typedef struct Node
{
    int data;
    struct Node *next
} Node;

Node *head;
void Insert(int x, int n);
void print();

void delete(int n)
{
    Node *temp1 = head;
    if (n == 1)
    {
        head = temp1->next;
        free(temp1);
        return;
    }
    for (int i = 0; i < n - 2; i++)
    {
        temp1 = temp1->next;
    }
    Node *temp2 = temp1->next;
    temp1->next = temp2->next;
    free(temp2);
}

int main(void)
{
    head = NULL;
    Insert(1, 1);
    Insert(2, 1);
    Insert(3, 2);
    Insert(4, 2);
    Insert(5, 3);
    print();
    delete(4);
    puts("\n");
    print();
    return 0;
}

void Insert(int x, int n)
{
    Node *temp1 = (Node *)malloc(sizeof(Node *));
    temp1->data = x;
    temp1->next = head;
    if (n == 1)
    {
        temp1->next = head;
        head = temp1;
        return;
    }
    Node *temp2 = head;
    for (int i = 0; i < n - 2; i++)
    {
        temp2 = temp2->next;
    }
    temp1->next = temp2->next;
    temp2->next = temp1;
}

void print()
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf(" %d", temp->data);
        temp = temp->next;
    }
}
