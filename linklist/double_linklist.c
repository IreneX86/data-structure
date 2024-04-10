/*
    Author: IreneX86
    Email: Irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *pre;
    struct Node *next;
} node_t;

node_t *init_list()
{
    node_t *head_node = (node_t *)malloc(sizeof(node_t));
    head_node->data = 0;
    head_node->pre = NULL;
    head_node->next = NULL;
    return head_node;
}

void head_insert(node_t *head_node, int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->pre = head_node;
    node->next = head_node->next;
    if (head_node->next)
    {
        head_node->next->pre = node;
        head_node->next = node;
    }
    else
    {
        head_node->next = node;
    }

    head_node->data++;
}

void tail_insert(node_t *head_node, int data)
{
    node_t *tail_node = head_node;
    while (tail_node->next)
    {
        tail_node = tail_node->next;
    }

    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->pre = tail_node;
    node->next = NULL;
    tail_node->next = node;
    head_node->data++;
}

// 删除
int delete(node_t *head_node, int data)
{
    node_t *current = head_node->next;
    while (current)
    {
        if (current->data == data)
        {
            current->pre->next = current->next;
            if (current->next)
            {
                current->next->pre = current->pre;
            }
            free(current);
            head_node->data--;
            return 1;
        }
        current = current->next;
    }
    return 0;
}

// 输出链表
void print_list(node_t *head_node)
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
    node_t *L = init_list();
    head_insert(L, 1);
    head_insert(L, 4);
    head_insert(L, 9);
    head_insert(L, 6);
    head_insert(L, 2);
    head_insert(L, 5);
    head_insert(L, 0);
    tail_insert(L, 2024);
    tail_insert(L, 410);
    tail_insert(L, 740);
    print_list(L);

    if (delete (L, 9))
        printf("successfully deleted\n");
    else
        printf("failed to delete");
    print_list(L);

    return 0;
}