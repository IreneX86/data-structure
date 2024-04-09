/*插入排序 是一种简单直观的排序算法

    1. 从第一个元素开始：这个元素可以认为已经被排序；
    2. 取出下一个元素：在已经排序的元素序列中从后向前扫描；
    3. 比较：如果该元素（已排序）大于新元素，将该元素移到下一位置；
    4. 重复步骤3：直到找到已排序的元素小于或等于新元素的位置；
    5. 插入新元素：将新元素插入到该位置后；
    6. 重复步骤2~5：直到排序完成。

    时间复杂度:
    最佳情况：O(n)，当输入的数据已经是升序排列时。
    平均情况：O(n^2)，对于随机排列的数据集。
    最差情况：O(n^2)，当输入的数据是降序排列时。

    空间复杂度:
    O(1)，因为它是在原地排序，不需要额外的存储空间。

    优点：
    稳定，即相同的元素在排序后保持其原有顺序。
    在线性：插入排序可以在接收到新元素时进行排序。
    适用性：对于部分已排序或元素数量较少的数据集效率较高。

    插入排序虽然在最坏情况下的时间复杂度比较高，但对于小规模数据或基本有序的数据集，它是非常高效的。
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

void insert_sort(int A[], int length)
{
    for (int i = 1; i < length; i++)
    {
        for (int j = 0; j < i; j++)
        {
            if (A[i] < A[j])
            {
                int temp = A[i];
                for (int k = i - 1; k >= j; k--)
                {
                    A[k + 1] = A[k];
                }
                A[j] = temp;
            }
        }
        print_array(A, length);
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {4, 12, 5, 2, 75, 1, 0, 78, 2, 99};
    print_array(array, 10);
    insert_sort(array, 10);

    return 0;
}