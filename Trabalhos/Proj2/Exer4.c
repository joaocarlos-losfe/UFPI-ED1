#include <stdio.h>
#include <stdlib.h>

typedef struct aux
{
    char operadores[4]; //ate 4 digitos
    struct aux* proximo;

}Operacao, *PontOperacao;

typedef struct
{
    PontOperacao topo_pilha;

}Pilha;

void executarOperacao(char *strexpressao);

int main()
{
    Pilha pos_fixa_temp;
    Pilha pos_fixa;
    
    pos_fixa.topo_pilha = NULL;
    pos_fixa_temp.topo_pilha = NULL;

    char expre[] = "40 + 40 * 2 + 5 * ( 1 + 1 )";

    executarOperacao(expre);

    return 0;
}

void executarOperacao(char *strexpressao)
{
    while (*strexpressao != '\0')
    {
        switch (*strexpressao)
        {
        case '(':
        case ')':
        break;

        case '+':
        case '-':
        break;

        case '*':
        case '/':
        break;

        default:
            break;
        }

        printf("\n%c", *strexpressao);

        strexpressao++;
    }
    
}