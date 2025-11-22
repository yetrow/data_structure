#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // 添加 isdigit() 函数
#define MAX_SIZE 100

/*
    Infix   中缀    2 + 3   a + b * c
    Prefix  前缀    + 2 3   + a * b c
    Suffix 后缀    2 3 +   a b c * +
*/





typedef struct Node
{
    int data;  
    struct Node* next;
}Node;

int Perform(int num1, char op, int num2);  // 返回类型改为 int
Node* Push(Node* p, int data);  // data 类型改为 int
Node* Pop(Node* p);
int Top(Node* p);  // 返回类型改为 int

// int EvaluatePostfix(char exp[])  // 返回类型改为 int
// {
//     struct Node* stack = NULL;
//     for(int i = 0; i < strlen(exp); i++)  // 修改循环条件，去掉等号
//     {
//         if(isdigit(exp[i]))  // 使用 isdigit() 判断数字
//         {
//             stack = Push(stack, exp[i] - '0');  // 转换为数字值存储
//         }
//         else if(exp[i] == '+' || exp[i] == '-' || exp[i] == '*' || exp[i] == '/' || exp[i] == '^')
//         {
//             int num2 = Top(stack);
//             stack = Pop(stack);
//             int num1 = Top(stack);
//             stack = Pop(stack);
//             stack = Push(stack, Perform(num1, exp[i], num2));
//         }
//     }
//     return Top(stack);
// }

int EvaluatePostfix(char exp[]) // exp 是输入的后缀表达式字符串
{
    struct Node* stack = NULL; 

    for(int i = 0; i < strlen(exp); i++) // 循环遍历表达式字符串 exp
    {
        // i 从 0 开始，直到字符串的最后一个字符 (strlen(exp) - 1)
        // 注意循环条件是 i < strlen(exp)，因为字符串下标从 0 开始，到 length-1 结束
        char currentChar = exp[i]; // 获取当前处理的字符

        if(isdigit(currentChar)) // 如果当前字符是数字 (例如 '0', '1', ..., '9')
        {
            // 是数字，根据算法，压入栈中
            // '0' 的 ASCII 值是 48，'1' 是 49，以此类推
            // currentChar - '0' 将字符数字转换为对应的整数值
            // 例如 '5' - '0' = 53 - 48 = 5
            stack = Push(stack, currentChar - '0'); // 调用 Push 函数将整数值压入栈
            printf("扫描到数字 '%c'. 压入栈 %d. 栈顶: %d\n", currentChar, currentChar - '0', Top(stack)); // 调试信息
        }
        else if(currentChar == '+' || currentChar == '-' || currentChar == '*' || currentChar == '/' || currentChar == '^') // 如果当前字符是运算符
        {
            // 是运算符，根据算法，需要弹出栈顶的两个操作数，进行计算，然后将结果压回栈
            printf("扫描到运算符 '%c'. ", currentChar); // 调试信息

            // 1. 弹出第二个操作数 (栈顶)
            int num2 = Top(stack); // 获取栈顶元素的值 (这是第二个操作数)
            stack = Pop(stack);    // 弹出栈顶元素
            printf("弹出第二个操作数: %d. ", num2); // 调试信息

            // 2. 弹出第一个操作数 (新的栈顶)
            int num1 = Top(stack); // 获取新的栈顶元素的值 (这是第一个操作数)
            stack = Pop(stack);    // 弹出新的栈顶元素
            printf("弹出第一个操作数: %d. ", num1); // 调试信息

            // 3. 执行运算
            int result = Perform(num1, currentChar, num2); // 调用 Perform 函数计算 num1 op num2
            printf("执行运算 %d %c %d = %d. ", num1, currentChar, num2, result); // 调试信息

            // 4. 将结果压回栈
            stack = Push(stack, result); // 将计算结果压入栈
            printf("压入结果 %d. 栈顶: %d\n", result, Top(stack)); // 调试信息
        }
        // 注意：这个简单的代码没有处理空格或其他非数字非运算符的字符
        // 也没有处理单目运算符或输入错误的情况
    }

    // 循环结束，栈中应该只剩下一个元素，就是最终结果
    int finalResult = Top(stack); // 获取栈顶的最终结果

    // 释放栈中剩余的节点，防止内存泄漏 (虽然 EvaluatePostfix 只返回结果，但良好的实践是清理)
    // 在这个简单的例子中，因为整个程序即将结束，不清理也问题不大，
    // 但如果 EvaluatePostfix 是一个子函数，并且栈是在内部 malloc 的，就需要清理
    while (stack != NULL) {
        stack = Pop(stack);
    }
    printf("栈已清空.\n"); 

    return finalResult; 
}


int Perform(int num1, char op, int num2)  
{
    switch(op)
    {
        case '+': return num1 + num2;
        case '-': return num1 - num2;
        case '*': return num1 * num2;
        case '/': return num1 / num2;
        case '^': 
        {
            int result = 1;
            for(int i = 0; i < num2; i++) 
                result *= num1;
            return result;
        }
        default: return 0;
    }
}

Node* Push(Node* p, int data)  
{
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = p;
    p = temp;
    return p;
}

Node* Pop(Node* p)
{
    Node* temp = p;
    if(p == NULL)
        return p;
    p = p->next;
    free(temp);
    return p;
}

int Top(Node* p)  
{
    if(p != NULL)
        return p->data;
    return 0;
}

int main()
{
    char n[MAX_SIZE];
    fgets(n, MAX_SIZE, stdin);  // 更安全的输入方式
    n[strcspn(n, "\n")] = '\0'; // 去除换行符
    printf("result is: %d\n", EvaluatePostfix(n));
    return 0;
}