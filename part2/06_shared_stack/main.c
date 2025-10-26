#include "SharedStack.h"
#include <stdio.h>
#include <stdlib.h>

void print_stack_state(Stack* stack)
{
    if(!stack)
    {
        printf("Stack is NULL\n");
        return;
    }

    puts("--------------");
    printf("Total Capacity: %zu\n", stack_get_total_capacity(stack));
    printf("Is Full: %s\n", stack_is_full(stack) ? "Yes" : "No");
    printf("Stack 1 Size: %zu (Empty: %s)\n", stack_get_size(stack, STACK_ONE), stack_is_empty(stack, STACK_ONE) ? "Yes" : "No");
    printf("Stack 2 Size: %zu (Empty: %s)\n", stack_get_size(stack, STACK_TWO), stack_is_empty(stack, STACK_TWO) ? "Yes" : "No");
    puts("--------------\n");
}

int main()
{
    printf("创建一个容量为10的共享栈。\n");
    Stack* s = stack_create(10, sizeof(int));
    print_stack_state(s);

    // --- 测试入栈 ---
    printf("向栈1推入5个元素...\n");
    for (int i = 1; i <= 5; ++i) {
        stack_push(s, STACK_ONE, &i);
    }
    print_stack_state(s);

    printf("向栈2推入5个元素...\n");
    for (int i = 101; i <= 105; ++i) {
        stack_push(s, STACK_TWO, &i);
    }
    print_stack_state(s);

    printf("尝试向已满的栈中推入元素 (应失败)...\n");
    int extra = 999;
    if (!stack_push(s, STACK_ONE, &extra)) {
        printf("入栈失败，符合预期。\n");
    }
    print_stack_state(s);

    // --- 测试查看栈顶 ---
    int peek_val;
    printf("查看栈1的栈顶元素...\n");
    if (stack_peek(s, STACK_ONE, &peek_val)) {
        printf("栈1的栈顶是: %d\n", peek_val);
    }
    printf("查看栈2的栈顶元素...\n");
    if (stack_peek(s, STACK_TWO, &peek_val)) {
        printf("栈2的栈顶是: %d\n", peek_val);
    }
    // 查看栈顶后，状态不应改变
    print_stack_state(s);

    // --- 测试出栈 ---
    int pop_val;
    printf("从栈1弹出2个元素...\n");
    for(int i = 0; i < 2; ++i) {
        if (stack_pop(s, STACK_ONE, &pop_val)) {
            printf("弹出: %d\n", pop_val);
        }
    }
    print_stack_state(s);

    printf("从栈2弹出3个元素...\n");
    for(int i = 0; i < 3; ++i) {
        if (stack_pop(s, STACK_TWO, &pop_val)) {
            printf("弹出: %d\n", pop_val);
        }
    }
    print_stack_state(s);

    // --- 弹栈直到空 ---
    printf("弹出栈1中所有剩余元素...\n");
    while(!stack_is_empty(s, STACK_ONE)) {
        stack_pop(s, STACK_ONE, &pop_val);
        printf("弹出: %d\n", pop_val);
    }
    print_stack_state(s);

    printf("尝试从空的栈1中弹出 (应失败)...\n");
    if (!stack_pop(s, STACK_ONE, &pop_val)) {
        printf("出栈失败，符合预期。\n");
    }
    print_stack_state(s);

    // --- 销毁栈 ---
    printf("销毁栈...\n");
    stack_destroy(&s);
    if (s == NULL) {
        printf("栈已成功销毁。\n");
    }
    print_stack_state(s);

    return 0;
}
