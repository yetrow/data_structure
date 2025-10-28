#include "LinkedStack.h"
#include <stdio.h>
#include <string.h>

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

bool is_opener(char c)
{
    return c == '(' || c == '{' || c == '[';
}

bool matches(char opener, char closer)
{
    return  (opener == '(' && closer == ')') ||
            (opener == '{' && closer == '}') ||
            (opener == '[' && closer == ']');
}

bool check_brack(const char* code)
{
    Stack* stack = stack_create(sizeof(char));
    
    if(!stack)
    {
        fprintf(stderr, "Failed to create stack for bracket checking.\n");
        return false;
    }

    size_t len = strlen(code);
    for(size_t i = 0; i < len; i++)
    {
        char current_char = code[i];
        // 如果是开括号，则压入栈
        if(is_opener(current_char))
        {
            stack_push(stack, &current_char);
        }
        // 如果是闭括号，则检查栈顶元素
        else if(current_char == ')' || current_char == '}' || current_char == ']')
        {
            // 错误情况1：栈为空，闭括号多余
            if(stack_is_empty(stack))
            {
                fprintf(stderr, "Unmatched closing bracket '%c' found.\n", current_char);
                return false;
            }

            char popped_opener;
            // 从栈顶弹出一个开括号进行比较
            stack_pop(stack, &popped_opener);   // 将弹出的char存入popped_opener

            // 错误情况2：开括号和闭括号不匹配(类型不匹配)
            if(!matches(popped_opener, current_char))
            {
                fprintf(stderr, "Mismatched brackets: '%c' don't match '%c'.\n", popped_opener, current_char);

                stack_destroy(&stack);
                return false;
            }
        }
    }

    // 错误情况3：遍历结束，但是栈中仍然有未关闭的开括号
    if(!stack_is_empty(stack))
    {
        char unclosed_opener;

        // 查看一下是哪个开括号没有关闭
        stack_peek(stack, &unclosed_opener);
        fprintf(stderr, "Unmatched opening brackets remain in stack. \n");
        stack_destroy(&stack);
        return false;
    }
    
    // 销毁栈
    stack_destroy(&stack);

    return true;
}

void check()
{
    const char* test[] = {
        "int main() { int a = 1; }",// 有效
        "void foo() { if (a == 1) { return; } }",   // 有效
        "int main() { int a = 1; if (a == 1) { return; } }",    // 有效
        "([])]]"    ,    // 无效
    };
    int n = sizeof(test) / sizeof(test[0]);
    for (int i = 0; i < n; i++)
    {
        printf("正在检查: %s\n", test[i]);
        if (check_brack(test[i]))
        {
            printf("括号匹配成功\n");
        }
        else
        {
            printf("括号匹配失败\n");
        }
    }
}

int main()
{
    // 测试链式栈
    // test_record_stack();



    // 测试括号匹配器
    check();

    return 0;
}
