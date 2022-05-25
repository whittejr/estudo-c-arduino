#include <stdio.h>

int main(void)
{
  int a[50], size, i;

  printf("Digite os tamanho da array: ");
  scanf("%d", &size);

  if (size > 50)
  {
    printf("Tamanho de array invalido.");
    return 1;
  }
  else
  {
    printf("Digite os elementos da array: ");
  }

  for (i = 0; i < size; i++)
  {
    scanf("%d", &a[i]);
  }

  printf("Os elementos da array sao: ");

  for (i = 0; i < size; i++)
  {
    printf("%d", a[i]);
  }
}