#include "SequentialStack.h"
#include <stdlib.h>
#include <string.h>
#include <assert.h>


struct Stack
{
    void* data;             // 指向存储数据的连续内存块（我们的“数组”）
    size_t capacity;
    size_t element_size;    // 每个元素的大小
    int top;                // 栈顶索引，-1表示空栈
};


Stack* stack_create(size_t capacity, size_t element_size)
{
    if(capacity == 0 || element_size == 0)      return NULL;

    // 1. 为栈结构体分配内存
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(stack  == NULL) return NULL;

    // 2. 为存储数据的数组分配内存
    stack->data = malloc(capacity * element_size);
    if(stack->data == NULL)
    {
        free(stack);
        return NULL;
    }

    // 3. 初始化其他成员变量
    stack->capacity = capacity;
    stack->element_size = element_size;
    stack->top = -1;    // -1代表空栈

    return stack;
}

void stack_destroy(Stack** stack_p)
{
    if(stack_p == NULL || *stack_p == NULL) return;

    free((*stack_p)->data);
    free(*stack_p);
    *stack_p = NULL;
}

bool stack_push(Stack* stack, const void* element_data)
{
    if(stack == NULL || element_data == NULL) return false;
    if(stack_is_full(stack))    return false;      // 栈满，无法压入

    stack->top++;                                  //  栈顶指针上移，为新元素腾出空间
    // 计算要插入的位置的地址
    // stack->tio++;  先将 top 加 1，再计算地址
    // top => 0
    // top 0 => index

    // stack->top * stack->element_size 计算字节偏移量
    // stack->element_size 是每个元素的大小
    // 当top为 0 时，计算出来的偏移量就是 0*4 = 0
    
    // (char*)stack->data
    // c语言中，指针算术是基于类型的，需要将 void* 转换为 char*
    // 因为 char 是 1 字节的类型， 这样可以按字节进行偏移
    // 当我们把任何指针的类型转换为 char* 时，相当于告诉编译器，请把整个指针看作一个字节数组来处理
    // (char*)stack->data + N ：获取 stack->data 的地址，并且向后移动 N 个字节
    void* address = (char*)stack->data + (stack->top * stack->element_size);

    // 将用户数据拷贝到栈的内存中
    memcpy(address, element_data, stack->element_size);

    return true;
}

bool stack_pop(Stack* stack, void* output_buffer)
{
    if(stack == NULL || output_buffer == NULL) return false;

    if(stack_is_empty(stack))    return false;      

    void* address = (char*)stack->data + (stack->top * stack->element_size);

    memcpy(output_buffer, address, stack->element_size);

    stack->top--;      // 栈顶指针下移

    return true;
}

bool stack_peek(Stack* stack, void* output_buffer)
{
    if(stack == NULL || output_buffer == NULL) return false;

    if(stack_is_empty(stack))   return false;

    void* address = (char*)stack->data + (stack->top * stack->element_size);

    memcpy(output_buffer, address, stack->element_size);

    // 与 pop 的唯一区别：不移动 top 指针
    return true;
}

bool stack_is_empty(const Stack* stack)
{
    if(stack == NULL) return true;

    return stack->top == -1;
}

bool stack_is_full(const Stack* stack)
{
    if(stack == NULL) return false;     // 栈不满

    // 类型转换，避免有符号与无符号比较的错误
    return stack->top == (int)(stack->capacity - 1);
}

size_t stack_get_size(const Stack* stack)
{
    if(stack == NULL) return 0;

    return (size_t)(stack->top + 1);
}

size_t stack_get_capacity(const Stack* stack)
{
    if(stack == NULL) return 0;

    return stack->capacity;
}