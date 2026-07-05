#pragma once
#include <stddef.h>
#include <stdbool.h>

typedef struct AVLNode AVLNode;
typedef struct AVLTree AVLTree;


typedef int(*AVLCompareFunc)(const void* a, const void* b, const void* context);


