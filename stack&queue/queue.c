/* 队列(queue) 是一种线性表。此处使用“双指针循环链表”来构造队列。

    特点：先进先出。(First In First Out)

    操作：1.初始化队列
         2.入队
         3.出队
         4.判断队空

    Author: IreneX86
    Email: Irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node // 双指针循环链表
{
    int data;
    struct Node *next;
    struct Node *pre;
} node_t;

int is_empty(node_t *head_node);

// 初始化队列，返回头节点（头节点用于存储队列信息，头节点的下一个节点才是队列的第一个节点）
node_t *init_queue() // 双指针循环链表
{
    node_t *head_node = (node_t *)malloc(sizeof(node_t));
    head_node->data = 0; // 头节点的data用来记录队列中元素个数（而不是作为一个节点的数值）
    head_node->pre = head_node;
    head_node->next = head_node;
    return head_node;
}

// 入队(加到双指针循环链表末尾)
void en_queue(node_t *head_node, int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = head_node;
    node->pre = head_node->pre;
    head_node->pre->next = node;
    head_node->pre = node;
    head_node->data++;
}

// 出队
int de_queue(node_t *head_node)
{
    if (is_empty(head_node))
    {
        return 0; // 队已空
    }
    else
    {
        node_t *node = head_node->next;
        int data = node->data;
        head_node->next = head_node->next->next;
        head_node->next->pre = head_node;
        free(node);
        head_node->data--;
        return data;
    }
}

// 判断队空
int is_empty(node_t *head_node)
{
    if (head_node->data == 0 || head_node->next == head_node)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 输出队列
void print_queue(node_t *head_node)
{
    node_t *node = head_node->next; // 从第一个节点开始
    while (node != head_node)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("HEAD\n");
}

int main(int argc, char *argv[])
{
    node_t *Q = init_queue();
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