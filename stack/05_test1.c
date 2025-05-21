#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

#define MAX_SIZE 100

typedef struct Node{
    int data;
    struct Node* next;
}Node;

Node* Pop(Node* p);
Node* Push(Node* p,int data);
int Top(Node* p);

int perform(int num1,char op,int num2)
{
    switch(op)
    {
        case '+': return num1+num2;
        case '-': return num1-num2;
        case '*': return num1*num2;
        case '/': return num1/num2;
        default: return 0;
    }
}

Node* Pop(Node* p)
{
    Node* temp=p;
    if(p!=NULL)
    {
        p=p->next;
    }
    else return p;

    free(temp);
    return p;
}
Node* Push(Node* p,int data)
{
    Node* temp=(Node*)malloc(sizeof(Node));
    temp->data=data;
    temp->next=p;
    p=temp;

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
            stack=Push(stack,current-'0');
            printf("扫描到数字%c,压入栈%d,栈顶%d\n",current,current-'0',Top(stack));
        }
        else if(current == '+' || current == '-' || current == '*' || current == '/' )
        {
            int num2=Top(stack);
            stack=Pop(stack);
            printf("弹出数字%d\n",num2);

            int num1=Top(stack);
            stack=Pop(stack);
            printf("弹出数字%d\n",num1);

            int res=perform(num1,current,num2);
            stack=Push(stack,res);
            
            printf("执行 %d %c %d = %d 运算",num1,current,num2,res);
            printf(", 运算结果'%d'压入栈.栈顶'%d'\n",res,Top(stack));
        }
    }
    int finalres=Top(stack);
    while(stack!=NULL)
        stack=Pop(stack);

    return finalres;
}






int main(void)
{
    char n[MAX_SIZE];
    fgets(n,MAX_SIZE,stdin);
    n[strcspn(n,"\n")]='\0';

    printf("result is: %d\n",Count(n));
}