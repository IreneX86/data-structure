/* 快速排序 的原理是分而治之（divide and conquer），通过递归的方式将数据分解为更小的子序列来解决问题。

    1.选择基准值（Pivot）：从序列中选择一个元素作为基准值，选择方法有多种，比如选择第一个元素、最后一个元素或中位数等。
    2.分区（Partitioning）：重新排列序列，使所有比基准值小的元素都排在基准前面，所有比基准值大的元素都排在基准后面。在这个过程中，基准元素会找到它正确的排序位置。
    3.递归排序：递归地将上述过程应用于基准值左右两边的子序列，直到每个子序列只包含一个元素或为空，这时序列就完全排序了。

    时间复杂度：
    平均:O(nlog(n))
    最坏（即序列已经是升序或降序）:O(n^2)

    空间复杂度：
    因为其递归，故其空间复杂度主要取决于递归调用的深度
    一般为 O(log n)

    优点：
    平均情况下非常高效。
    排序过程不需要额外的存储空间（原地排序）。
    适用于大数据集。

    缺点：
    最坏情况下的时间复杂度较高。
    对于小数据集或几乎已经排序的数据，其性能可能不如其他排序算法（如插入排序）。
    高度递归的实现可能导致栈溢出。
    不稳定。

    由于其优秀的平均性能，快速排序仍然是最受欢迎和广泛使用的排序算法之一。
*/

#include <stdio.h>

int partition(int A[], int i, int j)
{
    int pivox = A[i];
    while (i < j)
    {
        while (i < j && A[j] >= pivox)
        {
            j--;
        }
        if (i < j)
        {
            A[i] = A[j];
            i++;
        }
        while (i < j && A[i] < pivox)
        {
            i++;
        }
        if (i < j)
        {
            A[j] = A[i];
            j--;
        }
    }
    A[i] = pivox;

    return i;
}

void quick_sort(int A[], int i, int j)
{
    if (i < j)
    {
        int pivox = partition(A, i, j);
        quick_sort(A, i, pivox - 1);
        quick_sort(A, pivox + 1, j);
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {4, 12, 5, 2, 75, 1, 0, 78, 2, 99};
    quick_sort(array, 0, 9);

    return 0;
}
