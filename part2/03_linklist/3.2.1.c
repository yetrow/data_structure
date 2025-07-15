#include<stdio.h>
#include<stdlib.h>

int main(void)
{
    int select,student_no=0,num=0;
    float Msum=0,Esum=0;
    struct student
    {
        char name[20];
        int Math;
        int Eng;
        char no[10];
        struct student* next;
    };

    typedef struct student s_data;
    s_data *ptr;
    s_data *head;
    s_data *new_data;

    head=(s_data*)malloc(sizeof(s_data));
    head->next=NULL;
    ptr=head;

    do{
        printf("[1]添加；[2]离开=>>\n");
        scanf_s("%d",&select);
        if(select!=2)
        {
            printf("姓名 学号 数学成绩 英语成绩：\n");
            new_data=(s_data*)malloc(sizeof(s_data));
            scanf_s("%s %s %d %d", new_data->name, sizeof(new_data->name), new_data->no, sizeof(new_data->no), &new_data->Math, &new_data->Eng);

            ptr->next=new_data;
            new_data->next=NULL;
            ptr=ptr->next;
            num++;
        }
    }while(select!=2);

    ptr=head->next;
    putchar('\n');
    while(ptr!=NULL)
    {
        printf("姓名：%s\t学号：%s\t数学成绩：%d\t英语成绩：%d\n"
        ,ptr->name,ptr->no,ptr->Math,ptr->Eng);
        Msum+=ptr->Math;
        Esum+=ptr->Eng;
        student_no++;
        ptr=ptr->next;
    }


    // // 释放链表内存
    // s_data *current = head->next;
    // s_data *next_node;
    // while (current != NULL) {
    //     next_node = current->next;
    //     free(current);
    //     current = next_node;
    // }
    // free(head); // 释放头节点

    return 0;
}
