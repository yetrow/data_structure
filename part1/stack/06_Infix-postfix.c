#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_SIZE 100

typedef struct Node
{
    char data;
    struct Node* next;
}Node;

Node* Push(Node* p, char data)
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

void Print(Node* p)
{
    if(p == NULL)
        return;
    printf("栈为：");
    while(p != NULL)
    {
        printf("%c", p->data);  // 修正打印格式
        p = p->next;  // 修正指针移动
    }
    printf("\n");
}

char Top(Node* p)
{
    if(p != NULL)
        return p->data;
    return '\0';  // 栈为空时返回空字符
}

int IsEmpty(Node* p)
{
    return p == NULL;
}

int IsLeftBracket(char n)
{
    return n == '(';
}

int HasHigherPrec(char exp1, char exp2)
{
    // 定义优先级
    int prec1 = 0, prec2 = 0;
    
    switch(exp1) {
        case '^': prec1 = 4; break;
        case '*':
        case '/': prec1 = 3; break;
        case '+':
        case '-': prec1 = 2; break;
    }
    
    switch(exp2) {
        case '^': prec2 = 4; break;
        case '*':
        case '/': prec2 = 3; break;
        case '+':
        case '-': prec2 = 2; break;
    }
    
    return prec1 >= prec2;  // 栈顶运算符优先级高于或等于当前运算符
}

// 将中缀表达式 exp 转换为后缀表达式
char* InfixToPostfix(char exp[]) // exp 是输入的中缀表达式字符串
{
    int n = 0; // 用于记录后缀表达式结果字符串的当前写入位置
    Node* stack = NULL; // 初始化一个空栈，用于存放运算符和左括号

    // 为结果字符串分配内存
    // 理论上，后缀表达式的长度不会超过中缀表达式长度 (操作数不变，运算符位置移动)
    // MAX_SIZE 是一个安全的上限
    char* res = (char*)malloc(sizeof(char) * MAX_SIZE);
    if (res == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(EXIT_FAILURE);
    }

    // 扫描输入的中缀表达式
    for(int i = 0; i < strlen(exp); i++)
    {
        char currentChar = exp[i]; // 获取当前字符

        // Debugging prints (useful for seeing the process)
        printf("扫描: '%c'. ", currentChar);
        // Print(stack); // Print stack before processing character

        if(isdigit(currentChar)) // 如果当前字符是数字 (操作数)
        {
            // 规则 1: 如果是操作数，直接添加到结果字符串
            res[n++] = currentChar;
            printf("操作数. 输出: %s\n", res); // Debug
        }
        else if(currentChar == '+' || currentChar == '-' ||
                currentChar == '*' || currentChar == '/' ||
                currentChar == '^') // 如果当前字符是运算符
        {
            // 规则 2: 如果是运算符
            printf("运算符. ");
            // While stack is not empty, top is not '(', AND top has higher or equal precedence:
            // Pop stack operator and append to result
            while(!IsEmpty(stack) &&
                  !IsLeftBracket(Top(stack)) &&
                  HasHigherPrec(Top(stack), currentChar)) // 栈顶运算符优先级 >= 当前运算符
            {
                res[n++] = Top(stack); // 将栈顶运算符添加到结果
                stack = Pop(stack);    // 弹出栈顶运算符
                 printf("因优先级弹出 '%c'. 输出: %s\n", res[n-1], res); // Debug
            }
            // Push the current operator onto the stack
            stack = Push(stack, currentChar); // 将当前运算符压入栈
            printf("压入 '%c'. ", currentChar); Print(stack); // Debug
        }
        else if(currentChar == '(') // 如果当前字符是左括号
        {
            // 规则 3: 如果是左括号，压入栈
            printf("左括号. ");
            stack = Push(stack, currentChar);
            Print(stack); // Debug
        }
        else if(currentChar == ')') // 如果当前字符是右括号
        {
            // 规则 4: 如果是右括号
            printf("右括号. ");
            // Pop operators from stack and append to result until a left bracket '(' is found
            while(!IsEmpty(stack) && !IsLeftBracket(Top(stack)))
            {
                res[n++] = Top(stack); // 将栈顶运算符添加到结果
                stack = Pop(stack);    // 弹出栈顶运算符
                 printf("在括号内弹出 '%c'. 输出: %s\n", res[n-1], res); // Debug
            }
            // If stack is not empty and top is '(', pop the left bracket (and discard)
            if(!IsEmpty(stack) && IsLeftBracket(Top(stack)))
            {
                stack = Pop(stack); // 弹出左括号，不添加到结果
                printf("弹出 '('. "); Print(stack); // Debug
            }
            // TODO: Error handling for unmatched ')'
        }
        // TODO: Handle spaces or other invalid characters if necessary
        // printf("End of step stack: "); Print(stack); // Debug after processing character
    }

    // 规则 5: 扫描完表达式后，将栈中剩余的所有运算符弹出并添加到结果字符串
    printf("表达式结束. 弹出剩余运算符.\n"); // Debug
    while(!IsEmpty(stack))
    {
        // TODO: Error handling for unmatched '(' remaining in stack
        res[n++] = Top(stack); // 将栈顶运算符添加到结果
        stack = Pop(stack);    // 弹出栈顶运算符
        printf("弹出 '%c'. 输出: %s\n", res[n-1], res); // Debug
    }

    res[n] = '\0'; // 在结果字符串末尾添加 null 终止符

    // 清理栈中可能剩余的节点 (虽然在上面的 while 循环中应该已经清空了)
    // 这是一个防御性清理，确保 malloc 的节点都被 free
    while (!IsEmpty(stack)) {
        stack = Pop(stack);
    }
    // printf("Stack cleaned up.\n"); // Debug

    return res; // 返回指向后缀表达式字符串的指针
}


int main()
{
    char n[MAX_SIZE];
    fgets(n, MAX_SIZE, stdin);  // 更安全的输入方式
    n[strcspn(n, "\n")] = '\0'; // 去除换行符
    
    char* postfix_exp = InfixToPostfix(n);
    printf("%s\n", postfix_exp);
    free(postfix_exp);  // 释放内存
    
    return 0;
}