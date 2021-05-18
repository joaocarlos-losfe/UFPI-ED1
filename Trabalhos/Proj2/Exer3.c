#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>

typedef struct 
{
    char expressao[50][100];
    int topo;

}Expressao;

void menu();

int main()
{
    Expressao expressao;
    expressao.topo = 0;

    int op;

    char strexpressao[100];

    do
    {
        menu();
        scanf("%d", &op);
        

        switch (op)
        {
        case 1:
            printf("(str) digite um expressão: ")

            break;
        
        default:
            break;
        }

    } while (op!=0);
    
    return 0;
}

void menu()
{
    printf("\n0 - sair");
    printf("\n1 - digitar expressão");
    printf("\n2 - digitar expressão");
    printf("\n3 - converter para pos fix\n: ");
}