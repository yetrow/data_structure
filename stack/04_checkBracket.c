#include<stdio.h>
#include<string.h>
#include<windows.h>
#include<stdlib.h>


#define MAX_SIZE 100

/*
struct Node*
{   int data
    int next
};
*/

char stack[MAX_SIZE] = {0};//数组
int top = -1;

void Push(char x)
{
    if(top == MAX_SIZE)
    {
        printf("the stack is overflow!");
        return;
    }
    stack[++top] = x;
}


void Pop()
{
    if(top == -1)
    {
        printf("the stack is empty");
        return;
    }
    top--;
}

char Top()
{
    if(top == -1)
    {
        //printf("the stack is empty"); // 在 Balance 函数中处理空栈情况
        return '\0'; // 返回一个特殊值表示栈空
    }
    return stack[top];
}

int IsEmpty(); // 函数原型声明

int IsEmpty()
{
    if(top == -1)
        return 1;
    else
        return 0;
}

void Print()
{
    printf("The stack is:\n");
    for(int i = 0; i <= top; i++)
    {
        printf("%d", stack[i]);
    }
    printf("\n");
}


int Balance(char c[])
{
    for(int i = 0; i < strlen(c); i++) // 循环条件改为 <
    {
        if((c[i] == '(') || (c[i] == '[') || (c[i] == '{'))
            {
                Push(c[i]);
            }
        else if((c[i] == ')') || (c[i] == ']') || (c[i] == '}'))//只需要与栈顶进行比较
            {
                if(IsEmpty()) // 遇到右括号时检查栈是否为空
                {
                    return 0; // 栈为空，不匹配
                }
                char top_char = Top();
                if((c[i] - top_char == 1) || (c[i]-top_char == 2))
                {
                    Pop();
                }
                else
                    return 0; // 不匹配
            }
    }
    return IsEmpty() ? 1 : 0; // 循环结束后检查栈是否为空
}


int main()
{
    char n[MAX_SIZE];
    int flag = -1;//是否平衡的变量

    printf("Enter a string:\n");
    fgets(n, MAX_SIZE, stdin);
    // 移除 fgets 读取到的换行符
    n[strcspn(n, "\n")] = 0;

    flag = Balance(n);

    if(flag == 1)
        printf("success!\n");
    else
        printf("fail...\n");

    system("pause");
    return 0;
}


/*
( 的 ASCII 值是 40
) 的 ASCII 值是 41
[ 的 ASCII 值是 91
] 的 ASCII 值是 93
{ 的 ASCII 值是 123
} 的 ASCII 值是 125
*/