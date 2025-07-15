#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

#define MAX_SIZE 100

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* Push(Node* p,int data);
Node* Pop(Node* p);
int Top(Node* p);

int perform(int num1,char op,int num2)
{
    switch(op)
    {
        case '+':return num1+num2;
        case '-':return num1-num2;
        case '*':return num1*num2;
        case '/':return num1/num2;
        default: return 0;
    }
}

Node* Push(Node* p,int data)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=data;
    temp->next=p;
    p=temp;

    return p;
}
Node* Pop(Node* p)
{
    Node* temp=p;
    if(p==NULL)
        return p;
    p=p->next;
    free(temp);

    return p;
}
int Top(Node* p)
{
    if(p!=NULL)
        return p->data;
    return 0; 
}

int Count(char exp[])
{
    Node* stack=NULL;
    
    for(size_t i=0;i<strlen(exp);i++)
    {
        char current=exp[i];

        if(isdigit(current))
        {
            stack=Push(stack,current-'0'); //将字符形式的数字转换为整数形式
                                            //current 是字符 '5'，其 ASCII 值为 53。字符 '0' 的 ASCII 值为 48。
                                            //current - '0' 实际上是 53 - 48，结果是整数 5。
            printf("扫描到数字'%c',压入栈'%d'.栈顶'%d'\n",current,current-'0',Top(stack));
        }
        else if(current == '+' || current == '-' || current == '*' || current == '/' || current == '^')
        {
            printf("扫描到运算符'%c'.\n",current);

            int num2=Top(stack);
            stack=Pop(stack);
            printf("弹出第二个操作数是'%d'.\n",num2);

            int num1=Top(stack);
            stack=Pop(stack);
            printf("弹出第一个操作数是'%d'.\n",num1);

            int res=perform(num1,current,num2);
            printf("执行运算 %d %c %d = %d",num1,current,num2,res);
            stack=Push(stack,res); // Push the result back onto the stack
            printf(", 运算结果'%d'压入栈.栈顶'%d'\n",res,Top(stack));
        }
    }
    int finalres=Top(stack);
    while(stack!=NULL)
    {
        stack=Pop(stack);
    }
    puts("栈已清空\n");

    return finalres;
}





int main(void)
{
    char n[MAX_SIZE];
    fgets(n,MAX_SIZE,stdin);
    n[strcspn(n,"\n")]='\0';

    printf("result is: %d\n",Count(n));
}