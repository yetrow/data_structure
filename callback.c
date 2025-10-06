#include <stdio.h>
#include <stdlib.h> // 包含 NULL

// 1. 定义 add 函数，并简化参数类型为 int
//    现在 add 函数直接接受两个 int 参数，更符合其功能。
int add(int a, int b) {
    return a + b;
}

// 2. 让 func 函数实际使用回调函数，并简化函数指针参数类型
//    func 函数现在会调用传入的 callback 函数。
// 4. 错误处理和边缘情况：添加对 NULL 回调函数的检查
//    防止在回调函数为 NULL 时程序崩溃。
int func(int a, int b, int (*callback)(int, int)) {
    if (callback == NULL) {
        // 最简化的错误处理
        return 0;
    }
    return callback(a, b);
}

int main(void) {
    int c = func(2, 3, add);
    printf("%d\n", c);

    return 0;
}