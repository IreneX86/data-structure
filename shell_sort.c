#include <stdio.h>

void print_array(int A[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void shell_sort(int A[], int length, int step)
{
    for (int i = 0; i < length; i++)
    {
        for (int j = i + step; j < length; j += step)
        {
            for (int k = i; k < j; k += step)
            {
                if (A[j] < A[k])
                {
                    int temp = A[j];
                    for (int l = j - step; l >= k; l -= step)
                    {
                        A[l + step] = A[l];
                    }
                    A[k] = temp;
                }
            }
        }
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {4, 12, 5, 2, 75, 1, 0, 78, 2, 99};
    int steps[3] = {5, 3, 1};
    for (int i = 0; i < 3; i++)
    {
        shell_sort(array, 10, steps[i]);
        print_array(array, 10);
    }

    return 0;
}