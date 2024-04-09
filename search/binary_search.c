

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
    int array[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29};
    int target_index_iter = binary_search_iteration(19, array, 10);
    printf("using iteration, the index of number 19 is: %d\n", target_index_iter);
    int target_index_recur = binary_search_recursion(19, array, 0, 9);
    printf("using recursion, the index of number 19 is: %d\n", target_index_recur);
    return 0;
}