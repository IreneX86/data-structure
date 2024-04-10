/* 栈(stack) 是一种线性表。

    特点：后进先出。(Last In First Out)

    操作：1.初始化栈
         2.入栈
         3.出栈
         4.判断栈空

    Author: IreneX86
    Email: Irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node_t;

// 初始化栈，返回头节点（头节点用于存储栈信息，头节点的下一个节点才是栈的第一个节点）
node_t *init_stack()
{
    node_t *head_node = (node_t *)malloc(sizeof(node_t));
    head_node->data = 0; // 头节点的data用来记录栈中元素个数（而不是作为一个节点的数值）
    head_node->next = NULL;
    return head_node;
}

// 入栈
void push(node_t *head_node, int data)
{
    node_t *push_node = (node_t *)malloc(sizeof(node_t));
    push_node->data = data;
    push_node->next = head_node->next;
    head_node->next = push_node;
    head_node->data++;
}

// 出栈
int pop(node_t *head_node)
{
    if (head_node->data == 0)
    {
        return 0; // 栈已空
    }
    else
    {
        node_t *pop_node = head_node->next;
        int pop_data = pop_node->data;
        head_node->next = pop_node->next;
        free(pop_node);
        head_node->data--;
        return pop_data;
    }
}

// 判断栈空
int is_empty(node_t *head_node)
{
    if (head_node->data == 0 || head_node->next == NULL)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

// 输出栈
void print_stack(node_t *head_node)
{
    node_t *node = head_node->next; // 从第一个节点开始
    while (node)
    {
        printf("%d->", node->data);
        node = node->next;
    }
    printf("NULL\n");
}

int main(int argc, char *argv[])
{
    node_t *S = init_stack();
    push(S, 1);
    push(S, 4);
    push(S, 9);
    push(S, 6);
    push(S, 2);
    push(S, 5);
    push(S, 0);
    print_stack(S);

    printf("pop = %d\n", pop(S));
    printf("pop = %d\n", pop(S));
    print_stack(S);

    return 0;
}