/* 单独链接（Separate Chaining）

    是另一种解决哈希冲突的方法。
    它使用一个数组来存储链表或者其他数据结构，
    当发生哈希冲突时，将冲突的键值对存储在对应位置的链表中。
    这样，即使多个键映射到相同的位置，它们也可以通过链表存储在同一个位置。

*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10

// 定义节点结构体，用于链表存储哈希冲突的键值对
typedef struct Node
{
    int data;          // 键值对中的键
    struct Node *next; // 指向下一个节点的指针
} node_t;

node_t *hash_table[SIZE] = {NULL}; // 哈希表，每个元素是一个指向链表头的指针

// 哈希函数，计算键的哈希值
int hash(int key)
{
    return key % SIZE;
}

// 插入键值对到哈希表
void insert(int key)
{
    int index = hash(key);                               // 计算键的哈希值
    node_t *new_node = (node_t *)malloc(sizeof(node_t)); // 创建新节点
    new_node->data = key;                                // 设置节点的键
    new_node->next = NULL;                               // 初始化节点的下一个指针为 NULL

    if (hash_table[index] == NULL) // 如果哈希表当前位置为空
    {
        hash_table[index] = new_node; // 直接将新节点设为头节点
    }
    else // 如果哈希表当前位置不为空（发生哈希冲突）
    {
        node_t *temp = hash_table[index]; // 临时指针指向当前位置的头节点
        while (temp->next != NULL)        // 遍历链表，直到找到尾节点
        {
            temp = temp->next;
        }
        temp->next = new_node; // 将新节点连接到链表的末尾
    }
}

// 输出哈希表
void display(void)
{
    for (int i = 0; i < SIZE; i++) // 遍历哈希表数组
    {
        printf("Index %d: ", i);      // 打印当前索引
        node_t *temp = hash_table[i]; // 临时指针指向当前位置的头节点
        while (temp != NULL)          // 遍历链表
        {
            printf("%d->", temp->data); // 打印当前节点的键
            temp = temp->next;          // 移动到下一个节点
        }
        printf("NULL\n"); // 打印链表末尾的 NULL
    }
}

int main(int argc, char *argv[])
{
    int keys[] = {23, 45, 34, 67, 78, 89, 56};
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++) // 遍历键数组
    {
        insert(keys[i]); // 将键插入哈希表
    }
    display(); // 打印哈希表

    return 0;
}
