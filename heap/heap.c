/* 最大堆

    1.初始化堆：
    initHeap 函数初始化一个空的最大堆。

    2.插入元素：
    insert 函数将新元素插入堆末尾，然后通过 bubbleUp 操作调整堆结构。

    3.删除堆顶元素：
    extractMax 函数删除堆顶元素，并用堆末尾的元素填补堆顶，通过 bubbleDown 操作调整堆结构。

    4.上浮和下沉操作：
    bubbleUp 和 bubbleDown 函数分别用于在插入和删除操作后调整堆，以维护堆的性质。

    5.打印堆：
    printHeap 函数用于打印堆中的元素。


    堆是一种高效的数据结构，广泛应用于优先队列、排序算法和图算法中。

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX_HEAP_SIZE 100

typedef struct
{
    int data[MAX_HEAP_SIZE];
    int size;
} max_heap_t;

// 初始化堆
void init_heap(max_heap_t *heap)
{
    heap->size = 0;
}

// 上浮
void bubble_up(max_heap_t *heap, int index)
{
    while (index > 0)
    {
        int parent = (index - 1) / 2;
        if (heap->data[index] > heap->data[parent])
        {
            // 交换
            int temp = heap->data[index];
            heap->data[index] = heap->data[parent];
            heap->data[parent] = temp;
            index = parent;
        }
        else
        {
            break;
        }
    }
}

// 插入
void insert(max_heap_t *heap, int value)
{
    if (heap->size >= MAX_HEAP_SIZE)
    {
        printf("Heap is full.\n");
        return;
    }

    heap->data[heap->size] = value;
    bubble_up(heap, heap->size);
    heap->size++;
}

// 下沉
void bubbleDown(max_heap_t *heap, int index)
{
    int left_child, right_child, max_index, temp;
    while (index < heap->size)
    {
        left_child = 2 * index + 1;
        right_child = 2 * index + 2;
        max_index = index;

        if (left_child < heap->size && heap->data[left_child] > heap->data[max_index])
        {
            max_index = left_child;
        }
        if (right_child < heap->size && heap->data[right_child] > heap->data[max_index])
        {
            max_index = right_child;
        }

        if (max_index != index)
        {
            // 交换
            temp = heap->data[index];
            heap->data[index] = heap->data[max_index];
            heap->data[max_index] = temp;
            index = max_index;
        }
        else
        {
            break;
        }
    }
}

// 删除并返回堆顶元素(最大元素)
int extract_max(max_heap_t *heap)
{
    if (heap->size == 0)
    {
        printf("Heap is empty.\n");
        return -1;
    }
    int max = heap->data[0];
    heap->data[0] = heap->data[heap->size - 1];
    heap->size--;
    bubbleDown(heap, 0);
    return max;
}

// 打印堆
void print_heap(max_heap_t *heap)
{
    for (int i = 0; i < heap->size; i++)
    {
        printf("%d ", heap->data[i]);
    }
    printf("\n");
}

int main()
{
    max_heap_t heap;
    init_heap(&heap);

    insert(&heap, 10);
    insert(&heap, 20);
    insert(&heap, 15);
    insert(&heap, 30);
    insert(&heap, 40);

    printf("Max Heap: ");
    print_heap(&heap);

    printf("Extracted max: %d\n", extract_max(&heap));
    printf("Max Heap after extraction: ");
    print_heap(&heap);

    return 0;
}