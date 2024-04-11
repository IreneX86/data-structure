/*  kmp (Knuth-Morris-Pratt)

    Author:IreneX86
    E-mail:irene.127.0.0.1@gmail.com
*/

#include <stdio.h>
#include <string.h>

void Next(char *sub, int *next)
{
    int len_sub = strlen(sub);
    next[0] = -1;

    int i = 0, j = -1;
    while (i < strlen(sub))
    {
        if (j == -1 || sub[i] == sub[j])
        {
            i++;
            j++;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
}

int kmp(char *master, char *sub)
{
    int len_master = strlen(master);
    int len_sub = strlen(sub);

    int next[len_sub];
    Next(sub, next);

    printf("next_array: ");
    for (int l = 0; l < len_sub - 1; l++)
    {
        printf("%d->", next[l]);
    }
    printf("%d\n", next[len_sub - 1]);

    int i = 0, j = 0;
    while (i < len_master)
    {
        if (j == -1 || master[i] == sub[j])
        {
            i++;
            j++;
        }
        else
        {
            j = next[j];
        }

        if (j == len_sub)
            return i - j;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    int index = kmp("ababcabcacbab", "abcac"); // index start from 0

    if (index == -1)
        printf("Not found.\n");
    else
        printf("index: %d\n", index);

    return 0;
}
