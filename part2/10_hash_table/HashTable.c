#include "HashTable.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
typedef struct Node
{
    char* key;          // 动态分配的键字符串
    char* value;        // 动态分配的值字符串
    struct Node* next;  // 指向链表的下一个节点
} Node;

// 哈希表的实际管理结构
struct HashTable
{
    Node** buckets;     // 指向一个指针数组，每个指针是一个桶（链表头结点）
    size_t capacity;    // 桶的数量
    size_t size;        // 当前存储的键值对总数
} ;


//----哈希函数：将字符串转换为一个在[0, capacity - 1]范围内的索引
static size_t hash_function(const char* key, size_t capacity)
{
    unsigned long hash_value = 0;
    for(size_t i = 0; key[i] != '\0'; i++)
    {
        hash_value += key[i];
    }

    return hash_value % capacity;
}

HashTable* ht_create(size_t capacity)
{
    if(capacity == 0)   return NULL;
    HashTable* ht = (HashTable*)malloc(sizeof(HashTable));
    if(!ht) return NULL;
    // 使用 calloc 分配并初始化桶，确保所有指针都为 NULL, 这是一个数组指针所以是 sizeof(Node*)
    ht->buckets = (Node**)calloc(capacity, sizeof(Node*));
    if(!ht->buckets)
    {
        free(ht);
        return NULL;
    }

    ht->capacity = capacity;
    ht->size = 0;
    return ht;
}

void ht_destroy(HashTable** ht_p)
{
    if(ht_p && *ht_p)
    {
        HashTable* ht = *ht_p;
        for(size_t i = 0; i < ht->capacity; i++)
        {
            // 遍历桶中的链表，释放每一个节点
            Node* current = ht->buckets[i];
            // 增加防御性检查，确保ht_free->key和ht_free->value非NULL后再释放
            while(current != NULL)
            {
                Node* ht_free = current;
                current = current->next;
                if(ht_free->key)
                {
                    free(ht_free->key);
                }
                if(ht_free->value)
                {
                    free(ht_free->value);
                }
                free(ht_free);
            }
        }
        free(ht->buckets);
        free(ht);
        *ht_p = NULL;
    }
}

bool ht_set(HashTable* ht, const char* key, const char* value)
{
    /*教学案例
    假设 capacity = 10, hash("name") = 4, hash("mane") = 4 (哈希冲突)
    案例1：插入("name", "Alice")
              - 计算哈希得到索引 4
              - 桶 4 为空，直接插入
              - 桶 4：->[("name", "Alice")] -> NULL
    案例2：插入("name", "Bob")
              - 计算哈希得到索引 4
              - 桶 4 不为空，遍历链表，未找到键"mane"
              - 在链表尾部插入
              - 桶 4：->[("name", "Alice")] -> [("name", "Bob")] -> NULL
    案例3：插入("mane", "Amy")
              - 计算哈希得到索引 4
              - 遍历桶 4 的链表，使用 strcmp()找到键 "name"
              - 释放旧值 "Alice" 的内存，分配新内存 "Amy"
              - 桶 4：->[("name", "Amy")] -> [("name", "Bob")] -> NULL
    */
    // 步骤1：防御性编程，检查输入参数
    if(!ht || !key || !value)   return false;
    // 步骤2：计算哈希值，得到索引（确定它属于哪个桶）
    size_t index = hash_function(key, ht->capacity);
    // 步骤3：遍历桶中的链表，查找键是否已存在
    Node* current = ht->buckets[index];
    while(current != NULL)
    {
        //--情况A：已经存在，执行“更新”操作
        if(strcmp(current->key, key) == 0)
        {
            free(current->value);
            current->value = (char*)malloc(strlen(value) + 1);

            if(!current->value) return false;
            strcpy(current->value, value);

            return true;
        }
        current = current->next;
    }

    //--情况B：不存在，执行“插入”操作
    // 步骤4：创建新节点
    Node* new_node = (Node*)malloc(sizeof(Node));
    if(!new_node) return false;

    // 为键和值分配独立的内存并拷贝，这样哈希表就不依赖于外部传入的指针生命周期
    new_node->key = (char*)malloc(strlen(key) + 1);
    new_node->value = (char*)malloc(strlen(value) + 1);

    if(!new_node->key || !new_node->value)
    {
        free(new_node->key);
        free(new_node->value);
        free(new_node);
        return false;
    }

    strcpy(new_node->key, key);
    strcpy(new_node->value, value);

    // 步骤5：将新节点插入到链表的头部
    new_node->next = ht->buckets[index];
    ht->buckets[index] = new_node;

    ht->size++;
    return true;
}

const char* ht_get(const HashTable* ht, const char* key)
{
    /*
    教学案例：
        在 'ht_set' 案例3的状态下查找 "name"
         - 桶4：->[("name", "Bob")] -> [("name", "Amy")] -> NULL
         - 计算哈希得到索引 4
         - 遍历桶4的链表
         - 第一个节点 "mane" != "name"
         - 第二个节点 "name" == "name"
         - 返回 "Amy"
    */
    if(!ht || !key) return NULL;

    size_t index = hash_function(key, ht->capacity);
    Node* current = ht->buckets[index];

    while(current != NULL)
    {
        if(strcmp(current->key, key) == 0)
        {
            return current->value;
        }
        current = current->next;
    }
    // 遍历链表未找到
    return NULL; 
}

bool ht_remove(HashTable* ht, const char* key)
{
    /*
    教学案例：在 'ht_set' 案例3的状态下删除 "mane"
        - 桶4：-> [("mane", "Bob")] -> [("name", "Amy")] -> NULL
        - 计算哈希("mane")得到索引 4
        - 遍历桶4的链表，需要一个"prev"指针来辅助删除
        - 找到 "mane" 时，它是头节点(prev = NULL)
        - 将桶的头指针 'buckets[4]' 指向 "mane" 的下一个节点"name" 
        - 释放 "mane" 的内存
        - 桶4：-> [("name", "Amy")] -> NULL
    */
   if(!ht || !key)   return false;

   size_t index = hash_function(key, ht->capacity);
   Node* current = ht->buckets[index];
   Node* prev = NULL;

   while(current != NULL && strcmp(current->key, key) != 0)
   {
       prev = current;
       current = current->next;
   }
   // 如果 current == NULL, 说明遍历完链表未找到这个键
   if(current == NULL) return false;

   // 情况A：删除的是头节点
   if(prev == NULL)
   {
       ht->buckets[index] = current->next;
   }
   // 情况B：删除的是中间或尾节点
   else
   {
       prev->next = current->next;
   }

   free(current->key);
   free(current->value);
   free(current);

   ht->size--;
   return true;
}

void ht_print(const HashTable* ht)
{
    if(!ht)
    {
        printf("HashTable is NULL\n");
        return;
    }

    printf("--- HashTable (capacity: %zu, size: %zu) ---\n", ht->capacity, ht->size);
    for(size_t i = 0; i < ht->capacity; i++)
    {
        printf("Bucket[%zu]: ", i);
        Node* current = ht->buckets[i];
        if(current == NULL)
        {
            printf("-> NULL\n");
        }
        else
        {
            while(current != NULL)
            {
                printf("-> [K:\"%s\", V: \"%s\"] ", current->key, current->value);
                current = current->next;
            }
            printf(" -> NULL\n");
        }
    }
    puts("----------------------------------\n");
}
