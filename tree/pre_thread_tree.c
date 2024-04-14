/*  线索二叉树 (thread tree)

    如果算法中多次涉及到对二叉树的遍历，普通的二叉树就需要使用栈结构做重复性的操作。
    线索二叉树不需要如此，在遍历的同时，使用二叉树中空闲的内存空间记录某些结点的前趋和后继元素的位置（不是全部）。
    这样在算法后期需要遍历二叉树时，就可以利用保存的结点信息，提高了遍历的效率。

    如果在二叉树中想保存每个结点前趋和后继所在的位置信息，最直接的想法就是改变结点的结构，即添加两个指针域，分别指向该结点的前趋和后继。

    但是这种方式会降低树存储结构的存储密度。而对于二叉树来讲，其本身还有很多未利用的空间。
    (存储密度指的是数据本身所占的存储空间和整个结点结构所占的存储量之比。)

    每一棵二叉树上，很多结点都含有未使用的指向NULL的指针域。除了度为2的结点，度为 1 的结点，有一个空的指针域；叶子结点两个指针域都为NULL。
    (规律：在有 n 个结点的二叉链表中必定存在 n+1 个空指针域。)
    (一个二叉树有 n 个结点，则有 n-1 个指针指向它们；一共有 2n 个指针，2n-(n-1)=n+1 个指针没有用；利用这 n+1 个指针，来指向二叉树遍历序列中的前驱和后继)

    线索链表中的“线索”，指的是链表中指向结点前趋和后继的指针。
    线索二叉树实际上就是使用这些空指针域来存储结点之间前趋和后继关系的一种特殊的二叉树。


    线索二叉树的结点结构：
    __________________________________________
    | lchild | l_tag | data | r_tag | rchild |
    ------------------------------------------

    l_tag 和 r_tag 为标志域。实际上就是两个布尔类型的变量：
    l_tag 值为 0 时，表示 lchild 指针域指向的是该结点的左孩子；为 1 时，表示指向的是该结点的直接前趋结点；
    r_tag 值为 0 时，表示 rchild 指针域指向的是该结点的右孩子；为 1 时，表示指向的是该结点的直接后继结点。

    表示二叉树时，使用如上所示的结点结构构成的二叉链表，被称为线索链表；构建的二叉树称为线索二叉树。

    (线索链表中的“线索”，指的是链表中指向结点前趋和后继的指针。)
    二叉树经过某种遍历方法转化为线索二叉树的过程称为线索化。

    将二叉树转化为线索二叉树，实质上是在遍历二叉树的过程中，将二叉链表中的空指针改为指向直接前趋或者直接后继的线索。
    线索化的过程即为在遍历的过程中修改空指针的过程。

    e.g.在遍历过程中，如果当前结点没有左孩子，需要将该结点的 lchild 指针指向遍历过程中的前一个结点，所以在遍历过程中，设置一个指针(名为 pre )，时刻指向当前访问结点的前一个结点。

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct TreeNode
{
    char data;
    struct TreeNode *lchild;
    struct TreeNode *rchild;
    int l_tag; // 左线索标志
    int r_tag; // 右线索标志
} treeNode_t;

// 递归创建二叉树
void create_tree(treeNode_t **tree)
{
    char ch;
    scanf(" %c", &ch);

    if (ch == '#')
        *tree = NULL;
    else
    {
        *tree = (treeNode_t *)malloc(sizeof(treeNode_t));
        /*
        if (*tree == NULL) {
            fprintf(stderr, "Failed to allocate memory\n");
            exit(EXIT_FAILURE);
        }
        */
        (*tree)->data = ch;
        (*tree)->l_tag = 0;
        (*tree)->r_tag = 0;
        create_tree(&((*tree)->lchild));
        create_tree(&((*tree)->rchild));
    }
}

// 释放线索二叉树内存
// 只在左右子树的指针不是线索时才递归释放(否则会导致segmentation fault)
// 释放节点自身前，不会尝试释放线索指向的节点
void free_threaded_tree(treeNode_t *tree)
{
    if (tree == NULL)
        return;

    // 递归释放左子树，仅当左指针不是线索时
    if (tree->l_tag == 0 && tree->lchild != NULL)
    {
        free_threaded_tree(tree->lchild);
    }
    // 递归释放右子树，仅当右指针不是线索时
    if (tree->r_tag == 0 && tree->rchild != NULL)
    {
        free_threaded_tree(tree->rchild);
    }

    // 释放当前节点
    free(tree);
}

// 前序线索化处理
void pre_thread(treeNode_t *tree, treeNode_t **pre)
{
    if (tree)
    {
        // 处理当前节点
        if (!tree->lchild) // 当前节点左子树为空 则指向前驱(建立前驱线索)
        {
            tree->l_tag = 1;
            tree->lchild = *pre;
        }
        if (*pre && !(*pre)->rchild) // 前驱节点的右子树为空 则指向其后继(其后继为当前节点)
        {
            (*pre)->r_tag = 1;
            (*pre)->rchild = tree;
        }

        *pre = tree; // 更新前驱节点pre为当前节点

        if (tree->l_tag == 0)              // 当有左子树时
            pre_thread(tree->lchild, pre); // 递归左子树
        pre_thread(tree->rchild, pre);     // 递归右子树
    }
}

// 根据先序线索获取后继节点
treeNode_t *get_next(treeNode_t *tree)
{
    if (!tree)
        return NULL;
    if (tree->r_tag == 1 || tree->l_tag == 1)
        return tree->rchild;
    else
        return tree->lchild;
}

int main(int argc, char *argv[])
{
    treeNode_t *T = NULL;
    treeNode_t *pre = NULL;
    create_tree(&T);

    pre_thread(T, &pre); // 进行先序线索化

    if (pre)
    {
        pre->r_tag = 1; // 先序遍历完pre到了最后一个节点，最后一个节点的后继线索指向NULL
        pre->rchild = NULL;
    }

    // 使用线索进行先序遍历
    printf("Pre-order traversal using threading: ");
    for (treeNode_t *node = T; node != NULL; node = get_next(node))
    {
        printf("%c ", node->data);
    }
    printf("\n");

    free_threaded_tree(T);

    return 0;
}