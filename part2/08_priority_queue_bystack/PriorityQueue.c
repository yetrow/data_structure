#include "PriorityQueue.h"
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
    void* data;
    struct Node* next;
} Node;

struct PriorityQueue
{
    Node* head;
    size_t element_size;
    size_t size;
    CompareFunc compare_func;
};

PQueue* pqueue_create(size_t element_size, CompareFunc compare_func)
{
    if (element_size == 0 || compare_func == NULL) return NULL;
    PQueue* pq = (PQueue*)malloc(sizeof(PQueue));
    if (!pq) return NULL;
    pq->head = NULL;
    pq->element_size = element_size;
    pq->size = 0;
    pq->compare_func = compare_func;
    return pq;
}

void pqueue_destroy(PQueue** pqueue_p)
{
    if (pqueue_p && *pqueue_p)
    {
        PQueue* pq = *pqueue_p;
        Node* current = pq->head;
        while (current != NULL)
        {
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
        free(pq);
        *pqueue_p = NULL;
    }
}

bool pqueue_enqueue(PQueue* pqueue, const void* element_data)
{
    if (!pqueue || !element_data) return false;

    Node* new_node = (Node*)malloc(sizeof(Node));
    if (!new_node) return false;

    new_node->data = malloc(pqueue->element_size);
    if (!new_node->data) {
        free(new_node);
        return false;
    }
    memcpy(new_node->data, element_data, pqueue->element_size);
    new_node->next = NULL;

    // Case 1: 队列为空或新元素优先级最高
    if (pqueue->head == NULL || pqueue->compare_func(element_data, pqueue->head->data) < 0)
    {
        new_node->next = pqueue->head;
        pqueue->head = new_node;
    }
    else // Case 2: 遍历查找插入位置
    {
        Node* current = pqueue->head;
        while (current->next != NULL && pqueue->compare_func(element_data, current->next->data) >= 0)
        {
            current = current->next;
        }
        new_node->next = current->next;
        current->next = new_node;
    }

    pqueue->size++;
    return true;
}

bool pqueue_dequeue(PQueue* pqueue, void* output_buffer)
{
    if (!pqueue || pqueue_is_empty(pqueue)) return false;

    Node* temp = pqueue->head;
    memcpy(output_buffer, temp->data, pqueue->element_size);
    pqueue->head = pqueue->head->next;

    free(temp->data);
    free(temp);
    pqueue->size--;

    return true;
}

bool pqueue_peek(PQueue* pqueue, void* output_buffer)
{
    if (!pqueue || pqueue_is_empty(pqueue)) return false;
    memcpy(output_buffer, pqueue->head->data, pqueue->element_size);
    return true;
}

bool pqueue_is_empty(PQueue* pqueue)
{
    if (!pqueue) return true;
    return pqueue->size == 0;
}

size_t pqueue_get_size(PQueue* pqueue)
{
    if (!pqueue) return 0;
    return pqueue->size;
}
