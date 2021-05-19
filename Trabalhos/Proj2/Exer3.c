#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <locale.h>

#define max 100

typedef struct 
{
    int topo;
    char expressoes[max][5];  // 100 dados com maximo de 5 caractres

}PilhaExpressoes;

typedef struct 
{
    int topo;
    char operadores[max];

}PilhaOperadores;

typedef struct 
{
    int topo;
    int valores[max];

}PilhaValores;


void menu();
void extrairDadosExpressao(PilhaExpressoes *pilha_expressoes, char *strexpressao);
bool empilharExpressoes(PilhaExpressoes *pilha_expressoes, char *strexpressao);
void mostrarPilhaExpressoes(PilhaExpressoes *pilha_expressoes);

void distribuirDados(PilhaExpressoes *pilha_expressoes, PilhaOperadores *pilha_operadores, PilhaValores *pilha_valores);

int main()
{
    setlocale(LC_ALL, "Portuguese");
    printf("João Carlos de Sousa Fé");

    PilhaExpressoes pilha_expressoes; pilha_expressoes.topo = 0;
    PilhaOperadores pilha_operadores; pilha_operadores.topo = 0;
    PilhaValores pilha_valores; pilha_valores.topo = 0;

    char expressao[] = "50 + 5 * 10 / 3 + ( ( 4 + 1 ) * 2 ) + 40 - 3 * 10 + 5 * ( 4 + 1 )";

    printf("\n%s\n", expressao);

    extrairDadosExpressao(&pilha_expressoes, expressao);
    //mostrarPilhaExpressoes(&pilha_expressoes);

    distribuirDados(&pilha_expressoes, &pilha_operadores, &pilha_valores);

    return 0;
}

void distribuirDados(PilhaExpressoes *pilha_expressoes, PilhaOperadores *pilha_operadores, PilhaValores *pilha_valores)
{
    pilha_expressoes->topo -=1;

    while (pilha_expressoes->topo >= 0)
    {
        switch (pilha_expressoes->expressoes[pilha_expressoes->topo][0]) // se o caractere da string ja inicia com olguma expressÃ£o
        {
        case '+':
        case '-':
        case '*':
        case '/':
        case '(':
        case ')':
            pilha_operadores->operadores[pilha_operadores->topo] = pilha_expressoes->expressoes[pilha_expressoes->topo][0];
            pilha_operadores->topo+=1;
            break;
        
        default:
            pilha_valores->valores[pilha_valores->topo] = atoi(pilha_expressoes->expressoes[pilha_expressoes->topo]);
            pilha_valores->topo+=1;
            break;
        }

        pilha_expressoes->topo -=1;
    }

    int i=0, j = 0;

    printf("\n");

    char temp_str[10];

    for(i= (pilha_valores->topo -1); i>=0; i--)
    {
        printf("%d ", pilha_valores->valores[i]);

    }

    printf("  ");
    for(i= (pilha_operadores->topo -1); i>=0; i--)
    {
        printf("%c ", pilha_operadores->operadores[i]);
        
    }
}

void extrairDadosExpressao(PilhaExpressoes *pilha_expressoes, char *strexpressao)
{
    char temp_str[5];
    int i, j = 0;

    for (i=0; i<strlen(strexpressao); i++)
    {
        if(strexpressao[i] != ' ')
        {
            temp_str[j] = strexpressao[i];
            j++;
        }
        else
        {
            temp_str[j] = '\0'; //fecha com o \0 para definir uma string
            j = 0;
            empilharExpressoes(pilha_expressoes, temp_str); // empilha a string temporaria
        }
    }

    empilharExpressoes(pilha_expressoes, temp_str); 
}

bool empilharExpressoes(PilhaExpressoes *pilha_expressoes, char *strexpressao)
{
    if(pilha_expressoes->topo != max)
    {
        strcpy(pilha_expressoes->expressoes[pilha_expressoes->topo], strexpressao);
        pilha_expressoes->topo++;
        return true;
    }

    return false;
}

void mostrarPilhaExpressoes(PilhaExpressoes *pilha_expressoes)
{
    int i;

    for(i = (pilha_expressoes->topo - 1); i>=0; i--)
    {
        printf("%s ", pilha_expressoes->expressoes[i]);
    }
}
