#pragma once 
#include<stddef.h>

typedef int Data;

//定义动态数组的结构体
typedef struct {
    Data* data;     //指向存储数据的连续内存块；指向一个数组的首地址 
    size_t size;
    size_t capacity;
}DynamicArray; 

//创建并初始化一个动态数组
DynamicArray* create_array(size_t initial_capcity);

//销毁数组，释放内存
void destroy_array(DynamicArray* arr);

//在末尾追加元素
void array_append(DynamicArray* arr,Data value);

//读取指定的索引元素
//返回一个指针，如果索引无效，返回NULL
Data* array_read(DynamicArray* arr,size_t index);

//更新指定索引元素
//返回0成功，返回-1失败
int array_updata(DynamicArray* arr,size_t index,Data value);

int array_insert(DynamicArray* arr,size_t index,Data value);

//删除指定索引的元素
int array_delete(DynamicArray* arr,size_t index);

void print_array(DynamicArray* arr);