#include <stdio.h>
#include <stdlib.h>


// 定义链表节点
struct Node {
    int data;
    struct Node* next;
};

// 全局变量，表示链表的头结点
struct Node* head = NULL;

// 反转链表函数
void Reverse() {
    if (head == NULL) return;  // 如果链表为空，直接返回

    // 创建一个节点指针的栈
    struct Node** stack = (struct Node**)malloc(100 * sizeof(struct Node*));
    int top = -1;  // 栈顶指针

    struct Node* temp = head;

    // 将所有节点推入栈中
    while (temp != NULL) {
        stack[++top] = temp;
        temp = temp->next;
    }

    // 取出栈顶元素作为新的头结点
    temp = stack[top--];
    head = temp;

    // 将栈中的节点连接起来
    while (top >= 0) {
        temp->next = stack[top--];  // 设置当前节点的 next 为栈顶节点
        temp = temp->next;          // 移动 temp 指针
    }

    // 设置链表尾部的 next 为 NULL
    temp->next = NULL;

    free(stack);  // 释放栈内存
}

// 辅助函数：用于打印链表（调试用）
void PrintList(struct Node* head) {
    struct Node* temp = head;
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

// 辅助函数：创建链表节点（调试用）
struct Node* CreateNode(int value) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    return newNode;
}

int main() {
    // 创建一个链表：1 -> 2 -> 3 -> 4 -> 5
    head = CreateNode(1);
    head->next = CreateNode(2);
    head->next->next = CreateNode(3);
    head->next->next->next = CreateNode(4);
    head->next->next->next->next = CreateNode(5);

    printf("Original list: ");
    PrintList(head);

    // 调用反转函数
    Reverse();

    printf("Reversed list: ");
    PrintList(head);

    // 释放链表内存
    struct Node* temp;
    while (head != NULL) {
        temp = head;
        head = head->next;
        free(temp);
    }

    return 0;
}