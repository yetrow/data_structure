#include "GenericCircularQueue.h"
#include <stdio.h>
#include <stdlib.h>

// 辅助函数，用于打印队列的当前状态
void print_queue_state(const Queue* q, const char* title)
{
    printf("---------- %s ----------\n", title);
    if (!q)
    {
        printf("队列是 NULL\n\n");
        return;
    }

    printf("容量: %zu, 大小: %zu\n", queue_get_capacity(q), queue_get_size(q));
    printf("空？ %s, 满？ %s\n", queue_is_empty(q) ? "是" : "否", queue_is_full(q) ? "是" : "否");

    // 为了演示，我们访问队列的内部成员。
    // 注意：这破坏了封装性，通常不推荐在生产代码中这样做。
    // 这里的结构体定义必须与 GenericCircularQueue.c 中的定义完全匹配。
    struct CircularQueue_Internal 
    {
        void* data;
        size_t capacity;
        size_t element_size;
        size_t size;
        int front;
        int rear;
    };
    struct CircularQueue_Internal* internal_q = (struct CircularQueue_Internal*)q;
    printf("内部指针: front: %d, rear: %d\n", internal_q->front, internal_q->rear);

    // if (!queue_is_empty(q)) {
    //     int peek_val;
    //     queue_peek(q, &peek_val);
    //     printf("队头元素 (peek): %d\n", peek_val);
    // }
    // printf("\n");
}

int main()
{
    // 1. 创建一个容量为 4，用于存储 int 类型的队列
    size_t capacity = 4;
    Queue* q = queue_create(capacity, sizeof(int));
    print_queue_state(q, "1. 创建队列");

    // 2. 入队 3 个元素
    printf("---------- 2. 入队 3 个元素 ----------\n");
    for (int i = 10; i <= 30; i += 10) {
        printf("入队: %d\n", i);
        queue_enqueue(q, &i);
    }
    print_queue_state(q, "入队 3 个元素后");

    // 3. 出队 2 个元素
    printf("---------- 3. 出队 2 个元素 ----------\n");
    int dequeued_val;
    for (int i = 0; i < 2; ++i) {
        if (queue_dequeue(q, &dequeued_val)) {
            printf("出队: %d\n", dequeued_val);
        }
    }
    print_queue_state(q, "出队 2 个元素后");

    // 4. 填满队列，展示循环特性
    printf("---------- 4. 填满队列 ----------\n");
    int values_to_enqueue[] = {40, 50, 60};
    for (int i = 0; i < 3; ++i) {
        printf("尝试入队: %d\n", values_to_enqueue[i]);
        if (queue_enqueue(q, &values_to_enqueue[i])) {
            printf("  成功\n");
        } else {
            printf("  失败，队列已满\n");
        }
    }
    print_queue_state(q, "填满队列后 (rear 指针已循环)");

    // 5. 再次尝试入队一个元素到已满的队列
    printf("---------- 5. 尝试入队到满队列 ----------\n");
    int extra_val = 70;
    printf("尝试入队: %d\n", extra_val);
    if (!queue_enqueue(q, &extra_val)) {
        printf("  失败，队列已满\n");
    }
    print_queue_state(q, "尝试入队到满队列后");

    // 6. 出队所有元素
    printf("---------- 6. 出队所有元素 ----------\n");
    while (!queue_is_empty(q)) {
        if (queue_dequeue(q, &dequeued_val)) {
            printf("出队: %d\n", dequeued_val);
        }
    }
    print_queue_state(q, "出队所有元素后");

    // 7. 尝试从空队列中出队
    printf("---------- 7. 尝试从空队列出队 ----------\n");
    if (!queue_dequeue(q, &dequeued_val)) {
        printf("出队失败，队列为空\n");
    }
    print_queue_state(q, "尝试从空队列出队后");

    // 8. 销毁队列
    printf("---------- 8. 销毁队列 ----------\n");
    queue_destroy(&q);
    print_queue_state(q, "销毁队列后");
    if (q == NULL) {
        printf("队列指针已设为 NULL\n");
    }

    return 0;
}
