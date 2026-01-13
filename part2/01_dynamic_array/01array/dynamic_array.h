#pragma once
#include <stddef.h>

typedef int Data;

// typedef Student Data; // typedef int Data;
// 定义我们自己的动态数组的结构体
// [{stu1.id=1, stu1.name="frank"}, {}, ...]

typedef struct
{
    Data* data; // 指向存储数据的连续内存块；指向一个数组的首地址
    // int* data; 说白了，我们可以放很多int类型的数据，因为是指向一个连续不断的内存空间
    size_t size;
    size_t capacity;
} DynamicArray;
// 动态数组三要素：Data;size;capacity

// 创建并初始化一个动态数组
DynamicArray* create_array(size_t initial_capcity);

// 销毁数组，释放内存
void destroy_array(DynamicArray* arr);

// 在末尾追加元素
void array_append(DynamicArray* arr, Data value);

// 读取指定的索引元素
// 返回一个指针，以便能够检查是否成功如果索引无效，返回NULL
Data *array_read(DynamicArray* arr, size_t index);

// 更新指定索引元素
// 返回0成功，返回-1失败
int array_updata(DynamicArray* arr, size_t index, Data value);

int array_insert(DynamicArray* arr, size_t index, Data value);

// 删除指定索引的元素
int array_delete(DynamicArray* arr, size_t index);


void print_array(DynamicArray* arr);
