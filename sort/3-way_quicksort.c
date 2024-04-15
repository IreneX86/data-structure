/*  3-Way QuickSort (Dutch National Flag)
    三路快排(又称荷兰旗问题)

    将数组分为三个部分：小于主元、等于主元、大于主元。
    在处理含有许多重复元素的数组时非常有效，可以减少不必要的比较和交换。

    Author: IreneX86
    E-mail: irene.127.0.0.1@gmail.com

*/

#include <stdio.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// 分区函数，将数组分为三部分
void partition(int A[], int left, int right, int *i, int *j)
{

    *i = left;        // 从左边开始扫描(Start scanning from the left)
    int p = A[right]; // 选取最右元素作为主元(pivot) (Choose the right-most element as the pivot)
    *j = right;       // 从右边开始扫描(Start scanning from the right)
    int lt = left;    // Pointer for the end of the less-than pivot region
    int gt = right;   // Pointer for the start of the greater-than pivot region

    while (*i <= gt) // 当i指针未超过gt指针时处理元素
    {
        if (A[*i] < p) // 当前元素小于主元
        {
            swap(&A[*i], &A[lt]); // 将其交换到小于区
            lt++;                 // 扩大小于区
            (*i)++;               // 向前移动索引
        }
        else if (A[*i] > p) // 当前元素大于主元
        {
            swap(&A[*i], &A[gt]); // 将其交换到大于区
            gt--;                 // 缩小大于区
        }
        else // 当前元素等于主元
        {
            (*i)++; // 直接向前移动索引
        }
    }
    *i = lt; // 分区后，lt为等于区的开始 ('lt' points to the start of elements equal to pivot)
    *j = gt; // gt为等于区的结束 ('gt' points to the end of elements equal to pivot)
}

// 三路快速排序函数
void quicksort_3way(int A[], int left, int right)
{
    if (left >= right) // 基本情况：如果区域内只有0个或1个元素，则不做处理
        return;

    int i, j;
    partition(A, left, right, &i, &j); // 将数组分为三部分
    quicksort_3way(A, left, i - 1);    // 递归排序小于区
    quicksort_3way(A, j + 1, right);   // 递归排序大于区
}

// 输出数组
void print_arr(int A[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int arr[] = {0, 1, 2, 1, 1, 2, 0, 2, 1, 0};
    int size = sizeof(arr) / sizeof(int);

    print_arr(arr, size);             // 输出原始数组
    quicksort_3way(arr, 0, size - 1); // 使用三路快排
    print_arr(arr, size);             // 输出排序后的数组

    return 0;
}