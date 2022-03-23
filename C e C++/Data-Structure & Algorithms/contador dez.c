#include <stdio.h>

int main(void)
{
    int i = 15;

    while (i >= 10)
    {
        i--;
        printf("%d", i);
    }
    if (i == 10)
    {
        do
        {
            i--;
            printf("%d", i);
        }
        while (i != 0);
    }
}