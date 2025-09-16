#include <stdio.h>
#include <stdlib.h>
#include "dynamic_array.h"
#define INITIAL_CAPACITY 10

// 内部辅助函数(加上static)：当容量不足的时候进行扩容
static int resize_array(DynamicArray *arr, size_t new_capacity)
{
    Data *new_data = realloc(arr->data, new_capacity * sizeof(Data));
    if (!new_data)
    { // realloc失败，内存不足
        return -1;
    }
    // realloc成功后，才会用新的地址更新结构体
    arr->data = new_data;
    arr->capacity = new_capacity;
    return 0;
}

// 创建并初始化一个动态数组
DynamicArray *create_array(size_t initial_capcity)
{
    if (initial_capcity == 0)
        initial_capcity = INITIAL_CAPACITY;
    DynamicArray *arr = (DynamicArray *)malloc(sizeof(DynamicArray));

    if (!arr)
        return NULL;
    arr->data = (Data *)malloc(initial_capcity * sizeof(Data));
    // arr作为结构体变量，它有三个成员，在这三个成员中，最重要的是Data* data;
    // data指向一个新的连续不断的内存空间
    // 而整个空间，现在被我们指向的是一个capcity=10的数组
    if (!arr->data)
    {
        free(arr);
        return NULL;
    }
    arr->size = 0;
    arr->capacity = initial_capcity;
    return arr;
}

// 销毁数组，释放内存
void destroy_array(DynamicArray *arr)
{
    if (arr)
    {
        free(arr->data);
        free(arr);
    }
}

// 在末尾追加元素
void array_append(DynamicArray *arr, Data value)
{
    // 检查是否扩容
    if (arr->size >= arr->capacity)
    {
        size_t new_capacity = arr->capacity * 2;
        if (resize_array(arr, new_capacity) != 0)
        {
            // 扩容失败，无法追加
            return;
        }
    }
    arr->data[arr->size] = value;
    arr->size++;
}

// 读取指定的索引元素
// 返回一个指针，如果索引无效，返回NULL
Data *array_read(DynamicArray *arr, size_t index)
{
    if (index >= arr->size)
        return NULL;
    // address = base_address + index * sizeof(element)

    return &(arr->data[index]);
}

// 更新指定索引元素
// 返回0成功，返回-1失败
int array_updata(DynamicArray *arr, size_t index, Data value)
{
    if (index >= arr->size)
        return -1;

    arr->data[index] = value;
    return 0;
}

int array_insert(DynamicArray *arr, size_t index, Data value)
{
    if (index > arr->size)
        return -1; // 可以在末尾插入，因此是大于size

    if (arr->size >= arr->capacity)
    {
        if (resize_array(arr, arr->capacity * 2) != 0)
        {
            return -1;
        }
    }

    for (size_t i = arr->size; i > index; --i)
    {
        arr->data[i] = arr->data[i - 1];
    }

    arr->data[index] = value;

    arr->size++;
    return 0;
}

// 删除指定索引的元素
int array_delete(DynamicArray *arr, size_t index)
{
    if (index >= arr->size)
        return -1;

    for (size_t i = index; i < arr->size - 1; ++i)
    {
        arr->data[i] = arr->data[i + 1];
    }
    arr->size--;

    if (arr->size > 0 && arr->size <= arr->capacity / 4 && arr->capacity > INITIAL_CAPACITY)
    {
        size_t new_capacity = arr->capacity / 2;

        if (new_capacity < arr->size)
            new_capacity = INITIAL_CAPACITY;

        if (new_capacity < INITIAL_CAPACITY)
            new_capacity = INITIAL_CAPACITY;

        printf("\n-----[缩容警告！]Size[%zu]<=Capacity/4[%zu].准备缩容值 [%zu]\n", arr->size, arr->capacity / 4, new_capacity);

        resize_array(arr, new_capacity);
    }

    return 0;
}
// 万能打印函数(选学，这不是数据结构的重点，而是c语言课程的内容)
//print_array第二个参数，要求传递一个指向函数的指针，这个传递的函数必须满足条件是参数必须是const void
void print_array(const DynamicArray *arr, void (*print_func)(const void *data))
{
    if (!print_func)
    {
        printf("错误：未提供有效的打印函数\n");
        return;
    }

    printf("Array (Size: %zu,Capacity: %zu):[\n", arr->size, arr->capacity);
    for (size_t i = 0; i < arr->size; i++)
    {
        printf("  ");
        // 关键是调用外部传入函数指针打印每一个元素
        // 需要传递每个元素的地址&arr->data[i]
        // 因为print_func接受的一个void* 指针
        print_func(&arr->data[i]);
        printf("\n");
    }
}
