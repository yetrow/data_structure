#pragma once
#include <stddef.h>        // for size_t 
#include <stdbool.h>


typedef struct Stack Stack;

Stack* stack_create(size_t capacity, size_t element_size);

void stack_destroy(Stack** stack_p);

bool stack_push(Stack* stack, const void* element_data);

// output_buffer 是指向一个缓冲区的指针，用于接收弹出的元素数据
bool stack_pop(Stack* stack, void* output_buffer);

// 查看栈顶元素，但不弹出
bool stack_peek(Stack* stack, void* output_buffer);

bool stack_is_empty(const Stack* stack);

bool stack_is_full(const Stack* stack);

size_t stack_get_size(const Stack* stack);

size_t stack_get_capacity(const Stack* stack);