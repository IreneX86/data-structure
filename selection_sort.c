/*  选择排序
    1. 初始状态：无序区为整个数组，有序区为空。
    2. 第一次遍历：从无序区中找到最小（或最大）的元素，然后将其与无序区的第一个元素交换位置，此时第一个元素成为有序区，其余为无序区。
    3. 后续遍历：从剩余的无序区中继续找到最小（或最大）的元素，将其与无序区的第一个元素交换，使得有序区逐步增长，无序区逐步减少。
    4. 重复过程：重复上述过程，直到无序区的元素数量为0，整个数组变成有序区。

    时间复杂度：O(n^2)
    空间复杂度：O(1)
    不稳定

    优点：
    简单直观，实现容易。
    不需要额外的存储空间，是原地排序。
    缺点：
    时间复杂度较高，不适合数据量大的情况。
    不稳定，可能会改变相等元素的原始顺序。

    选择排序适合于元素数量较少的情况。由于其固定的时间复杂度，不建议在数据量大的情况下使用。
*/

#include <stdio.h>

void print_array(int A[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void selection_sort(int A[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < length; j++)
        {
            if (A[j] < A[min])
            {
                min = j;
            }
        }

        print_array(A, length);

        int temp = A[i];
        A[i] = A[min];
        A[min] = temp;
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {4, 12, 5, 2, 75, 1, 0, 78, 2, 99};
    selection_sort(array, 10);

    return 0;
}