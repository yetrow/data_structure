#include <stdio.h>
#include "dynamic_array.h"

// void print_array(DynamicArray *arr)
// {
//     printf("Array (Size: %zu, Capacity: %zu) :[ ", arr->size, arr->capacity);

//     for (size_t i = 0; i < arr->size; i++)
//     {
//         printf("%d ", arr->data[i]);
//     }
//     printf(" ]\n");
// }

int main(void)
{   
    // === 1. 初始化数组
    printf("1. 初始化数组\n");
    DynamicArray *my_array = create_array(5);

    array_append(my_array, 0);
    array_append(my_array, 2);
    array_append(my_array, 3);
    array_append(my_array, 4);
    array_append(my_array, 5);

    print_array(my_array);
    printf("初始化数组完成！当前size和capacity相等，下一次添加触发扩容\n");
    array_append(my_array, 6);
    print_array(my_array);
    printf("\n");

    // === 2. 读取
    printf("2. 读取\n");
    size_t read_index = 2;
    Data* value_ptr = array_read(my_array, read_index);
    if(value_ptr)
    {
        printf("读取索引 %zu \n", read_index);
        printf("读取成功！值为：%d\n", *value_ptr);
    }
    printf("\n");
    
    // === 3. 更新
    printf("3. 更新\n");
    size_t update_index = 3;
    Data new_value = 999;
    printf("将索引 %zu 的值从 %d 更新为 %d \n", update_index, *array_read(my_array, update_index), new_value);

    array_updata(my_array, update_index, new_value);
    print_array(my_array);

    // === 4. 插入
    printf("\n4. 插入测试\n");
    printf("在索引 1 处插入 100\n");
    array_insert(my_array, 1, 100);
    print_array(my_array);

    printf("在索引 0 处插入 50 (头部插入)\n");
    array_insert(my_array, 0, 50);
    print_array(my_array);

    printf("在索引 %zu 处插入 200 (尾部插入)\n", my_array->size);
    array_insert(my_array, my_array->size, 200);
    print_array(my_array);

    // === 5. 删除与缩容测试
    printf("\n5. 删除与缩容测试\n");
    printf("先追加一些元素使容量扩大...\n");
    for(int i = 0; i < 15; i++) {
        array_append(my_array, i + 100);
    }
    print_array(my_array); // 此时 size 应该较大，capacity 应该超过了 INITIAL_CAPACITY

    printf("删除索引 2 的元素\n");
    array_delete(my_array, 2);
    print_array(my_array);

    printf("持续删除元素以触发缩容测试\n");
    while (my_array->size > 1) {
        array_delete(my_array, 0);
    }
    print_array(my_array);

    // === 6. 销毁
    printf("\n6. 销毁数组\n");
    destroy_array(my_array);
    printf("数组已销毁。\n");

    return 0;
}
