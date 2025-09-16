#define _CRT_SECURE_NO_WARNINGS // 忽视vs的一些字符串的sb警告，写在最上边
#include "dynamic_array.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// void print_student_array(const DynamicArray *arr)
// {
//     printf("---学生名单（当前人数:%zu,仓库容量:%zu）---\n", arr->size, arr->capacity);
//     if (arr->size == 0)
//     {
//         printf("名单为空.\n");
//         return;
//     }
//     for (size_t i = 0; i < arr->size; i++)
//     {
//         printf(" 索引[%zu]:学号:%zu,姓名:%s\n", i, arr->data[i].id, arr->data[i].name);
//     }
//     printf("--------------------\n\n");
// }

// 定义我们自己的回调函数
// 1. 这是一个知道如何打印Student的函数
//  它的函数签名必须和函数指针的定义完全匹配
void print_student(const void *data)
{
    // 接收的data是一个void*指针，我们需要将它转换为我们真正的类型
    const Student *ptr = (const Student *)data;
    printf("Student:{id: %d,name:\"%s\"}",ptr->id,ptr->name);
}

int main()
{
    printf("---测试Student动态数组---\n");
    DynamicArray *student_list = create_array(3);
    Student s1 = {101, "Alice"};
    strcpy(s1.name, "Alice");
    Student s2 = {102, "Bob"};
    strcpy(s2.name, "Bob");
    Student s3 = {103, "Carol"};
    strcpy(s3.name, "Carol");

    array_append(student_list, s1);
    array_append(student_list, s2);
    array_append(student_list, s3);
    // print_student_array(student_list);
    print_array(student_list,&print_student);

    // 扩容
    printf("添加新学生Dave,触发扩容\n");
    Student s4 = {104, "Dave"};
    strcpy(s4.name, "Dave");
    array_append(student_list, s4);
    // print_student_array(student_list);
    print_array(student_list,&print_student);
    // 插入
    printf("在索引2处插入新学生Eve\n");
    Student s5 = {105, "Eve"};
    strcpy(s5.name, "Eve");
    array_insert(student_list, 2, s5);
    // print_student_array(student_list);

    // 删除
    printf("删除索引1的学生Bob\n");
    array_delete(student_list, 1);
    // print_student_array(student_list);
    print_array(student_list,&print_student);
    // 读取并更新学生信息
    printf("读取并更新一个学生信息\n");
    Data *student_p = array_read(student_list, 3);
    if (student_p)
    {
        printf("找到学生：学号=%d,姓名:%s\n", student_p->id, student_p->name);
        printf("姓名更新为David\n");
        strcpy(student_p->name, "David");
    }
    // print_student_array(student_list);
    print_array(student_list,&print_student);    
    destroy_array(student_list);

    return 0;
}