linear probing
线性探测

separate chaining
单独链接

cuckoo hashing
布谷鸟哈希



/*
可能能用到的函数：

memset 是 C 标准库 <string.h> 中的一个函数，其作用是将指定内存区域的内容全部设置为指定的值。

函数原型如下：
void *memset(void *ptr, int value, size_t num);

参数解释：
ptr：要设置的内存区域的起始地址。
value：要设置的值，通常是一个无符号字符或者整数。
num：要设置的字节数。
memset 在实际应用中常用于对数组、结构体等连续内存块进行初始化或者清零操作。例如，可以使用 memset 将数组所有元素设置为特定值，或者将结构体清零等。

示例：
#include <stdio.h>
#include <string.h>

int main() {
    int numbers[5];

    // 使用 memset 将数组元素设置为 0
    memset(numbers, 0, sizeof(numbers));

    for (int i = 0; i < 5; i++) {
        printf("%d ", numbers[i]);
    }
    printf("\n");

    return 0;
}
在这个例子中，memset(numbers, 0, sizeof(numbers)) 将整数数组 numbers 中的所有元素设置为 0。

*/
