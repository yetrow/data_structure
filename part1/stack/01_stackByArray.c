#include<stdio.h>

#define MAX_SIZE 101

// 定义一个数组a，用于存储栈中的元素
int a[MAX_SIZE];
// 定义一个变量top，用于指向栈顶元素
int top=-1;

// 定义一个函数Push，用于将元素x压入栈中
void Push(int x)
{
    // 如果栈已满，则输出错误信息
    if(top==MAX_SIZE-1)
    {
        printf("stack overflow\n");
        return;
    }
    // 将元素x压入栈中
    a[++top]=x;
}

// 定义一个函数Pop，用于将栈顶元素弹出
void Pop()
{
    // 如果栈为空，则输出错误信息
    if(top==-1)
    {
        printf("Error:no element to pop\n");
        return;
    }
    // 将栈顶元素弹出
    top--;
}

// 定义一个函数Top，用于返回栈顶元素
int Top()
{
    // 返回栈顶元素
    return a[top];
}

int main(void)
{

    Push(10);
    Push(20);
    Push(30);
    printf("%d\n",Top()); //30
    Pop();
    printf("%d\n",Top()); //20
    return 0;
}