#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct LinkedQueue Queue;

Queue* queue_create(size_t element_size);

void queue_destroy(Queue** queue_p);

bool queue_enqueue(Queue* queue, const void* element_data);

bool queue_dequeue(Queue* queue, void* output_buffer);

bool queue_peek(Queue* queue, void* output_buffer);

bool queue_is_empty(Queue* queue);

size_t queue_get_size(Queue* queue);
