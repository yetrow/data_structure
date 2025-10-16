#define _CRT_SECURE_NO_WARNINGS
#include "DoublyLinkedList.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char* name;
} Employee;

char* protable_strdup(const char* str)
{
    if(!str)    return NULL;
    size_t len = strlen(str);
    char* new_str = (char*)malloc(len + 1);
    
    if(new_str)
    {
        memcpy(new_str, str, len);
    }

    return new_str;
}

void fee_employee(void* data)
{
    Employee* emp = (Employee*)data;
    
    if(emp)
    {
        printf("Freeing employee ID: %d, name: %s\n", emp->id, emp->name);
        free(emp->name);
        free(emp);
    }
}

int compare_employee_by_id(const void* data1, const void* data2)
{
    Employee* emp1 = (Employee*)data1;
    Employee* emp2 = (Employee*)data2;

    return emp1->id - emp2->id;
}

void print_employee_action(void* data, void* context)
{
    const Employee* emp = (const Employee*)data;

    if(!emp)
    {
        printf("NULL employee\n");
        return ;
    }

    printf("Employee ID: %d, name: %s\n", emp->id, emp->name);
}

int main(void)
{
    printf("");
}