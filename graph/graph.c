/*  图 (graph)

    此为无向图(Undigraph)的遍历：
    DFS 深度优先搜索
    BFS 广度优先搜索

    Author: IreneX86
    E-mail: irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <stdlib.h>

#define MAXSIZE 5 // 定义队列的最大容量

// 图的节点结构定义
typedef struct Graph
{
    char *vexs;  // 顶点数组 (vertex array)
    int **arcs;  // 邻接矩阵，用于存储边信息 (弧:arc)
    int vex_num; // 顶点数量
    int arc_num; // 边数量
} graph_t;

// 队列结构定义，用于BFS
typedef struct Queue
{
    int front;         // 队头指针
    int rear;          // 队尾指针
    int data[MAXSIZE]; // 队列存储数组
} queue_t;

// 初始化队列
queue_t *init_queue()
{
    queue_t *queue = (queue_t *)malloc(sizeof(queue_t));
    queue->front = queue->rear = 0;
    return queue;
}

// 判断队列是否已满
int is_full(queue_t *queue)
{
    if ((queue->rear + 1) % MAXSIZE == queue->front)
        return 1;
    else
        return 0;
}

// 判断队列是否为空
int is_empty(queue_t *queue)
{
    if (queue->front == queue->rear)
        return 1;
    else
        return 0;
}

// 入队操作
int en_queue(queue_t *queue, int data)
{
    if (is_full(queue))
        return 0;
    else
    {
        queue->data[queue->rear] = data;
        queue->rear = (queue->rear + 1) % MAXSIZE;
        return 1;
    }
}

// 出队操作
int de_queue(queue_t *queue)
{
    if (is_empty(queue))
        return -1;
    else
    {
        int data = queue->data[queue->front];
        queue->front = (queue->front + 1) % MAXSIZE;
        return data;
    }
}

// 初始化图
graph_t *init_graph(int vex_num)
{
    graph_t *graph = (graph_t *)malloc(sizeof(graph_t));   // 分配图结构的内存
    graph->vexs = (char *)malloc(sizeof(char) * vex_num);  // 为顶点数组分配内存，存储图的各个顶点
    graph->arcs = (int **)malloc(sizeof(int *) * vex_num); // 为邻接矩阵分配内存，邻接矩阵用于存储边的信息
    for (int i = 0; i < vex_num; i++)
    {
        graph->arcs[i] = (int *)malloc(sizeof(int) * vex_num); // 为邻接矩阵的每一行分配内存，每行代表与该顶点相邻的其他顶点
    }
    graph->vex_num = vex_num; // 设置图中顶点的数量
    graph->arc_num = 0;       // 初始化图中边的数量为0
    return graph;             // 返回初始化的图结构指针
}

// 创建图，基于提供的顶点和边信息
void create_graph(graph_t *graph, char *vexs, int *arcs)
{
    for (int i = 0; i < graph->vex_num; i++) // 遍历每一个顶点
    {
        graph->vexs[i] = vexs[i];                // 将传入的顶点数据复制到图的顶点数组中
        for (int j = 0; j < graph->vex_num; j++) // 遍历与当前顶点相邻的每一个顶点
        {
            graph->arcs[i][j] = *(arcs + i * graph->vex_num + j); // 从传入的一维数组中读取邻接矩阵信息，并赋值给图的邻接矩阵
            if (graph->arcs[i][j] != 0)                           // 如果邻接矩阵中的值不为0，说明两个顶点之间存在边
            {
                graph->arc_num++; // 增加图中边的计数
            }
        }
    }
    graph->arc_num /= 2; // // 由于每条边在无向图的邻接矩阵中被计算了两次，所以实际边数是计数的一半 (无向图的邻接矩阵沿对角线对称）
}

// 深度优先搜索（DFS）
void dfs(graph_t *graph, int *visited, int index)
{
    printf("%c\t", graph->vexs[index]);      // 输出当前访问的顶点
    visited[index] = 1;                      // 标记当前顶点为已访问
    for (int i = 0; i < graph->vex_num; i++) // 遍历所有顶点，查找当前顶点的邻接顶点
    {
        if (graph->arcs[index][i] == 1 && !visited[i]) // 如果当前顶点与顶点i相连且顶点i未被访问
        {
            dfs(graph, visited, i); // 递归调用dfs，从顶点i继续进行深度优先搜索
        }
    }
}

// 广度优先搜索（BFS）
void bfs(graph_t *graph, int *visited, int index)
{
    queue_t *queue = init_queue();      // 初始化队列
    printf("%c\t", graph->vexs[index]); // 输出当前访问的顶点
    visited[index] = 1;                 // 标记当前顶点为已访问
    en_queue(queue, index);             // 将当前顶点索引加入队列
    while (!is_empty(queue))            // 当队列不为空时继续循环
    {
        int i = de_queue(queue);                 // 从队列中取出一个顶点索引i
        for (int j = 0; j < graph->vex_num; j++) // 遍历所有顶点，查找与顶点i相连的顶点
        {
            if (graph->arcs[i][j] == 1 && !visited[j]) // 如果顶点i与顶点j相连且顶点j未被访问
            {
                printf("%c\t", graph->vexs[j]); // 输出顶点j
                visited[j] = 1;                 // 标记顶点j为已访问
                en_queue(queue, j);             // 将顶点j的索引加入队列，以便后续访问其邻接顶点
            }
        }
    }
}

int main()
{
    graph_t *G = init_graph(5);
    int *visited = (int *)malloc(sizeof(int) * G->vex_num);
    for (int i = 0; i < G->vex_num; i++)
        visited[i] = 0;
    int arcs[5][5] = {
        0, 1, 1, 1, 0,
        1, 0, 1, 1, 1,
        1, 1, 0, 0, 0,
        1, 1, 0, 0, 1,
        0, 1, 0, 1, 0};
    create_graph(G, "ABCDE", (int *)arcs);
    dfs(G, visited, 0);
    printf("\n");
    for (int i = 0; i < G->vex_num; i++)
        visited[i] = 0;
    bfs(G, visited, 0);
    printf("\n");
    return 0;
}
