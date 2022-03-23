#include <stdio.h>

int main(void)
{
    int i = 0;
    int timer;


    printf("Acesso negado.\n");

    for (int timer = 10; timer >= i; timer--)
    {
        printf("%d\n", timer);
        sleep(1);
    }
    printf("Programa resetado.");
}