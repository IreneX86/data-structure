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