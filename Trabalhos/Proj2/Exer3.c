#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct 
{
    int topo_operadores;
    char operadores[100][2];

    int topo_operandos;
    char operandos[100][5];

    int topo_posfixa;
    char posfixa[100][5];

}PilhaExpressoes;

void empilhar(PilhaExpressoes *expressoes, char *operandoOuoperador)
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
        
        strcpy(expressoes->operadores[expressoes->topo_operadores], operandoOuoperador);
        expressoes->topo_operadores +=1;
    }
    else
    {
        strcpy(expressoes->operandos[expressoes->topo_operandos], operandoOuoperador);
        expressoes->topo_operandos +=1;
    }
    
}

void fragmentarExpressao(char *str_expressao, PilhaExpressoes *expressoes)
{
    int i;

    char string_composta[5];
    int k = 0;

    for(i=0; i<strlen(str_expressao); i++)
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

    empilhar(expressoes, string_composta); // ultimo dado depois do for
    
}

int main()
{
    char expressao [] = "500 + 50 * ( 20 + 1 ) / 3 - 4 * 2"; 
    PilhaExpressoes pilha_expressao;

    pilha_expressao.topo_operadores = pilha_expressao.topo_operandos = pilha_expressao.topo_posfixa = 0;

    fragmentarExpressao(expressao, &pilha_expressao);

    printf("%s", pilha_expressao.operandos[0]);

    return 0;
}