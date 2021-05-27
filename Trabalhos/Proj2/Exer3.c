#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct 
{
    int topo_dados;
    char dados[100][5];

}PilhaExpressoes;

void empilhar(PilhaExpressoes *expressoes, char *str)
{
    strcpy(expressoes->dados[expressoes->topo_dados], str);
    expressoes->topo_dados += 1;
}

void inverterPilha(PilhaExpressoes *expressoes)
{
    PilhaExpressoes expressoes_temp;
    expressoes_temp.topo_dados = 0;

    int i=0;

    for(i= expressoes->topo_dados-1; i>=0; i--)
    {
        empilhar(&expressoes_temp, expressoes->dados[i]);
    }

    *expressoes = expressoes_temp;

}

void exibirpilha(PilhaExpressoes *expressoes)
{
    int i=0;

    for(i=expressoes->topo_dados -1; i>=0; i--)
    {
        printf("\n %s", expressoes->dados[i]);
    }
}

bool ehOperador(char *operandoOuoperador)
{
    if
    (
        strcmp(operandoOuoperador, "+") == 0  || 
        strcmp(operandoOuoperador, "-") == 0  || 
        strcmp(operandoOuoperador, "*") == 0  || 
        strcmp(operandoOuoperador, "/") == 0  ||
        strcmp(operandoOuoperador, "(") == 0  ||
        strcmp(operandoOuoperador, ")") == 0
    ) 
    {
        
        return true;
    }
    else
    {
        return false;
    }
    
}

void fragmentarExpressao(char *str_expressao, PilhaExpressoes *expressoes)
{
    int i;

    char string_composta[5];
    int k = 0;

    for(i=0; i<=strlen(str_expressao); i++)
    {
        if(str_expressao[i] != ' ')
        {
            string_composta[k] = str_expressao[i];
            k++;
        }
        else
        {
            string_composta[k] = '\0';
            k = 0;
            empilhar(expressoes, string_composta);
        }
    }
    empilhar(expressoes, string_composta);
}

int main()
{
    char expressao [] = "500 + 50 * ( 20 + 1 ) / 3 - 4 * 2"; 
    PilhaExpressoes pilha_expressao;
    pilha_expressao.topo_dados = 0;

    fragmentarExpressao(expressao, &pilha_expressao);
    inverterPilha(&pilha_expressao);

    exibirpilha(&pilha_expressao);

    return 0;
}