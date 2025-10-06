```
---测试Student动态数组---
Array (Size: 3,Capacity: 3):[
  Student:{id: 101,name:"Alice"}
  Student:{id: 102,name:"Bob"}
  Student:{id: 103,name:"Carol"}
添加新学生Dave,触发扩容
Array (Size: 4,Capacity: 6):[
  Student:{id: 101,name:"Alice"}
  Student:{id: 102,name:"Bob"}
  Student:{id: 103,name:"Carol"}
  Student:{id: 104,name:"Dave"}
在索引2处插入新学生Eve
删除索引1的学生Bob
Array (Size: 4,Capacity: 6):[
  Student:{id: 101,name:"Alice"}
  Student:{id: 105,name:"Eve"}
  Student:{id: 103,name:"Carol"}
  Student:{id: 104,name:"Dave"}
读取并更新一个学生信息
找到学生：学号=104,姓名:Dave
姓名更新为David
Array (Size: 4,Capacity: 6):[
  Student:{id: 101,name:"Alice"}
  Student:{id: 105,name:"Eve"}
  Student:{id: 103,name:"Carol"}
  Student:{id: 104,name:"David"}
```



- __`resize_array` 函数__:

  - 该函数使用 `realloc` 重新分配内存。`realloc` 的时间复杂度取决于操作系统如何实现内存管理，但在最坏情况下，如果需要将数据复制到新的内存位置，则为 __O(n)__，其中 n 是数组中的元素数量。

- __`create_array` 函数__:

  - 该函数包含两次 `malloc` 调用和一些基本赋值操作。`malloc` 的时间复杂度通常被认为是 __O(1)__（平均情况），但在某些系统或极端情况下可能更高。因此，`create_array` 的时间复杂度为 __O(1)__。

- __`destroy_array` 函数__:

  - 该函数包含两次 `free` 调用。`free` 的时间复杂度通常被认为是 __O(1)__。因此，`destroy_array` 的时间复杂度为 __O(1)__。

- __`array_append` 函数__:

  - 在大多数情况下，它只是在数组末尾添加一个元素，这是 __O(1)__ 操作。
  - 然而，如果 `arr->size >= arr->capacity`，它会调用 `resize_array` 进行扩容。在扩容的情况下，时间复杂度变为 __O(n)__，其中 n 是数组中的元素数量。
  - 由于扩容操作不经常发生（通常是指数级扩容），因此 `array_append` &#x7684;__&#x5E73;均时间复杂&#x5EA6;__&#x662F; __O(1)__，__最坏时间复杂&#x5EA6;__&#x662F; __O(n)__。

- __`array_read` 函数__:

  - 该函数通过索引直接访问数组元素。这是一个直接的内存地址计算和访问，与数组大小无关。因此，`array_read` 的时间复杂度为 __O(1)__。

- __`array_updata` 函数__:

  - 该函数通过索引直接更新数组元素。这也是一个直接的内存访问操作，与数组大小无关。因此，`array_updata` 的时间复杂度为 __O(1)__。

- __`array_insert` 函数__:

  - 首先，它检查是否需要扩容，这在最坏情况下是 __O(n)__（如果调用 `resize_array`）。
  - 然后，它有一个 `for` 循环，用于将从插入点开始的所有元素向后移动一位。在最坏情况下（在索引 0 处插入），需要移动 `arr->size` 个元素。
  - 因此，`array_insert` 的时间复杂度为 __O(n)__，其中 n 是数组中的元素数量。

- __`array_delete` 函数__:

  - 该函数有一个 `for` 循环，用于将从删除点开始的所有元素向前移动一位。在最坏情况下（删除索引 0 处的元素），需要移动 `arr->size - 1` 个元素。
  - 此外，它还包含一个缩容逻辑，如果满足条件，会调用 `resize_array`。在缩容的情况下，时间复杂度变为 __O(n)__。
  - 因此，`array_delete` 的时间复杂度为 __O(n)__，其中 n 是数组中的元素数量。

- __`print_array` 函数__:

  - 该函数有一个 `for` 循环，从 `i = 0` 遍历到 `arr->size - 1`。它会访问并打印数组中的每一个元素。
  - 因此，`print_array` 的时间复杂度为 __O(n)__，其中 n 是数组中的元素数量。
