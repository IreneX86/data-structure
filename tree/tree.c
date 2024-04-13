/*  二叉树

    e.g. 输入 "ABC###D#E##" ，如图：

        A
       /  \
      B    D
     /      \
    C        E

    输出：
    PreOrder:ABCDE
    InOrder:CBADE
    PostOrder:CBEDA
    Leaves:CE
    height:3

    Author: IreneX86
    E-mail:irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
} treeNode_t;

// 创建二叉树
void create_tree(treeNode_t **tree)
{
    char ch;
    scanf(" %c", &ch); // 此处使用 scanf(" %c", &ch);（注意 %c 前的空格），这样可以自动忽略任何空白字符，包括空格、制表符和新行。

    if (ch == '#') // 用 '#' 代表空结点。
        *tree = NULL;
    else
    {
        *tree = (treeNode_t *)malloc(sizeof(treeNode_t));
        /*
        if (!(*tree)) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
        */
        (*tree)->data = ch;
        create_tree(&((*tree)->lchild));
        create_tree(&((*tree)->rchild));
    }
}

// free
void free_tree(treeNode_t *tree)
{
    if (tree != NULL)
    {
        free_tree(tree->lchild);
        free_tree(tree->rchild);
        free(tree);
    }
}

// 递归遍历
void pre_order(treeNode_t *tree) // 前序
{
    if (tree)
    {

        printf("%c", tree->data);
        pre_order(tree->lchild);
        pre_order(tree->rchild);
    }
}

void in_order(treeNode_t *tree) // 中序
{
    if (tree)
    {
        in_order(tree->lchild);
        printf("%c", tree->data);
        in_order(tree->rchild);
    }
}

void post_order(treeNode_t *tree) // 后序
{
    if (tree)
    {
        post_order(tree->lchild);
        post_order(tree->rchild);
        printf("%c", tree->data);
    }
}

// 其他操作
void pre_order_print_leaves(treeNode_t *tree) // 先序遍历输出二叉树叶子结点
{
    if (tree)
    {
        if (!tree->lchild && !tree->rchild)
            printf("%c", tree->data);
        pre_order_print_leaves(tree->lchild);
        pre_order_print_leaves(tree->rchild);
    }
}

int post_order_get_height(treeNode_t *tree) // 后序遍历求二叉树的高度
{
    if (tree)
    {
        int l_height = post_order_get_height(tree->lchild);
        int r_height = post_order_get_height(tree->rchild);
        return (l_height > r_height ? l_height : r_height) + 1;
    }
    else
        return 0;
}

int main(int argc, char *argv[])
{
    treeNode_t *T = NULL;
    create_tree(&T);

    printf("\nPreOrder:");
    pre_order(T);

    printf("\nInOrder:");
    in_order(T);

    printf("\nPostOrder:");
    post_order(T);

    printf("\nLeaves:");
    pre_order_print_leaves(T);

    printf("\nheight:%d\n", post_order_get_height(T));

    free_tree(T);
    return 0;
}