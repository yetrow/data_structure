#include "Deque.h"
#include <stdio.h>

void test_deque_as_queue()
{
    printf("--- 1. 使用双端队列模拟“标准队列” ---\n");
    printf("操作：push_back + pop_front\n");
    Deque* dq = deque_create(5, sizeof(int));
    int val;

    printf("Push Back: 10, 20, 30\n");
    for(val = 10; val <= 30;  val += 10)
    {
        deque_push_back(dq, &val);
    }
    printf("当前大小：%zu\n", deque_get_size(dq));

    int peek_val;
    deque_peek_front(dq, &peek_val);
    printf("Peek Front: %d\n", peek_val);
    deque_peek_back(dq, &peek_val);
    printf("Peek Back: %d\n", peek_val);


    printf("Pop Front: ");
    while(!deque_is_empty(dq))
    {
        deque_pop_front(dq, &val);
        printf("%d ", val);
    }
    printf("\n");
    printf("当前大小：%zu\n", deque_get_size(dq));
    deque_destroy(&dq);
    printf("\n");
}

void test_deque_as_stack_push_back()
{
    printf("--- 2. 使用双端队列模拟“栈”(后端入，后端出) ---\n");
    printf("操作：push_back + pop_back\n");
    Deque* dq = deque_create(5, sizeof(int));
    int val;

    printf("Push Back: 10, 20, 30\n");
    for(val = 10; val <= 30;  val += 10)
    {
        deque_push_back(dq, &val);
    }
    printf("当前大小：%zu\n", deque_get_size(dq));

    int peek_val;
    deque_peek_front(dq, &peek_val);
    printf("Peek Front: %d\n", peek_val);
    deque_peek_back(dq, &peek_val);
    printf("Peek Back: %d\n", peek_val);

    printf("Pop Back: ");
    while(!deque_is_empty(dq))
    {
        deque_pop_back(dq, &val);
        printf("%d ", val);
    }
    printf("\n");
    printf("当前大小：%zu\n", deque_get_size(dq));
    deque_destroy(&dq);
    printf("\n");
}

void test_deque_as_stack_push_front()
{
    printf("--- 3. 使用双端队列模拟“栈”(前端入，前端出) ---\n");
    printf("操作：push_front + pop_front\n");
    Deque* dq = deque_create(5, sizeof(int));
    int val;

    printf("Push Front: 10, 20, 30\n");
    for(val = 10; val <= 30;  val += 10)
    {
        deque_push_front(dq, &val);
    }
    printf("当前大小：%zu\n", deque_get_size(dq));

    int peek_val;
    deque_peek_front(dq, &peek_val);
    printf("Peek Front: %d\n", peek_val);
    deque_peek_back(dq, &peek_val);
    printf("Peek Back: %d\n", peek_val);

    printf("Pop Front: ");
    while(!deque_is_empty(dq))
    {
        deque_pop_front(dq, &val);
        printf("%d ", val);
    }
    printf("\n");
    printf("当前大小：%zu\n", deque_get_size(dq));
    deque_destroy(&dq);
    printf("\n");
}

void test_deque_full_and_empty()
{
    printf("--- 4. 测试队列满和空的情况 ---\n");
    Deque* dq = deque_create(3, sizeof(int));
    int val;

    printf("Push Front: 1, 2, 3\n");
    for (val = 1; val <= 3; ++val) {
        deque_push_front(dq, &val);
    }
    printf("Is full: %s\n", deque_is_full(dq) ? "true" : "false");
    printf("Size: %zu\n", deque_get_size(dq));

    printf("Push Front 4 (should fail): %s\n", deque_push_front(dq, &val) ? "success" : "fail");

    printf("Pop Back: ");
    while(!deque_is_empty(dq))
    {
        deque_pop_back(dq, &val);
        printf("%d ", val);
    }
    printf("\n");
    printf("Is empty: %s\n", deque_is_empty(dq) ? "true" : "false");
    printf("Size: %zu\n", deque_get_size(dq));

    deque_destroy(&dq);
}


int main()
{
    test_deque_as_queue();
    test_deque_as_stack_push_back();
    test_deque_as_stack_push_front();
    test_deque_full_and_empty();
    return 0;
}
