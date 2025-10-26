#include "SharedStack.h"
#include <stdlib.h>
#include <string.h>


struct SharedStack
{
    void* data;
    size_t capacity;
    size_t element_size;
    int top1;
    int top2;
} ;


Stack* stack_create(size_t total_capacity, size_t element_size)\
{
    if(total_capacity == 0 || element_size == 0)    return NULL;

    Stack* temp = (Stack*)malloc(sizeof(Stack));
    if(!temp)   return NULL;
    temp->data = malloc(element_size * total_capacity);

    if(!temp->data)
    {
        free(temp);
        return NULL;
    }

    temp->capacity = total_capacity;
    temp->element_size = element_size;
    temp->top1 = -1;
    temp->top2 = (int)total_capacity;   // 栈2从尾开始，capacity为空

    return temp;
}

void stack_destroy(Stack** stack_p)
{
    if(stack_p && *stack_p)
    {
        free((*stack_p)->data);
        free(*stack_p);
        *stack_p = NULL;
    }
}

bool stack_is_full(Stack* stack)
{
    if(!stack)  return true;

    return stack->top1 + 1 == stack->top2;
}

bool stack_is_empty(Stack* stack, StackNumber num)
{
    if(!stack)  return true;

    if(num == STACK_ONE)    return stack->top1 == -1;
    else    return stack->top2 == (int)stack->capacity;
}

bool stack_push(Stack* stack, StackNumber num, const void* element_data)
{
    if(!stack || !element_data || stack_is_full(stack))     return false;

    void* address;
    if(num == STACK_ONE)
    {
        stack->top1++;
        address = (char*)stack->data + (stack->top1 * stack->element_size);
    }
    else
    {
        stack->top2--;
        address = (char*)stack->data + (stack->top2 * stack->element_size);
    }

    memcpy(address, element_data, stack->element_size);
    return true;
}

bool stack_pop(Stack* stack, StackNumber num, void* output_buffer)
{
    if(!stack || !output_buffer || stack_is_empty(stack, num))   return false;

    void* address;
    if(num == STACK_ONE)
    {
        address = (char*)stack->data + (stack->top1 * stack->element_size);
        memcpy(output_buffer, address, stack->element_size);
        
        stack->top1--;
    }
    else{
        address = (char*)stack->data + (stack->top2 * stack->element_size);
        memcpy(output_buffer, address, stack->element_size);
        stack->top2++;
    }
    return true;
}

bool stack_peek(Stack* stack, StackNumber num, void* output_buffer)
{
    if(!stack || !output_buffer || stack_is_empty(stack, num))   return false;

    void* address;
    if(num == STACK_ONE)
    {
        address = (char*)stack->data + (stack->top1 * stack->element_size);
    }
    else{
        address = (char*)stack->data + (stack->top2 * stack->element_size);
    }
    memcpy(output_buffer, address, stack->element_size);

    return true;
}

size_t stack_get_size(Stack* stack, StackNumber num)
{
    if(!stack)  return 0;

    if(num == STACK_ONE)    return (size_t)(stack->top1 + 1);
    else                    return stack->capacity - stack->top2;
}

size_t stack_get_total_capacity(Stack* stack)
{
    if(!stack)  return 0;

    return stack->capacity;
}
