#pragma once
#include <stddef.h>
#include <stdbool.h>


typedef struct Deque Deque;


Deque* deque_create(size_t capacity, size_t element_size);

void deque_destroy(Deque** deque_p);

bool deque_push_front(Deque* dq, const void* element_data);

bool deque_push_back(Deque* dq, const void* element_data);

bool deque_pop_front(Deque* dq, void* output_buffer);

bool deque_pop_back(Deque* dq, void* output_buffer);

bool deque_peek_front(Deque* dq, void* output_buffer);

bool deque_peek_back(Deque* dq, void* output_buffer);

bool deque_is_empty(Deque* dq);

bool deque_is_full(Deque* dq);

size_t deque_get_size(Deque* dq);
