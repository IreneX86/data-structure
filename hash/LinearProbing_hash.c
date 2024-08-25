/* linear probing hash (线性探测哈希)

    线性探测（Linear Probing）是一种解决哈希冲突的方法。
    在使用哈希表存储数据时，可能会发生多个键映射到相同的位置的情况，这就是哈希冲突。
    线性探测是一种解决冲突的开放寻址方法，当发生冲突时，它会沿着哈希表的下一个位置继续查找，直到找到一个空的位置或者遍历整个哈希表。

*/

#include <stdio.h>
#define SIZE 10

// 哈希函数，计算键的哈希值
int hash(int key)
{
    return key % SIZE;
}

// 线性探测函数，解决哈希冲突
int linear_probe(int hash_table[], int key)
{
    int index = hash(key);          // 计算键的哈希值
    while (hash_table[index] != -1) // 如果哈希表当前位置不为空
    {
        index = (index + 1) % SIZE; // 线性探测下一个位置
    }
    return index; // 返回可以插入键的位置
}

int main(int argc, char *argv[])
{
    // int hash_table[SIZE] = {-1}; // 初始化哈希表，-1 表示空位置
    // 此处有误。此语法只会将数组的第一个元素初始化为 -1，而其他元素将被初始化为 0。
    // 为初始化整个数组为 -1，需要通过循环手动初始化每个元素：
    int hash_table[SIZE];
    for (int i = 0; i < SIZE; i++) {
        hash_table[i] = -1;
    }
    
    int keys[] = {23, 45, 34, 67, 78, 89, 56};
    for (int i = 0; i < sizeof(keys) / sizeof(keys[0]); i++)
    {
        int index = linear_probe(hash_table, keys[i]); // 线性探测找到可以插入键的位置
        hash_table[index] = keys[i];                   // 将键插入哈希表
    }

    // 输出哈希表
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", hash_table[i]);
    }
    printf("\n");

    return 0;
}
