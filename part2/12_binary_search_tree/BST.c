#include "BST.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

// --- Private Structure Definitions ---
typedef struct Node
{
    void* data;
    struct Node* left;
    struct Node* right;
} Node;

struct BST
{
    Node* root;
    size_t element_size;
    size_t size;
    CompareFunc compare;
} ;

// --- Static Helper Functions (Recursive Implementations) ---

// 私有辅助函数：创建一个节点
static Node* _create_node(const void* data, size_t element_size)
{
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node)   return NULL;

    new_node->data = malloc(element_size);
    if(!new_node->data)
    {
        free(new_node);
        return NULL;
    }

    memcpy(new_node->data, data, element_size);
    new_node->left = NULL;
    new_node->right = NULL;
    
    return new_node;
}

// 私有辅助函数：递归销毁树(后序遍历)
static void _destroy_recursive(Node* node)
{
    if(node == NULL)    return;
    _destroy_recursive(node->left);
    _destroy_recursive(node->right);
    free(node->data);
    free(node);
}

// 私有辅助函数：递归插入新节点
static Node* _insert_recursive(BST* bst, Node* node, const void* data)
{
     if(node == NULL)
     {
        bst->size++;
        return _create_node(data, bst->element_size);
     }

     int cmp = bst->compare(data, node->data);

     if(cmp < 0)
     {
        node->left = _insert_recursive(bst, node->left, data);
     }
     else if(cmp > 0)
     {
        // 新数据比当前节点大，递归地插入到右子树
        node->right = _insert_recursive(bst, node->right, data);
     }
     
     // 如果 cmp == 0, 说明数据已经存在，我们什么都不需要做，直接返回原节点
     return node;
}

// 私有辅助函数：查找子树中最小的节点（用于删除）
static Node* _find_min_recursive(Node* node) 
{
    // 在BST中，最左边的节点永远是最小的。
    while (node && node->left != NULL) 
    {
        node = node->left;
    }

    return node;
}

// 私有辅助函数：删除
static Node* _remove_recursive(BST* bst, Node* node, const void* key)
{
    if(node == NULL)    return NULL;

    int cmp = bst->compare(key, node->data);

    if(cmp < 0)
    {
        node->left = _remove_recursive(bst, node->left, key);
    }
    else if(cmp > 0)
    {
        node->right = _remove_recursive(bst, node->right, key);
    }
    else
    {
        if(node->left == NULL && node->right == NULL)
        {
            free(node->data);
            free(node);
            bst->size--;
            return NULL;
        }

        if(node->left == NULL)
        {
            Node* temp = node->right;
            free(node->data);
            free(node);
            bst->size--;
            return temp;
        }

        else if(node->right == NULL)
        {
            Node* temp = node->left;
            free(node->data);
            free(node);
            bst->size--;
            return temp;
        }

        Node* successor = _find_min_recursive(node->right);
        memcpy(node->data, successor ->data, bst->element_size);
        node->right = _remove_recursive(bst, node->right, successor);
    }

    return node; 
}

static void _traverse_recursive(const Node* node, VisitFunc visit, TraverseOrder order)
{
    if(node == NULL)    return ;

    if(order == PRE_ORDER)  visit(node->data);
    _traverse_recursive(node->left, visit, order);
    if(order == IN_ORDER)   visit(node->data);
    _traverse_recursive(node->right, visit, order);
    if(order == POST_ORDER)  visit(node->data);
}

// --- Public Api Implementations ---

BST* bst_create(size_t element_size, CompareFunc compare_func)
{
    if(element_size == 0 || !compare_func)  return NULL;
    BST* bst = (BST*)malloc(sizeof(BST));
    if(!bst)    return NULL;
    bst->root = NULL;
    bst->element_size = element_size;
    bst->size = 0;
    bst->compare = compare_func;

    return bst;
}

void bst_destroy(BST** bst_p)
{
    if(bst_p && *bst_p)
    {
        _destroy_recursive((*bst_p)->root);
        free(bst_p);
        *bst_p = NULL;
    }
}

bool bst_insert(BST* bst, const void* element_data)
{
    if(!bst || !element_data)   return false;
    size_t old_size = bst->size;
    bst->root = _insert_recursive(bst, bst->root, element_data);
    // 如果size减小了，说明删除成功
    return bst->size > old_size;
}

bool bst_remove(BST* bst, const void* key)
{
    if(!bst || !key)    return false;
    
    size_t old_size = bst->size;

    bst->root = _remove_recursive(bst, bst->root, key);

    // 如果size减小了，说明删除成功
    return bst->size < old_size;
}

bool bst_search(const BST* bst, const void* key)
{
    if(!bst || !key)    return false;

    Node* current = bst->root;
    while(current != NULL)
    {
        int cmp = bst->compare(key, current->data);

        if(cmp == 0)    return true;
        if(cmp < 0)     current = current->left;
        else            current = current->right;
    }

    return false;
}


void bst_traverse(const BST* bst, TraverseOrder order, VisitFunc visit_func)
{
    if(bst && visit_func)
    {
        _traverse_recursive(bst->root, visit_func, order);
    }
}

bool bst_is_empty(const BST* bst)
{
    return !bst || bst->size == 0;
}

size_t bst_get_size(const BST* bst)
{
    return bst ? bst->size : 0;
}