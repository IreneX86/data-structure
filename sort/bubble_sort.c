#include <stdio.h>

void print_array(int A[], int length)
{
    for (int i = 0; i < length; i++)
    {
        printf("%d ", A[i]);
    }
    printf("\n");
}

void bubble_sort(int A[], int length)
{
    for (int i = 0; i < length - 1; i++)
    {
        for (int j = 0; j < length - 1 - i; j++)
        {
            if (A[j] > A[j + 1])
            {
                int temp = A[j];
                A[j] = A[j + 1];
                A[j + 1] = temp;
            }
        }
        print_array(A, length);
    }
}

int main(int argc, char *argv[])
{
    int array[10] = {4, 12, 5, 2, 75, 1, 0, 78, 2, 99};
    bubble_sort(array, 10);

    return 0;
}