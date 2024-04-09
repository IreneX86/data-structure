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
