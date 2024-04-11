/*  循环队列(circular queue)

    用一个环型的数组(array)来表示。
    初始状态：front==rear;

    牺牲掉队列的一个空间，用来标识队满or空。

    操作：1.初始化队列
         2.入队
         3.出队
         4.判断队空

    Author: IreneX86
    Email: Irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 10

typedef struct Queue
{
    int data[MAXSIZE]; // 用数组来存储循环队列
    int front;         // 数组首部索引(front index)
    int rear;          // 数组尾部索引(rear index)
} queue_t;

queue_t *init_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->front = queue->rear = 0; // 环形数组
    return queue;
}

int is_full(queue_t *queue)
{
    if ((queue->rear + 1) % MAXSIZE == queue->front)
        return 1;
    else
        return 0;
}

int is_empty(queue_t *queue)
{
    if (queue->front == queue->rear)
        return 1;
    else
        return 0;
}

int en_queue(queue_t *queue, int data)
{
    if (is_full(queue))
        return 0;
    else
    {
        queue->data[queue->rear] = data;
        queue->rear = (queue->rear + 1) % MAXSIZE;
        return 1;
    }
}

int de_queue(queue_t *queue)
{
    if (is_empty(queue))
        return -1;
    else
    {
        int data = queue->data[queue->front];
        queue->front = (queue->front + 1) % MAXSIZE;
        return data;
    }
}

void print_queue(queue_t *queue)
{
    int length = (queue->rear - queue->front + MAXSIZE) % MAXSIZE;
    int index = queue->front;
    for (int i = 0; i < length; i++)
    {
        printf("%d->", queue->data[index]);
        index = (index + 1) % MAXSIZE;
    }
    printf("HEAD\n");
}

int main(int argc, char *argv[])
{
    queue_t *Q = init_queue();
    en_queue(Q, 1);
    en_queue(Q, 4);
    en_queue(Q, 9);
    en_queue(Q, 6);
    en_queue(Q, 2);
    en_queue(Q, 5);
    en_queue(Q, 0);
    print_queue(Q);

    printf("de_queue data = %d\n", de_queue(Q));
    printf("de_queue data = %d\n", de_queue(Q));
    print_queue(Q);

    return 0;
}