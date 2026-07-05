#include <stdio.h>

void select_sort(int a[], int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_index = i;

        for (int j = i + 1; j < n; j++) {
            if(a[j] < a[min_index]) {
                min_index = j;
            }
        }

        int temp = a[i];
        a[i] = a[min_index];
        a[min_index] = temp;
    }
}

// 外层循环 for (i = 0; i < n - 1; i++)
// 作用：确定当前轮次要放最小值的位置

// 轮次	i 指向哪里	含义
// 第1轮	i = 0	从整个数组 [0 ~ n-1] 中找最小，放到 a[0]
// 第2轮	i = 1	从剩余部分 [1 ~ n-1] 中找最小，放到 a[1]
// ...	...	...
// 第 n-1 轮	i = n-2	从最后两个 [n-2 ~ n-1] 中找最小，放到 a[n-2]
// 为什么 i < n-1？因为最后一个元素 a[n-1] 前面 n-1 个都排好了，它自然就在正确位置，不用再比。



// 内层循环 for (j = i + 1; j < n; j++)
// 作用：在待排序区间 [i+1 ~ n-1] 里扫描，找真正的最小值的下标

// 初始: min_index = i
//       ↓
//     j从i+1开始往后扫
//       ↓
//     如果 a[j] < a[min_index]，说明找到更小的
//       ↓
//     更新 min_index = j
//       ↓
// 扫完后，min_index 就是 [i ~ n-1] 中最小值的位置

int main()
{
    int a[] = {5, 8, 7, 1, 3, 0};
    int size = sizeof(a)/sizeof(a[0]);

    select_sort(a,size);

    for(int i = 0; i < size; i++){
        printf("%d ", a[i]);
    }

    return 0;
}