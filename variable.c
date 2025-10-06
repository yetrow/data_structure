#include<stdio.h>
#include<stdarg.h>

void average(int num, ...)
{
    int sum=0;
    va_list args;
    va_start(args,num);
    for(int i=0;i<num;i++){
        int value=va_arg(args,int);
        sum+=value;
    }
    printf("%d",sum);
    va_end(args);
}

int main(void)
{
    average(4,1,2,3,4);

    return 0;
}