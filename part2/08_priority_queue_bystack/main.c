#include "PriorityQueue.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    int priority; // 优先级，数值越小，优先级越高
} Task;

// 比较函数：根据任务的优先级进行比较
int compare_tasks(const void* a, const void* b) {
    const Task* task_a = (const Task*)a;
    const Task* task_b = (const Task*)b;
    return task_a->priority - task_b->priority;
}

void print_task(const Task* t) {
    if (t) {
        printf("Task(id: %d, priority: %d)", t->id, t->priority);
    }
}

void print_pqueue(PQueue* pq, const char* title) {
    printf("-----%s-----\n", title);
    if (!pq) {
        printf("优先队列是NULL\n\n");
        return;
    }
    printf("大小: %zu, 空？%s\n", pqueue_get_size(pq), pqueue_is_empty(pq) ? "是" : "否");

    Task peeked_task;
    if (pqueue_peek(pq, &peeked_task)) {
        printf("队首元素: ");
        print_task(&peeked_task);
        printf("\n");
    } else {
        printf("优先队列为空\n");
    }
    printf("\n");
}

int main() {
    // 1. 创建优先队列
    PQueue* pq = pqueue_create(sizeof(Task), compare_tasks);
    print_pqueue(pq, "初始化优先队列");

    // 2. 定义任务
    Task t1 = {1, 3}; // 优先级 3
    Task t2 = {2, 1}; // 优先级 1 (最高)
    Task t3 = {3, 2}; // 优先级 2
    Task t4 = {4, 1}; // 优先级 1 (与t2相同)
    Task t5 = {5, 4}; // 优先级 4 (最低)

    // 3. 按任意顺序入队
    printf("任务(1, 3)入队...\n");
    pqueue_enqueue(pq, &t1);
    print_pqueue(pq, "任务(1, 3)入队后");

    printf("任务(2, 1)入队...\n");
    pqueue_enqueue(pq, &t2);
    print_pqueue(pq, "任务(2, 1)入队后");

    printf("任务(3, 2)入队...\n");
    pqueue_enqueue(pq, &t3);
    print_pqueue(pq, "任务(3, 2)入队后");
    
    printf("任务(4, 1)入队...\n");
    pqueue_enqueue(pq, &t4);
    print_pqueue(pq, "任务(4, 1)入队后");

    printf("任务(5, 4)入队...\n");
    pqueue_enqueue(pq, &t5);
    print_pqueue(pq, "任务(5, 4)入队后");

    // 4. 按优先级顺序出队
    printf("开始按优先级出队...\n");
    Task dequeued_task;
    while (!pqueue_is_empty(pq)) {
        if (pqueue_dequeue(pq, &dequeued_task)) {
            printf("出队的元素: ");
            print_task(&dequeued_task);
            printf("\n");
        }
        print_pqueue(pq, "出队一个元素后");
    }

    // 5. 检查空队列
    if (!pqueue_dequeue(pq, &dequeued_task)) {
        printf("优先队列为空，无法出队。\n\n");
    }
    print_pqueue(pq, "尝试对空队列出队后");

    // 6. 销毁队列
    printf("销毁优先队列...\n");
    pqueue_destroy(&pq);
    print_pqueue(pq, "销毁优先队列后");

    return 0;
}
