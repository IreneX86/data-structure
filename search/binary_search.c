/*  二分查找 是一种在有序数组中查找特定元素的高效算法


    时间复杂度:
    迭代和递归均为O(log n)，其中n是数组中元素的数量。
    这是因为在每一步查找中，算法都将搜索范围缩小为前一次范围的一半，因此操作次数与数组长度的对数成正比。

    空间复杂度:
    迭代:O(1)，因为它仅使用常量额外空间。
    递归:O(log n)，这主要是由于递归调用时栈空间的使用。在最坏情况下，递归调用会达到数组长度的对数次，每次递归调用都需要额外的栈空间。

    因此，尽管迭代和递归实现的二分查找算法在时间复杂度上是相同的，它们在空间复杂度上有所不同。在实际应用中，迭代实现通常更受欢迎，因为它不涉及额外的栈空间开销，更加节省空间。


    优点：
    1.高效：二分查找的时间复杂度为 O(log n)，比线性搜索的 O(n) 要快得多，特别是对于大型数据集。
    2.少量比较：与线性搜索相比，二分查找需要更少的比较次数，因为它每次比较后都会排除一半的搜索空间。
    3.可用于无限集合：二分查找可以应用于概念上无限的数据集，如在实时生成的数据或者按需计算的数据中查找。
    4.确定性和可预测性：二分查找的行为很容易预测和分析，使得性能调优和错误诊断更加直接。

    缺点

    1.仅适用于有序数组：二分查找只能在预先排序的数组或列表中使用。如果数据未排序，则必须先进行排序，这可能会增加额外的计算成本。
    2.对于动态或频繁变动的数据集效率较低：如果数据集频繁变动（添加、删除、修改操作），维持数据的有序状态可能会非常耗时和复杂。
    3.递归实现可能导致栈溢出：递归版本的二分查找可能在极端情况下导致栈溢出，尤其是在处理非常大的数据集时。
    4.不适用于链表：在链表上进行二分查找效率较低，因为链表不支持随机访问，获取链表中间元素的时间复杂度是 O(n)，这会抵消二分查找带来的效率优势。

    虽然二分查找在处理大型有序数据集时非常高效，但在需要频繁更新的数据集或者数据结构不支持快速随机访问的情况下，可能不是最佳选择。
*/

#include <stdio.h>

// 迭代
int binary_search_iteration(int target, int A[], int length)
{
    int start = 0;
    int end = length - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (A[mid] < target)
        {
            start = mid + 1; // 在右半部分查找
        }
        else if (A[mid] > target)
        {
            end = mid - 1; // 在左半部分查找
        }
        else
        {
            return mid;
        }
    }
    return -1; // 未找到元素，返回-1
}

// 递归
int binary_search_recursion(int target, int A[], int start, int end)
{
    if (start > end)
    {
        return -1; // 如果起始位置大于终止位置，表示未找到元素
    }
    int mid = (start + end) / 2;
    if (A[mid] == target)
    {
        return mid; // 找到元素，返回位置
    }
    else if (A[mid] < target)
    {
        return binary_search_recursion(target, A, mid + 1, end); // 在右半部分递归查找
    }
    else
    {
        return binary_search_recursion(target, A, start, mid - 1); // 在左半部分递归查找
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29}; // 此数组必须有序。若无序，先排序再二分查找。
    int target_index_iter = binary_search_iteration(19, array, 10);
    printf("using iteration, the index of number 19 is: %d\n", target_index_iter);
    int target_index_recur = binary_search_recursion(19, array, 0, 9);
    printf("using recursion, the index of number 19 is: %d\n", target_index_recur);
    return 0;
}
