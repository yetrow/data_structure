#include "LinkedStack.h"
#include <stdio.h>

typedef struct 
{
    int id;
    char name[20];
}  Record;

void print_record(const Record *record)
{
    printf("id: %d, name: %s\n", record->id, record->name);
}

void test_record_stack()
{
    printf("--- Testing Record Stack ---\n");

    // 1. 创建一个用于存储 Record 结构体的栈
    Stack* stack = stack_create(sizeof(Record));
    if (stack == NULL)
    {
        printf("Failed to create stack.\n");
        return;
    }
    printf("Stack created. Element size: %zu bytes.\n", sizeof(Record));
    printf("Is stack empty? %s\n", stack_is_empty(stack) ? "Yes" : "No");

    // 2. 创建一些 Record 实例并推入栈中
    Record r1 = {1, "Alice"};
    Record r2 = {2, "Bob"};
    Record r3 = {3, "Charlie"};

    printf("\nPushing elements...\n");
    stack_push(stack, &r1);
    printf("Pushed: "); print_record(&r1);
    stack_push(stack, &r2);
    printf("Pushed: "); print_record(&r2);
    stack_push(stack, &r3);
    printf("Pushed: "); print_record(&r3);

    printf("\nCurrent stack size: %zu\n", stack_get_size(stack));
    printf("Is stack empty? %s\n", stack_is_empty(stack) ? "Yes" : "No");

    // 3. 查看栈顶元素
    Record top_record;
    if (stack_peek(stack, &top_record))
    {
        printf("\nPeeking top element: ");
        print_record(&top_record);
    }
    printf("Stack size after peek: %zu\n", stack_get_size(stack));

    // 4. 弹出所有元素
    printf("\nPopping elements...\n");
    while (!stack_is_empty(stack))
    {
        Record popped_record;
        if (stack_pop(stack, &popped_record))
        {
            printf("Popped: ");
            print_record(&popped_record);
        }
    }

    printf("\nCurrent stack size: %zu\n", stack_get_size(stack));
    printf("Is stack empty? %s\n", stack_is_empty(stack) ? "Yes" : "No");

    // 5. 销毁栈
    stack_destroy(&stack);
    printf("\nStack destroyed.\n");
    printf("--- Test Finished ---\n");
}

int main()
{
    test_record_stack();

    return 0;
}
