#include "LinkedStack.h"
#include <stdlib.h>
#include <string.h>

// 内部节点结构，对用户不可见
typedef struct Node
{
    void* data;                 // 指向为该节点元素分配的内存
    struct Node* next;          // 指向栈中的下一个节点
} Node;

// 链式栈的实际管理结构
struct LinkedStack
{
    Node* top;
    size_t element_size;        // 栈中每个元素的大小（字节）
    size_t size;                // 栈中元素的个数
} ;

Stack* stack_create(size_t element_size)
{
    if(element_size == 0)   return NULL;

    Stack* stack = (Stack*)malloc(sizeof(Stack));
    if(!stack) return NULL;

    stack->top = NULL;
    stack->element_size = element_size;
    stack->size = 0;

    return stack;
}

void stack_destroy(Stack** stack_p)
{
    if(stack_p == NULL || *stack_p == NULL)     return ;

    Stack* stack = *stack_p;
    Node* current = stack->top;

    while(current != NULL)
    {
        Node* temp = current;
        current = current->next;
        if(temp->data != NULL)
        {
            free(temp->data);
        }
        free(temp);
    }

    free(stack);
    *stack_p == NULL;
}

bool stack_push(Stack* stack, const void* element_data)
{
    if(stack == NULL || element_data ==NULL)    return false;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if(new_node == NULL)
    {
        free(new_node);
        return false;
    }
    
    // 在 C 语言中（这和 C++ 不同），void* 可以被隐式地转换为任何其他类型的指针
    // 而 new_node->data 本身就是一个 void* 类型，所以这里不需要进行类型转换
    new_node->data = malloc(stack->element_size);
    if(new_node->data == NULL)
    {
        free(new_node);
        return false;
    }

    memcpy(new_node->data, element_data, stack->element_size);

    new_node->next = stack->top;
    stack->top = new_node;
                      
    stack->size++;
    return true;
}

bool stack_pop(Stack* stack, void* output_buffer)
{
    if(stack_is_empty(stack) || output_buffer == NULL)   return false;

    Node* temp_top = stack->top;

    memcpy(output_buffer, temp_top->data, stack->element_size);

    stack->top = temp_top->next;
    
    free(temp_top->data);
    free(temp_top);

    stack->size--;
    return true;
}

bool stack_peek(const Stack* stack, void* output_buffer)
{
    if(stack_is_empty(stack) || output_buffer == NULL)   return false;

    // 只需要拷贝数据，不需要修改任何指针或释放内存
    memcpy(output_buffer, stack->top->data, stack->element_size);

    return true;
}

bool stack_is_empty( const Stack* stack)
{
    if(stack == NULL)   return true;            

    return stack->top == NULL;      
}

size_t stack_get_size(const Stack* stack)
{
    if(stack == NULL)   return 0;

    return stack->size;
}