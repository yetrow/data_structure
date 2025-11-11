#pragma once

#include <stddef.h>
#include <stdbool.h>


typedef struct BST BST;

//比较函数指针类型
typedef int(*CompareFunc)(const void* a, const void* b);

// 访问函数指针类型，用于遍历
typedef void (*VisitFunc)(const void* data);

// 遍历顺序的枚举
typedef enum 
{
    IN_ORDER,       // 中序遍历(LNR -> 结果有序)
    PRE_ORDER,      // 前序遍历(NLR)
    POST_ORDER      // 后续遍历(LRN)
} TraverseOrder;

// --- Public Api Prototypes ---

BST* bst_create(size_t element_size, CompareFunc compare_func);

void bst_destroy(BST** bst_p);

bool bst_insert(BST* bst, const void* element_data);

bool bst_remover(BST* bst, const void* element_data);

bool bst_search(const BST* bst, const void* key);

void bst_traverse(const BST* bst, TraverseOrder order, VisitFunc visit_func);

bool bst_is_empty(const BST* bst);
size_t bst_get_size(const BST* bst);
