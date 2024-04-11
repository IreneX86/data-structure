/*  暴力匹配(brute force match)

    Author:IreneX86
    E-mail:irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <string.h>

int match(char *master, char *sub)
{
    int i = 0, j = 0;
    while (i < strlen(master) && j < strlen(sub))
    {
        if (master[i] == sub[j])
        {
            i++;
            j++;
        }
        else
        {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j == strlen(sub))
        return i - strlen(sub);

    return -1;
}

int main(int argc, char *argv[])
{
    int index = match("ababcabcacbab", "abcac"); // index start from 0

    if (index == -1)
        printf("Not found.\n");
    else
        printf("%d\n", index);

    return 0;
}
