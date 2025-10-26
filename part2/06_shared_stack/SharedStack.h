#pragma once
#include <stddef.h>
#include <stdbool.h>


// 使用枚举来清晰地标识要操作的栈
typedef enum
{
    STACK_ONE = 1,  // 栈1，从数组头部开始
    STACK_TWO = 2   // 栈2，从数组尾部开始
} StackNumber;

// 不透明指针，用户无法看到内部结构
typedef struct SharedStack Stack;

Stack* stack_create(size_t total_capacity, size_t element_size);

void stack_destroy(Stack** stack_p);

bool stack_push(Stack* stack, StackNumber num, const void* element_data);

bool stack_pop(Stack* stack, StackNumber num, void* output_buffer);

bool stack_peek(Stack* stack, StackNumber num, void* output_buffer);

bool stack_is_full(Stack* stack);

bool stack_is_empty(Stack* stack, StackNumber num);

size_t stack_get_size(Stack* stack, StackNumber num);

size_t stack_get_total_capacity(Stack* stack);
