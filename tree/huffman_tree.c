/*  哈夫曼树 (Huffman tree)

    又称最优二叉树，是一种特殊的二叉树。
    它在数据压缩等领域中特别有用，主要是因为它可以用来创建高效的编码系统。
    哈夫曼树的核心思想是基于字符出现的频率或概率来构建最优的编码方式，其中出现频率高的字符使用较短的编码，出现频率低的字符使用较长的编码。

    Author: IreneX86
    E-mail: irene.127.0.0.1@gmail.com

*/

#include <stdio.h>
#include <stdlib.h>
#define MAXNUM 1024

// 定义哈夫曼树节点结构
typedef struct TreeNode
{
    int weight; // 节点权重，用于存储频率或概率
    int parent; // 父节点的索引
    int lchild; // 左孩子的索引
    int rchild; // 右孩子的索引
} treeNode_t;

// 哈夫曼树结构
typedef struct HfmTree
{
    treeNode_t *data; // 节点数组，存储所有哈夫曼树节点
    int length;       // 数组中节点的实际数量
} hfmTree_t;

// 初始化哈夫曼树
hfmTree_t *init_tree(int *weight, int length)
{
    hfmTree_t *tree = (hfmTree_t *)malloc(sizeof(hfmTree_t));
    tree->data = (treeNode_t *)malloc(sizeof(treeNode_t) * (2 * length - 1)); // 节点数组有 2n-1 项
    tree->length = length;
    for (int i = 0; i < length; i++)
    {
        tree->data[i].weight = weight[i];
        tree->data[i].parent = 0;  // 初始化时，所有节点的父节点索引设置为0，表示没有父节点
        tree->data[i].lchild = -1; // 初始化为-1，表示没有孩子
        tree->data[i].rchild = -1;
    }
    return tree;
}

// 选择两个最小权值的节点
int *select_min2(hfmTree_t *tree)
{
    int min = MAXNUM;
    int second_min = MAXNUM;
    int min_index;
    int second_index;

    // 寻找最小权值的节点
    for (int i = 0; i < tree->length; i++)
    {
        if (tree->data[i].parent == 0) // 仅考虑还没有父节点的节点
        {
            if (tree->data[i].weight < min)
            {
                min = tree->data[i].weight;
                min_index = i;
            }
        }
    }
    // 寻找第二小权值的节点
    for (int i = 0; i < tree->length; i++)
    {
        if (tree->data[i].parent == 0 && i != min_index)
        {
            if (tree->data[i].weight < second_min)
            {
                second_min = tree->data[i].weight;
                second_index = i;
            }
        }
    }

    int *result = (int *)malloc(sizeof(int) * 2);
    result[0] = min_index;
    result[1] = second_index;
    return result; // (这么操作可以一次输出所需的两个数)
}

// 构建哈夫曼树
void create_hfmtree(hfmTree_t *tree)
{
    int *result;
    int min;
    int second_min;
    int length = tree->length * 2 - 1;

    // 通过合并最小权值的节点构建新的哈夫曼树
    for (int i = tree->length; i < length; i++) // (需要合并 n-1 次来构建哈夫曼树)
    {
        result = select_min2(tree);
        min = result[0];
        second_min = result[1];
        // 创建新节点作为两个最小节点的父节点
        tree->data[i].weight = tree->data[min].weight + tree->data[second_min].weight;
        tree->data[i].lchild = min;
        tree->data[i].rchild = second_min;
        tree->data[i].parent = 0;
        tree->data[min].parent = i;
        tree->data[second_min].parent = i;
        tree->length++;
    }
}

// 前序遍历输出哈夫曼树
void pre_order(hfmTree_t *tree, int index)
{
    if (index != -1)
    {
        printf("%d ", tree->data[index].weight);
        pre_order(tree, tree->data[index].lchild);
        pre_order(tree, tree->data[index].rchild);
    }
}

// 删除节点
/*
    在哈夫曼树中删除节点并不是一个常规的操作，因为哈夫曼树主要用于数据的编码和解码，而不是作为一个常规的数据结构进行数据的增删改。
    但如果要实现一个函数以从哈夫曼树中删除一个节点，这通常意味着需要重新构建树，因为删除节点可能会破坏树的最优性和平衡性。
    一个可能的实现是删除一个具有指定权重的节点，然后重建整个哈夫曼树。
    Not a common operation; the node removal and Huffman tree reconstruction would typically require re-running the Huffman encoding algorithm
*/

// 释放哈夫曼树
/*
treeNode_t类型在哈夫曼树实现中是作为数组的一部分分配的，而不是单独的指针链结构。
如果使用之前的free_tree(treeNode_t *tree)函数，它会尝试递归地访问并释放不是通过指针动态连接的节点，这会导致不正确的内存访问并可能引起程序崩溃。
正确的做法是释放整个数组和包含它的结构，如free_hfmtree函数所示。
这样处理是因为所有节点都在单个调用中被分配（即数组的分配），所以也应该在单个调用中被释放。
*/
void free_hfmtree(hfmTree_t *tree)
{
    free(tree->data); // 释放存储所有节点的数组
    free(tree);       // 释放哈夫曼树结构体本身
}

int main(int argc, char *argv[])
{
    int weight[7] = {5, 1, 3, 6, 11, 2, 4};
    hfmTree_t *T = init_tree(weight, 7);
    create_hfmtree(T);
    pre_order(T, T->length - 1);
    printf("\n");
    free_hfmtree(T);

    return 0;
}