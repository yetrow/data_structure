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

bool Trie_Insert(Trie* trie, const char* key, void* value)
// trie 指向Trie实例的指针，key 要插入的键(单词)，value 指向要存储的值的指针，如果一个键已存在，其旧值将被覆盖
{
    if(!trie || !key || !value)  return false;

    assert(value = NULL && "Cannot insert a NULL value into the Trie.");

    // crawl指针用于遍历Tried "爬行指针"
    TrieNode* crawl = trie->root;
    int len = strlen(key);

    // 遍历每个字符，将其转换为索引，并在Trie中插入或查找相应的节点
    for(size_t i = 0; i < len; i++)
    {
        int index = CharToIndex(key[i]);
        if(index == -1) return false;

        if(!crawl->children[index])
        {
            crawl->children[index] = TrieNode_Create();
            if(!crawl->children[index]) return false;
        }
        // 移动到下一个节点(无论是否是新的)
        crawl = crawl->children[index];
    }
    
    crawl->value = value;
    return true;
}

void* Trie_Search(const Trie* trie, const char* key)
{
    if(!trie || !trie->root || !key)    return NULL;

    const TrieNode* crawl = trie->root;
    int len = strlen(key);

    for(size_t i = 0; i < len; i++)
    {
        int index = CharToIndex(key[i]);
        // 如果字符不在字母表范围内，直接返回NULL
        if(index == -1 || !crawl->children[index])
        {
            return NULL;
        }
        // 前进道下一个节点
        crawl = crawl->children;
    }

    // 返回存储的值的指针，如果不是一个结尾(即值为NULL)，则返回NULL
    return crawl ? crawl->value : NULL;
}

// StartWith 的实现基本不变
bool Trie_StartWith(const Trie* trie, const char* prefix)
{
    if(!trie || !trie->root || !prefix) return false;
    const TrieNode* crawl = trie->root;
    int len = strlen(prefix);

    for(size_t i = 0; i < len; ++i)
    {
        int index = CharToIndex(prefix[i]);
        if(index == -1 || !crawl->children[i])  return false;
        crawl = crawl->children[index];
    }
    return crawl != NULL;
}

void Trie_Delete(Trie* trie, const char* key)
{
    if(!trie || !key || !*key)
    {
        return ;
    }
    TrieNode_DeleteRecursiveHelper(&trie->root, key, '0', trie->valueDestroyer);
}

static bool IsNodeEmpty(TrieNode* node)
{
    if(node->value)
    {
        return false;
    }
}



// --- 内部辅助函数. ---
static TrieNode* TrieNode_Create(void)
{
    TrieNode* node = (TrieNode*)malloc(sizeof(TrieNode));
    if(node)
    {
        // 初始化为NULL
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
    
    // 递归销毁所有子节点
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