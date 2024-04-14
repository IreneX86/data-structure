/*  二叉排序树(Binary Search Tree)

    一棵树，左子树上所有结点的值都比根节点小，右子树上所有结点的值都比根节点大。此性质递归。
    树中的结点的值不重复。

    Author: IreneX86
    E-mail: irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    int data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} treeNode_t;

treeNode_t *bst_search(treeNode_t *t_node, int data)
{
    if (t_node)
    {
        if (t_node->data == data)
            return t_node;
        else if (data < t_node->data)
            return bst_search(t_node->lchild, data);
        else
            return bst_search(t_node->rchild, data);
    }
    else
        return NULL;
}

void bst_insert(treeNode_t **tree, int data)
{
    if (*tree == NULL)
    {
        *tree = (treeNode_t *)malloc(sizeof(treeNode_t));
        (*tree)->data = data;
        (*tree)->lchild = NULL;
        (*tree)->rchild = NULL;
    }
    else if (data == (*tree)->data)
        return;
    else if (data < (*tree)->data)
        bst_insert(&((*tree)->lchild), data);
    else
        bst_insert(&((*tree)->rchild), data);
}

void pre_order(treeNode_t *tree)
{
    if (tree)
    {
        printf("%d ", tree->data);
        pre_order(tree->lchild);
        pre_order(tree->rchild);
    }
}

/*
    删除节点：在二叉搜索树中删除节点时，有三种情况需要考虑：
    1.无子节点：直接删除该节点。
    2.一个子节点：删除节点，并用其子节点替代。
    3.两个子节点：用其右子树的最小节点（或左子树的最大节点）替代删除节点，然后删除那个最小（或最大）节点。
*/

treeNode_t *find_min(treeNode_t *node)
{
    while (node && node->lchild)
        node = node->lchild;
    return node;
}

int bst_delete(treeNode_t **tree, int key)
{
    if (*tree == NULL)
        return 0;
    if (key < (*tree)->data)
        bst_delete(&((*tree)->lchild), key);
    else if (key > (*tree)->data)
        bst_delete(&((*tree)->rchild), key);
    else
    {
        if ((*tree)->lchild == NULL) // 节点只有右子节点or无子节点
        {
            treeNode_t *temp = *tree;
            *tree = (*tree)->rchild;
            free(temp);
        }
        else if ((*tree)->rchild == NULL) // 节点只有左节点
        {
            treeNode_t *temp = *tree;
            *tree = (*tree)->lchild;
            free(temp);
        }
        else // 有两个子节点
        {
            treeNode_t *temp = find_min((*tree)->rchild);
            (*tree)->data = temp->data;
            bst_delete(&((*tree)->rchild), temp->data);
        }
    }
    return 1;
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
    int nums[6] = {2, 13, 7, 5, 11, 3};
    for (int i = 0; i < 6; i++)
    {
        bst_insert(&T, nums[i]);
    }

    printf("Initial tree (Pre-order): ");
    pre_order(T);
    printf("\n");

    bst_delete(&T, 7);

    printf("After deleting 7 (Pre-order): ");
    pre_order(T);
    printf("\n");

    free_tree(T); // 清理所有树的节点
    T = NULL;     // 安全地将树的根设置为NULL，避免野指针

    return 0;
}