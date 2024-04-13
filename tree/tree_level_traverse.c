/*  二叉树层次遍历 (level traverse)

    利用队列(queue)实现。

    e.g. 输入 "ABC###D#E##" ，如图：

        A
       /  \
      B    D
     /      \
    C        E

    Author: IreneX86
    E-mail:irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

// 二叉树节点定义
typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} treeNode_t;

// 循环队列节点定义
typedef struct QueueNode
{
    treeNode_t *t_node; // 存放指向树节点的指针。
    struct QueueNode *next;
} queueNode_t;

// 创建二叉树
void create_tree(treeNode_t **tree)
{
    char ch;
    scanf(" %c", &ch); // 此处使用 scanf(" %c", &ch);（注意 %c 前的空格），这样可以自动忽略任何空白字符，包括空格、制表符和新行。

    if (ch == '#') // 用 '#' 代表空结点。
    {
        *tree = NULL;
    }
    else
    {
        *tree = (treeNode_t *)malloc(sizeof(treeNode_t));
        /*
        if (!(*tree))
        {
        fprintf(stderr, "Failed to allocate memory\n");
        exit(EXIT_FAILURE);
        }
         */
        (*tree)->data = ch;
        create_tree(&((*tree)->lchild));
        create_tree(&((*tree)->rchild));
    }
}

// 释放二叉树内存，递归释放每个节点
void free_tree(treeNode_t *tree)
{
    if (tree != NULL)
    {
        free_tree(tree->lchild);
        free_tree(tree->rchild);
        free(tree);
    }
}

// 初始化一个空的循环队列，返回队列头节点
queueNode_t *init_queue()
{
    queueNode_t *queue = (queueNode_t *)malloc(sizeof(queueNode_t));
    /*
    if (!queue) {
        fprintf(stderr, "Failed to allocate memory for queue\n");
        exit(EXIT_FAILURE);
    }
    */
    queue->t_node = NULL; // 设置哨兵节点的数据为NULL
    queue->next = queue;  // 初始化为循环队列，next指向自身
    return queue;
}

// 判断队空，如果队列中只有哨兵节点，则为空
int is_empty(queueNode_t *queue)
{
    return queue->next == queue;
}

// 入队(尾插法)
void en_queue(treeNode_t *tree, queueNode_t *queue)
{
    queueNode_t *en_node = (queueNode_t *)malloc(sizeof(queueNode_t));
    /*
    if (!node) {
        fprintf(stderr, "Failed to allocate memory for queue node\n");
        exit(EXIT_FAILURE);
    }
    */
    en_node->t_node = tree;
    en_node->next = NULL;
    queueNode_t *tail_node = queue;
    while (tail_node->next != NULL)
    {
        tail_node = tail_node->next;
    }
    tail_node->next = en_node;
}

// 出队，并返回其存储的树节点
treeNode_t *de_queue(queueNode_t *queue)
{
    if (is_empty(queue))
        return NULL;
    else
    {
        queueNode_t *de_node = queue->next;
        treeNode_t *result = de_node->t_node;
        queue->next = de_node->next; // 将头部节点从队列中移除
        free(de_node);               // 释放队列节点占用的内存
        return result;
    }
}

// 层次遍历二叉树
void level_traverse(treeNode_t *tree)
{
    if (!tree)
        return;

    queueNode_t *queue = init_queue();
    en_queue(tree, queue);

    while (!is_empty(queue))
    {
        treeNode_t *t_node = de_queue(queue);
        printf("%c ", t_node->data);

        if (t_node->lchild)
            en_queue(t_node->lchild, queue);
        if (t_node->rchild)
            en_queue(t_node->rchild, queue);
    }

    /*
    // 确保所有队列节点都被释放
    while (!is_empty(queue))
        de_queue(queue);
    */

    free(queue);
}

int main(int argc, char *argv[])
{
    treeNode_t *T = NULL;
    create_tree(&T);
    level_traverse(T);
    printf("\n");
    free_tree(T);
    return 0;
}