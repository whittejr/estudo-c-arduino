#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void unlocked();


int pass = 1234;
int count = 0;

int key;

int main(void)
{
    int tentativa;

    for (tentativa = 0; tentativa < 3; tentativa++)
    {
        printf("Digite a senha: ");
        scanf("%d", &key);
        
        if (key != pass)
        {
            printf("Senha Incorreta.\n\n");
        }
        else
        {
            unlocked();
            return 0;
        }
    }
    printf("Acesso Negado. ");

    for (int i = 5; i > 0; i--)
    {
        printf("%d ", i);
        sleep(1);
    }
    printf("\n\n");
    main();
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





