#pragma once
#include <stddef.h>     // for size_t 
#include <stdbool.h>    // for bool

// 无论是顺序栈还是链式栈 push和pop 的时间复杂度都是O(1)

typedef struct LinkedStack Stack;


Stack* stack_create(size_t element_size);

void stack_destroy(Stack** stack_p);

bool stack_push(Stack* stack, const void* element_data);

bool stack_pop(Stack* stack, void* output_buffer);

bool stack_peek(const Stack* stack, void* output_buffer);

bool stack_is_empty(const Stack* stack);

size_t stack_get_size(const Stack* stack);



