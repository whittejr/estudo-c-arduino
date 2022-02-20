int main(void)
{
    int a;

    do
    {
        printf("Digite o tamanho da piramide: ");
        scanf("%d", a);
    }
    while(a < 1 || a < 8);

    for(int l = 0; l < a; l++)
    {
        printf("#");
    }
    
    return 0;
}