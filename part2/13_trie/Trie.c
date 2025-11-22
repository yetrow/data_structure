#include "Trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

// alphabet
#define ALPHABET_SIZE 26


typedef struct TrieNode
{
    // 用 void* 替换bool isEndOfWord. NULL表示非单词结尾
    void* value;
    // 指针数组，数组的每个格子(0~25)，都用来存放指向另一个TireNode的指针
    struct TrieNode* children[ALPHABET_SIZE];
} TrieNode;

struct Trie
{
    TrieNode* root;
    ValueDestroyer valueDestroyer;      // 存储用户提供的析构函数
} ;

// --- 私有函数原型保持不变 --- 
static TrieNode* TrieNode_Create(void);
static void TrieNode_DestroyRecursive(TrieNode* node, ValueDestroyer destroyer);
static int CharToIndex(char c);

// --- 公共函数实现修改 ---
Trie* Trie_create(ValueDestroyer destroyer)
{
    Trie* trie =(Trie*)malloc(sizeof(Trie));
    if(!trie)   return NULL;

    trie->root = TrieNode_Create();

    if(!trie->root)
    {
        free(trie);
        return NULL;
    }
    trie->valueDestroyer = destroyer;
    
    return trie;
}

void Trie_destroy(Trie* trie)
{
    if(trie)
    {
        TrieNode_DestroyRecursive(trie->root, trie->valueDestroyer);
        free(trie);
    }
    return ;
}

// ---  ---
static TrieNode* Trie_Create(void)
{
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if(node)
    {
        node->value = NULL;
        for(size_t i = 0; i < ALPHABET_SIZE; ++i)
        {
            node->children[i] = NULL;
        }
    }
    return node;
}

static void TrieNode_DestroyRecursive(TrieNode* node, ValueDestroyer destroyer)
{
    if(!node)   return ;
    
    for(size_t i = 0; i < ALPHABET_SIZE; ++i)
    {
        TrieNode_DestroyRecursive(node->children[i], destroyer);
    }

    // 关键一步：在释放节点本身之前，检查是否有用户数据需要释放
    if(node->value && destroyer)
    {
        destroyer(node->value);
    }
    free(node);
}

static int CharToIndex(char c)
{
    if(c >= 'a' && c <= 'z')    return c - 'a';
    return -1;
}