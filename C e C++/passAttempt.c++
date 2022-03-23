#include <stdio.h>
#include <string.h>

void unlocked();


int pass = 1234;
int count = 0;
int tentativa = 0;
int key;

int main(void)
{

    do
    {
        printf("Digite a senha: ");
        scanf("%d", &key);
    } 
    while (key < 1);
    
    if (key == pass)
    {
        unlocked();
        return 0;
    }
        
    else
    {
        printf("Senha Incorreta.\n\n");
        tentativa++;
        main();
        

    if (tentativa == 3)
    {
        printf("Acesso Negado.");

        for (int i = 30; i > 0; i--)
        {
            printf("%d", i);
        }
        main();
    }
    }

    
    
    
}


void unlocked()
{
    printf("Acesso liberado!\n");
}

void digiteSenha()
{
     printf("Digite a senha: ");
     scanf("%d", &key);
}
