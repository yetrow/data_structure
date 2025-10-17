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

// 跨平台字符串处理拷贝问题
char* protable_strdup(const char* str)
{
    if(!str)    return NULL;
    size_t len = strlen(str);
    char* new_str = (char*)malloc(len + 1);
    
    if(new_str)
    {
        strcpy(new_str, str);
    }

    return new_str;
}

void free_employee(void* data)
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

// context is not used here, but you can use it if needed.
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
    printf("--- Architecture of Doubly Linked List ---\n");

    // 1. Create a new doubly linked list with a memory pool
    printf("1.创建一个带有10个节点内存池的list\n");

    DoublyLinkedList* em_list = List_Create(10, free_employee);

    if(!em_list)
    {
        fprintf(stderr, "Failed to create list\n");
        return 1;
    }
    printf("List created successfully. Initial size: %zu\n", List_GetSize(em_list));


    // 2. Add employees to the list
    printf("\n2.向list中添加员工\n");

    for(int i = 0; i < 5; i++)
    {
        Employee* emp = (Employee*)malloc(sizeof(Employee));
        if(emp == NULL)
        {
            fprintf(stderr, "Memory allocation failed for employee.\n");
            continue;
        }
        emp->id = 101 + i;
        char buffer[50];
        sprintf(buffer, "Employee %d", emp->id);
        emp->name = protable_strdup(buffer);
        if(emp->name == NULL)
        {
            fprintf(stderr, "Memory allocation failed for employee name.\n");
            free(emp);
            continue;
        }
        List_Append(em_list, emp);
    }



    // 3. Print the list
    printf("\n3.打印employees的list\n");

    List_ForEach(em_list, print_employee_action, NULL);
    printf("Current list size: %zu\n", List_GetSize(em_list));



    // 4. Find an employee by ID
    printf("\n4.找到ID为103的员工\n ");

    Employee search_key = {103, NULL};
    DListNode* found_node = List_Find(em_list, &search_key, compare_employee_by_id);

    if(found_node)
    {
        Employee* found_emp = (Employee*)List_GetData(found_node);
        printf("Found employee: ID = %d, name = %s\n", found_emp->id, found_emp->name);
    }
    else
    {
        printf("Employee with ID = %d not found\n", search_key.id);
    }



    // 5. Delete an employee from the list
    if(found_node)
    {
        printf("\n5.删除ID为103的员工\n");

        List_DeleteNode(em_list, found_node);
        printf("Employee with ID = %d deleted. Current list size: %zu\n", search_key.id, List_GetSize(em_list));
    }

    printf("\n --- List after deletion --- \n");
    List_ForEach(em_list, print_employee_action, NULL);



    // 6. insert value -> head node
    printf("\n6.在头部插入一个员工\n");
    Employee* ceo = (Employee*)malloc(sizeof(Employee));
    
    if(ceo != NULL)
    {
        ceo->id = 99;
        ceo->name = protable_strdup("CEO");
        if(ceo->name == NULL)
        {
            fprintf(stderr, "Memory allocation failed for CEO name.\n");
            free(ceo);
            // ceo = NULL;
        }
        else{
            List_Prepend(em_list, ceo);
            printf("Prepended employee with ID %d, Name: %s\n", ceo->id, ceo->name);
            printf("\n--- Final list contents ---\n");
            List_ForEach(em_list, print_employee_action, NULL);
            printf("Final list size: %zu\n", List_GetSize(em_list));
        }
    }
    else
    {
        fprintf(stderr, "Memory allocation failed for CEO.\n");
    }



    // 7. Destroy the list
    printf("\n7.释放list\n");

    List_Destroy(&em_list);
    printf("List destroyed. The pointer em_list is now NULL: %s\n", em_list == NULL ? "true" : "false");

  

    return 0;
}
