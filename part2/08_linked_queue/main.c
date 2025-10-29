#include "LinkedQueue.h"
#include <stdio.h>
#include <string.h>

typedef struct {
    int id;
    char name[20];
} Person;

void print_person(const Person* p)
{
    if(p)
    {
        printf("id: %d, name: %s\n", p->id, p->name);
    }
}

void print_queue(Queue* q, const char* title)
{
    printf("-----%s-----\n", title);
    if(!q)
    {
        printf("队列是NULL\n\n");
        return ;
    }
    printf("大小: %zu, 空？%s\n", queue_get_size(q), queue_is_empty(q) ? "是" : "否");

    Person peeked_person;
    if(queue_peek(q, &peeked_person))
    {
        printf("队首元素: ");
        print_person(&peeked_person);
        printf("\n");
    }
    else
    {
        printf("队列为空\n");
    }
    printf("\n");
}

int main()
{
    // 1. 创建队列
    Queue* q = queue_create(sizeof(Person));
    print_queue(q, "初始化队列");

    // 2. 入队
    Person p1 = {1, "Alice"};
    Person p2 = {2, "Bob"};
    Person p3 = {3, "Charlie"};

    printf("p1 入队...\n");
    queue_enqueue(q, &p1);
    print_queue(q, "p1 入队后");

    printf("p2 入队...\n");
    queue_enqueue(q, &p2);
    print_queue(q, "p2 入队后");

    printf("p3 入队...\n");
    queue_enqueue(q, &p3);
    print_queue(q, "p3 入队后");

    // 3. 出队
    Person dequeued_person;
    printf("出队...\n");
    if (queue_dequeue(q, &dequeued_person)) {
        printf("出队的元素: ");
        print_person(&dequeued_person);
    }
    print_queue(q, "出队一个元素后");

    printf("出队...\n");
    if (queue_dequeue(q, &dequeued_person)) {
        printf("出队的元素: ");
        print_person(&dequeued_person);
    }
    print_queue(q, "再出队一个元素后");
    
    // 4. 再次入队
    Person p4 = {4, "David"};
    printf("p4 入队...\n");
    queue_enqueue(q, &p4);
    print_queue(q, "p4 入队后");

    // 5. 全部出队
    printf("出队...\n");
    if (queue_dequeue(q, &dequeued_person)) {
        printf("出队的元素: ");
        print_person(&dequeued_person);
    }
    print_queue(q, "再出队一个元素后");

    printf("出队...\n");
    if (queue_dequeue(q, &dequeued_person)) {
        printf("出队的元素: ");
        print_person(&dequeued_person);
    }
    print_queue(q, "再出队一个元素后");

    // 6. 检查空队列
    if (!queue_dequeue(q, &dequeued_person)) {
        printf("队列为空，无法出队。\n\n");
    }
    print_queue(q, "尝试对空队列出队后");

    // 7. 销毁队列
    printf("销毁队列...\n");
    queue_destroy(&q);
    print_queue(q, "销毁队列后");

    return 0;
}
