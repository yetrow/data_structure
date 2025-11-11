#include "BST.h"
#include <stdio.h>


int compare_int(const void* a, const void* b)
{
    int int_a = *(const int*)a;
    int int_b = *(const int*)b;

    if(int_a < int_b)   return -1;
    if(int_a > int_b)   return 1;

    return 0;
}
// 假如我们写一个比较函数，比较类型是Student的id编号排序
// int compare_student_id(const void* a, const void* b)
// {
//     const Student* student_a = (Student*)a;
//     const Student* student_b = (Student*)b;

//     if(student_a->id < student_b->id)   return -1;
//     if(student_a->id > student_b->id)   return 1;

//     return 0;
// }