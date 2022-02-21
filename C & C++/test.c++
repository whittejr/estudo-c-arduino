#include <stdio.h>

int a = 0;
int main(void)
{
    printf("Digite o tamanho da piramide: ");
    
    do
    {
        scanf("%d", a);
    } while (a < 1 || a > 8);
    
    
    printf("O valor e %d", a);
  
}