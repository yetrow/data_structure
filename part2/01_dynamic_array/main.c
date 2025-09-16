#include<stdio.h>
#include "dynamic_array.h"

int main(void)
{
    DynamicArray* my_array=create_array(5);

    array_append(my_array,0);
    array_append(my_array,2);
    array_append(my_array,3);
    array_append(my_array,4);
    array_append(my_array,5);

    print_array(my_array);

    array_delete(my_array,1);

    print_array(my_array);

    return 0;
}