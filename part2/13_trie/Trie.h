#pragma once
#include <stdbool.h>
#include <stddef.h>

typedef struct Trie Trie;

//  定义一个函数指针类型，用于销毁用户自定义的值
// 当Trie被销毁时，如果节点上存有值，Trie会调用这个函数来释放值的内存
typedef void(*ValueDestroyer)(void* value);

Trie* Trie_Create(ValueDestroyer destroyer);

void Trie_Destroy(Trie* trie);

bool Trie_Insert(Trie* trie, const char* key, void* value);

void* Trie_Search(const Trie* trie, const char* key);

bool Trie_StartsWith(const Trie* trie, const char* prefix);

void Trie_Delete(Trie* trie, const char* key);
