/* 归并排序（Merge Sort）是一种分治法（Divide and Conquer）的排序算法。
    它将数组分成两半，对每部分递归地应用归并排序，然后将两个有序的部分合并成一个整体有序的数组。


    步骤：
    1.分解：将当前的数组分成两半，如果数组大小为1或0，则不需要进一步分解。
    2.递归排序：递归地对这两半进行归并排序，直到子数组的大小减少到1，这时每个子数组都是排好序的。
    3.合并：将两个排好序的子数组合并成一个单一的、排序好的数组。

    如何合并（合并过程是归并排序的核心）：
    - 使用两个指针分别跟踪两个子数组的开始。
    - 比较两个指针所指向的元素，选择较小的那个放入新数组中，并移动该指针到下一个元素。
    - 重复此过程，直到所有元素都被移动到新数组中。


    时间复杂度：
    在所有情况下都是O(n log n)，其中n是数组的元素数量。这是因为每次合并操作都需要线性时间（O(n)），而分解过程需要对数时间（O(log n)）。
    空间复杂度：
    由于需要额外的存储空间来合并两个子数组，归并排序的空间复杂度为O(n)。

    特点：
    非就地排序。
    稳定。
    适合大规模数据集合的排序，特别是当数据无法全部加载到内存时，归并排序特别有效。


    归并排序是一种非常有效的排序算法，尤其是在处理大数据集时，因为它的时间复杂度相对稳定，并且具有很好的并行化特性。
    然而，由于它的空间复杂度较高，所以在空间敏感的应用场景中可能需要考虑其他排序算法。

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

void merge(int A[], int temp[], int left, int mid, int right)
{
    int i = left, j = mid + 1, k = left;
    while (i <= mid && j <= right)
    {
        if (A[i] < A[j])
        {
            temp[k++] = A[i++];
        }
        else
        {
            temp[k++] = A[j++];
        }
    }
    // 如果左侧部分还有剩余，复制到临时数组
    while (i <= mid)
    {
        temp[k++] = A[i++];
    }
    // 如果右侧部分还有剩余，复制到临时数组
    while (j <= right)
    {
        temp[k++] = A[j++];
    }
    // 将合并后的数据复制回原数组
    for (int i = left; i <= right; i++)
    {
        A[i] = temp[i];
    }
    print_array(A, 10);
}

void merge_sort(int A[], int temp[], int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;

        merge_sort(A, temp, left, mid);      // 递归排序左半部分
        merge_sort(A, temp, mid + 1, right); // 递归排序右半部分

        merge(A, temp, left, mid, right); // 合并两半
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {4, 12, 5, 2, 75, 1, 0, 78, 2, 99};
    int temp[10]; // 用于合并的临时数组

    merge_sort(array, temp, 0, 9);

    return 0;
}
