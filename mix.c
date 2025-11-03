#include <stdio.h>
#include <threads.h>   // C11 线程库
#include <stdlib.h>

mtx_t lock;       // 互斥量
int counter = 0;  // 共享资源

int add_thread(void* arg) {
    for (int i = 0; i < 100000; i++) {
        mtx_lock(&lock);    // 加锁（进入关键区）
        counter++;          // 修改共享数据
        mtx_unlock(&lock);  // 解锁（退出关键区）
    }
    return 0;
}

int main(void) {
    thrd_t t1, t2;

    // ✅ 初始化互斥锁（核心函数）
    if (mtx_init(&lock, mtx_plain) != thrd_success) {
        printf("锁初始化失败\n");
        return -1;
    }

    // 创建线程
    thrd_create(&t1, add_thread, NULL);
    thrd_create(&t2, add_thread, NULL);

    // 等待线程结束
    thrd_join(t1, NULL);
    thrd_join(t2, NULL);

    // 销毁互斥锁资源
    mtx_destroy(&lock);

    printf("最终计数值: %d\n", counter); // 期望 200000
    return 0;
}