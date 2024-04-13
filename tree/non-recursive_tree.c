/*  非递归遍历二叉树

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

// 栈节点定义
typedef struct StackNode
{
    treeNode_t *t_node; // 存放指向树节点的指针。
    struct StackNode *next;
} stackNode_t;

// 创建树
void create_tree(treeNode_t **tree)
{
    char ch;
    scanf(" %c", &ch); // 此处使用 scanf(" %c", &ch);（注意 %c 前的空格），这样可以自动忽略任何空白字符，包括空格、制表符和新行

    if (ch == '#')
        *tree = NULL;
    else
    {
        *tree = (treeNode_t *)malloc(sizeof(treeNode_t));
        (*tree)->data = ch;
        create_tree(&((*tree)->lchild));
        create_tree(&((*tree)->rchild));
    }
}

// 释放二叉树内存，递归释放每个节点
void free_tree(treeNode_t *tree)
{
    if (tree)
    {
        free_tree(tree->lchild);
        free_tree(tree->rchild);
        free(tree);
    }
}

// 创建栈
stackNode_t *init_stack()
{
    stackNode_t *stack = (stackNode_t *)malloc(sizeof(stackNode_t));
    stack->t_node = NULL;
    stack->next = NULL;
    return stack;
}
// 判断栈空
int is_empty(stackNode_t *stack)
{
    return stack->next == NULL;
}

// 入栈
void push(treeNode_t *tree, stackNode_t *stack)
{
    stackNode_t *node = (stackNode_t *)malloc(sizeof(stackNode_t));
    node->t_node = tree;
    node->next = stack->next;
    stack->next = node;
}

// 出栈
treeNode_t *pop(stackNode_t *stack)
{
    if (is_empty(stack))
        return NULL;
    else
    {
        stackNode_t *node = stack->next;
        stack->next = node->next;
        treeNode_t *result = node->t_node;
        free(node);
        return result;
    }
}

// 非递归前序遍历实现
void pre_order(treeNode_t *tree)
{
    treeNode_t *current = tree;        // 当前遍历的节点
    stackNode_t *stack = init_stack(); // 初始化栈

    // 当还有节点未遍历或栈不为空时，继续循环
    while (current || !is_empty(stack))
    {
        // 一直向左遍历，直到没有左子节点
        while (current)
        {
            printf("%c ", current->data); // 访问当前节点
            push(current, stack);         // 当前节点入栈
            current = current->lchild;    // 移至左子节点
        }
        // 当左侧遍历完成后，从栈中弹出节点并转向右子节点
        if (!is_empty(stack))
        {
            current = pop(stack);      // 弹出节点
            current = current->rchild; // 转向右子节点
        }
    }
    free(stack); // 遍历完成后释放栈内存
}

// 非递归中序遍历实现
void in_order(treeNode_t *tree)
{
    treeNode_t *current = tree;        // 当前遍历的节点
    stackNode_t *stack = init_stack(); // 初始化栈

    // 当还有节点未遍历或栈不为空时，继续循环
    while (current || !is_empty(stack))
    {
        // 一直向左遍历，直到没有左子节点
        while (current)
        {
            push(current, stack);      // 当前节点入栈
            current = current->lchild; // 移至左子节点
        }
        // 当左侧遍历完成后，从栈中弹出节点进行访问，然后转向右子节点
        if (!is_empty(stack))
        {
            current = pop(stack);         // 弹出节点
            printf("%c ", current->data); // 访问节点
            current = current->rchild;    // 转向右子节点
        }
    }
    free(stack); // 遍历完成后释放栈内存
}

// 非递归后序遍历实现
void post_order(treeNode_t *tree)
{
    if (!tree)
        return;
    stackNode_t *stack = init_stack(); // 初始化栈
    treeNode_t *current = tree;        // 当前遍历的节点
    treeNode_t *last_visited = NULL;   // 上一个访问过的节点

    // 当还有节点未遍历或栈不为空时，继续循环
    while (current || !is_empty(stack))
    {
        // 一直向左遍历，直到没有左子节点
        if (current)
        {
            push(current, stack);      // 当前节点入栈
            current = current->lchild; // 移至左子节点
        }
        else
        {
            treeNode_t *peek_node = stack->next->t_node; // 查看栈顶元素但不弹出
            // 如果右子节点存在且未被访问，转向右子节点
            if (peek_node->rchild && last_visited != peek_node->rchild)
            {
                current = peek_node->rchild;
            }
            else
            {
                // 访问节点，并标记为最后访问过的节点
                printf("%c ", peek_node->data);
                last_visited = pop(stack); // 弹出节点，并更新最后访问节点
            }
        }
    }
    free(stack); // 遍历完成后释放栈内存
}

int main(int argc, char *argv[])
{
    treeNode_t *T = NULL;
    create_tree(&T);

    printf("PreOrder: ");
    pre_order(T);
    printf("\nInOrder: ");
    in_order(T);
    printf("\nPostOrder: ");
    post_order(T);
    printf("\n");

    free_tree(T);
    return 0;
}