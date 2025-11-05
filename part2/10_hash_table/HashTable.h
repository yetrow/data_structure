#pragma once 
#include <stddef.h>
#include <stdbool.h>


// 用户只知道有 HashTable 这个类型，但无法访问其内部结构，实现了完美封装
typedef struct HashTable HashTable;

HashTable* ht_create(size_t capacity);

void ht_destroy(HashTable** ht_p);

// 插入或更新一个键值对
// ht 指向要操作的哈希表
// key 要插入/更新的键（一个c字符串）
// value 关联的值（一个c字符串）
bool ht_set(HashTable* ht, const char* key, const char* value);

// 从哈希表查找键并返回其值
const char* ht_get(const HashTable* ht, const char* key);

bool ht_remove(HashTable* ht, const char* key);

// 辅助函数，打印哈希表内部结构
void ht_print(const HashTable* ht);