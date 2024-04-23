/* 布谷鸟哈希（Cuckoo Hashing）
    是一种哈希表的实现方法，它使用两个哈希函数和两个哈希表来解决哈希冲突。
    每个键值对可以在两个哈希表中的一个位置上存储，
    如果发生冲突，它会先尝试将键值对插入到第一个哈希表中的对应位置，
    如果位置已经被占用，则将占用位置的键值对移到另一个哈希表中，然后继续尝试插入。
    这个过程可能会导致递归移动键值对，直到找到合适的位置或者达到最大移动次数。

    布谷鸟哈希的特点是可以保证常数时间的查找和插入操作，但可能会引入较多的移动操作。

*/

#include <stdio.h>
#include <stdlib.h>
#define SIZE 10
#define MAX_MOVES 10

// 哈希函数1，计算键的哈希值
int hash_1(int key)
{
    return key % SIZE;
}

// 哈希函数2，计算键的备用哈希值
int hash_2(int key)
{
    return (key / SIZE) % SIZE; // 先除以SIZE再取余，得到备用哈希值
}

// 布谷鸟哈希函数，将键插入到哈希表中
void cuckoo_hash(int hash_table[], int keys[], int num_keys)
{
    int moves = 0;                     // 记录移动次数
    for (int i = 0; i < num_keys; i++) // 遍历所有键
    {
        int key = keys[i];             // 当前键
        int index_1 = hash_1(key);     // 计算哈希值1
        int index_2 = hash_2(key);     // 计算哈希值2
        if (hash_table[index_1] == -1) // 如果哈希表中哈希值1的位置为空
        {
            hash_table[index_1] = key; // 直接将键插入哈希表的哈希值1位置
        }
        else if (hash_table[index_2] == -1) // 如果哈希表中哈希值2的位置为空
        {
            hash_table[index_2] = key; // 直接将键插入哈希表的哈希值2位置
        }
        else // 如果两个位置都不为空，发生哈希冲突
        {
            int temp = hash_table[index_1]; // 临时存储哈希值1位置的键
            hash_table[index_1] = key;      // 将当前键插入哈希表的哈希值1位置
            key = temp;                     // 交换键
            moves++;                        // 增加移动次数
        }

        if (moves >= MAX_MOVES) // 如果移动次数超过最大允许移动次数
        {
            printf("Exceeded maximum moves, unable to insert all keys.\n");
            return;
        }
    }
}

// 输出哈希表
void display(int hash_table[])
{
    for (int i = 0; i < SIZE; i++)
    {
        printf("%d ", hash_table[i]);
    }
    printf("\n");
}

int main(int argc, char *argv[])
{
    int hash_table[SIZE] = {-1};                   // 初始化哈希表，-1 表示空位置
    int keys[] = {23, 45, 34, 67, 78, 89, 56};     // 键数组
    int num_keys = sizeof(keys) / sizeof(keys[0]); // 键的数量

    cuckoo_hash(hash_table, keys, num_keys); // 使用布谷鸟哈希插入键到哈希表

    display(hash_table);

    return 0;
}
