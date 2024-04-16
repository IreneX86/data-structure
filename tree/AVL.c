/*  平衡二叉树

    二叉排序树(BST)基础上设计的自平衡二叉查找树。
    查找、插入和删除在平均和最坏情况下的时间复杂度都是 O(log n)。
    增加和删除元素的操作则可能需要借由一次或多次树旋转，以实现树的重新平衡。

    Author: IreneX86
    E-mail: irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

// 定义二叉树节点结构体
typedef struct TreeNode
{
    int data;
    int height; // 建立过程中需要调整，调整需要用到树的高度，所以加上此字段来标识当前树的高度
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} treeNode_t;

// 获取节点的高度
int get_height(treeNode_t *node)
{
    return node ? node->height : 0;
}

// 计算两个整数的最大值
int max(int a, int b)
{
    return a > b ? a : b;
}

// 更新节点的高度
void update_height(treeNode_t *node)
{
    if (node)
        node->height = 1 + max(get_height(node->lchild), get_height(node->rchild));
}

// 左左旋转（LL）
void ll_rotation(treeNode_t **node)
{
    treeNode_t *temp = (*node)->lchild;
    (*node)->lchild = temp->rchild;
    temp->rchild = *node;
    update_height(*node);
    update_height(temp);
    *node = temp;
}

// 右右旋转（RR）
void rr_rotation(treeNode_t **node)
{
    treeNode_t *temp = (*node)->rchild;
    (*node)->rchild = temp->lchild;
    temp->lchild = *node;
    update_height(*node);
    update_height(temp);
    *node = temp;
}

// 左右旋转（LR）
void lr_rotation(treeNode_t **node)
{
    rr_rotation(&((*node)->lchild));
    ll_rotation(node);
}

// 右左旋转（RL）
void rl_rotation(treeNode_t **node)
{
    ll_rotation(&((*node)->rchild));
    rr_rotation(node);
}

// 前序遍历输出树
void pre_order(treeNode_t *tree)
{
    if (tree)
    {
        printf("%d ", tree->data);
        pre_order(tree->lchild);
        pre_order(tree->rchild);
    }
}

int balance_factor(treeNode_t *node)
{
    return node ? get_height(node->lchild) - get_height(node->rchild) : 0;
}

// 查找二叉树中最小的节点(即最左节点)
treeNode_t *find_min(treeNode_t *node)
{
    while (node && node->lchild)
        node = node->lchild;
    return node;
}

// AVL树插入操作
void avl_insert(treeNode_t **tree, int data)
{
    if (*tree == NULL)
    {
        *tree = (treeNode_t *)malloc(sizeof(treeNode_t));
        // if (!*tree) return; // Check for malloc failure
        (*tree)->data = data;
        (*tree)->height = 1;
        (*tree)->lchild = NULL;
        (*tree)->rchild = NULL;
    }
    else if (data < (*tree)->data)
    {
        avl_insert(&(*tree)->lchild, data);
    }
    else if (data > (*tree)->data)
    {
        avl_insert(&(*tree)->rchild, data);
    }

    update_height(*tree);

    int balance = balance_factor(*tree);

    if (balance > 1)
    {
        if (data < (*tree)->lchild->data) // ll
            ll_rotation(tree);
        else // lr
        {
            lr_rotation(tree);
        }
    }
    else if (balance < -1)
    {
        if (data > (*tree)->rchild->data) // rr
            rr_rotation(tree);
        else // rl
        {
            rl_rotation(tree);
        }
    }

    // update_height(*tree);
}

/*
    删除节点：
    是AVL树中最复杂的操作之一，因为它可能需要在删除后进行多次重新平衡。

    删除操作可以分为三种情况：
    1.无子节点（叶子节点）：直接删除节点。
    2.一个子节点：删除节点，并用其唯一的子节点替换它。
    3.两个子节点：找到节点的右子树中的最小值（或左子树中的最大值），用它来替换删除的节点，然后在其原位置递归删除那个最小（或最大）节点。

*/
// AVL树删除操作
void avl_delete(treeNode_t **node, int key)
{
    if (*node == NULL)
        return;

    if (key < (*node)->data)
    {
        avl_delete(&((*node)->lchild), key);
    }
    else if (key > (*node)->data)
    {
        avl_delete(&((*node)->rchild), key);
    }
    else
    {
        // 节点只有一个子节点or没有子节点
        if ((*node)->lchild == NULL || (*node)->rchild == NULL)
        {
            treeNode_t *temp = (*node)->lchild ? (*node)->lchild : (*node)->rchild;
            if (temp == NULL)
            { // 没有子节点
                temp = *node;
                *node = NULL; // avoid dangling pointers (避免悬垂指针)
            }
            else
            {                   // 只有一个子节点
                **node = *temp; // Copy the contents of the non-empty child
            }
            free(temp);
        }
        else
        {
            // 有两个孩子的节点：获取中序后继者
            treeNode_t *temp = find_min((*node)->rchild);
            (*node)->data = temp->data;
            avl_delete(&((*node)->rchild), temp->data);
        }
    }

    if (*node == NULL) // 如果树只有一个节点并且它已被删除
        return;

    update_height(*node); // 更新节点高度

    int balance = balance_factor(*node); // 检查并修复AVL树的平衡

    // ll
    if (balance > 1 && balance_factor((*node)->lchild) >= 0)
    {
        ll_rotation(node);
    }
    // lr
    else if (balance > 1 && balance_factor((*node)->lchild) < 0)
    {
        lr_rotation(node);
    }
    // rr
    else if (balance < -1 && balance_factor((*node)->rchild) <= 0)
    {
        rr_rotation(node);
    }
    // rl
    else if (balance < -1 && balance_factor((*node)->rchild) > 0)
    {
        rl_rotation(node);
    }
}

// 释放整个二叉树
void free_tree(treeNode_t *tree)
{
    if (tree == NULL)
    {
        return;
    }
    free_tree(tree->lchild);
    free_tree(tree->rchild);
    free(tree);
}

int main()
{
    treeNode_t *T = NULL;
    int nums[] = {10, 20, 30, 40, 50, 25};
    for (int i = 0; i < 6; i++)
    {
        avl_insert(&T, nums[i]);
    }

    printf("Initial tree (Pre-order): ");
    pre_order(T);
    printf("\n");

    avl_delete(&T, 20);

    printf("After deleting 20 (Pre-order): ");
    pre_order(T);
    printf("\n");

    free_tree(T); // 清理所有树的节点
    T = NULL;     // 安全地将树的根设置为NULL，避免野指针

    return 0;
}