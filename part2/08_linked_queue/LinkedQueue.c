#include "LinkedQueue.h"
#include <stdlib.h>
#include <string.h>


typedef struct Node
{
    void* data;
    struct Node* next;
} Node;

struct LinkedQueue
{
    Node* front;
    Node* rear;
    size_t element_size;
    size_t size;
} ;


Queue* queue_create(size_t element_size)
{
    if(element_size == 0)   return NULL;
    Queue* q = (Queue*)malloc(sizeof(Queue));
    if(!q)   return NULL;
    q->front = NULL;
    q->rear = NULL;
    q->element_size = element_size;
    q->size = 0;

    return q;
}

void queue_destroy(Queue** queue_p)
{
    if(queue_p && *queue_p)
    {
        Queue* q = *queue_p;
        Node* current = q->front;
        while(current != NULL)
        {
            Node* temp = current;
            current = current->next;
            free(temp->data);
            free(temp);
        }
        free(q);
        *queue_p = NULL;
    }
}

bool queue_enqueue(Queue* queue, const void* element_data)
{
    if(!queue || !element_data)   return false;
    
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)   return false;

    new_node->data = malloc(queue->element_size);
    if(!new_node->data) {
        free(new_node);
        return false;
    }

    memcpy(new_node->data, element_data, queue->element_size);
    new_node->next = NULL;

    if(queue_is_empty(queue))
    {
        queue->front = new_node;
        queue->rear = new_node;
    }
    else // 常规情况
    {
        queue->rear->next = new_node;
        queue->rear = new_node;
    }
    queue->size++;

    return true;
}

bool queue_dequeue(Queue* queue, void* output_buffer)
{
    if(!queue || queue_is_empty(queue))   return false;

    Node* temp = queue->front;
    memcpy(output_buffer, temp->data, queue->element_size);
    queue->front = queue->front->next;

    if (queue->front == NULL)
    {
        queue->rear = NULL;
    }

    free(temp->data);
    free(temp);
    queue->size--;

    return true;
}

bool queue_peek(Queue* queue, void* output_buffer)
{
    if(!queue || queue_is_empty(queue))   return false;

    memcpy(output_buffer, queue->front->data, queue->element_size);

    return true;
}

bool queue_is_empty(Queue* queue)
{
    if(!queue)  return true;
    return queue->size == 0;
}

size_t queue_get_size(Queue* queue)
{
    if(!queue)  return 0;
    return queue->size;
}
