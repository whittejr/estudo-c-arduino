#include <stdio.h>

int main()
{
   int n;
   
   do
   {
       
        printf("Altura: ");
        scanf("%d", &n);
   }
    while(n < 1);
    
    for(int i = 0; i < n; i++)
    {
        printf("?");
    }
    printf("\n");
}