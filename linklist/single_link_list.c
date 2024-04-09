#include <stdio.h>
#include <stdlib.h>

typedef struct Node
{
    int data;
    struct Node *next;
} node_t;

// 初始化链表，返回头节点（头节点用于存储链表信息，头节点的下一个节点才是链表的第一个节点）
node_t *init_list()
{
    node_t *head_node = (node_t *)malloc(sizeof(node_t));
    head_node->data = 0; // 头节点的data用来记录链表中元素个数（而不是作为一个节点的数值）
    head_node->next = NULL;
    return head_node;
}

// 头插
void head_insert(node_t *head_node, int data)
{
    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = head_node->next;
    head_node->next = node;
    head_node->data++;
}

// 尾插
void tail_insert(node_t *head_node, int data)
{
    node_t *tail_node = head_node;
    while (tail_node->next != NULL) // 遍历直到最后一个节点
    {
        tail_node = tail_node->next;
    }

    node_t *node = (node_t *)malloc(sizeof(node_t));
    node->data = data;
    node->next = NULL;
    tail_node->next = node;
    head_node->data++;
}

// 删除节点，若成功则返回1，未找到data则返回0
int delete(node_t *head_node, int data)
{
    node_t *pre_node = head_node;
    node_t *current = head_node->next;

    while (current)
    {
        if (current->data == data)
        {
            pre_node->next = current->next;
            free(current);
            head_node->data--;
            return 1;
        }
        pre_node = current;
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