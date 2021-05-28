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

char* desempilhar(PilhaExpressoes *expressoes)
{
    expressoes->topo_dados -=1;

    return expressoes->dados[expressoes->topo_dados];
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
        printf("%s ", expressoes->dados[i]);
    }
}

bool ehOperador(char *operandoOuoperador)
{
    switch (operandoOuoperador[0])
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
    return true;
        break;
    default:
    return false;
        break;
    }   
}

void fragmentarExpressaoStr(char *str_expressao, PilhaExpressoes *expressoes)
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

int pesoOperadores(char *str)
{
    int peso;
    switch (str[0])
    {
    case '*':
    case '/':
        peso = 3;
        break;

    case '+':
    case '-':
        peso = 2;
        break;

    case '(':
        peso = 1;
        break;
    }

    return peso;
}

void examinarExpressao(PilhaExpressoes *expressoes, PilhaExpressoes *operadores, PilhaExpressoes *saida)
{
    int i = 0;

    for(i=expressoes->topo_dados-1; i>0; i--)
    {
        if(!ehOperador(expressoes->dados[i]))
        {
            empilhar(saida, expressoes->dados[i]);
            printf("\n dado[i] no ehoperador: %s", expressoes->dados[i]);
        }
        else if (expressoes->dados[i][0] == '(')
        {
            empilhar(operadores, expressoes->dados[i]);
            printf("\n se a expressão for (: %s", expressoes->dados[i]);
        }
        else if (expressoes->dados[i][0] == ')')
        {
            char *operador = desempilhar(operadores); // retornando uma string
            printf("\nse a expressão for ): operador:  %s", operador);

            while (strcmp(operador, "(") != 0 && expressoes->topo_dados >0)
            {
                empilhar(saida, operador);
                operador = desempilhar(operadores); //facila a comparação
                printf("\nDado do operador desempilhado: %s", operador);
            }
            
        }
        else
        {
            while (operadores->topo_dados > 0 && 
            pesoOperadores( operadores->dados[operadores->topo_dados-1]) >= 
            pesoOperadores(expressoes->dados[i]))
            {
                empilhar(saida, desempilhar(operadores));
            }

            empilhar(operadores, expressoes->dados[i]);
        }
    }

    
    while (operadores->topo_dados > 0)
    {
        empilhar(saida, desempilhar(operadores));
    }
    
}

int main()
{
    char expressao [] = "1 * 3 + 4 "; 
    PilhaExpressoes pilha_expressao;
    pilha_expressao.topo_dados = 0;

    PilhaExpressoes operadores; operadores.topo_dados = 0;

    PilhaExpressoes saida; saida.topo_dados = 0;

    fragmentarExpressaoStr(expressao, &pilha_expressao);
    inverterPilha(&pilha_expressao);
    //exibirpilha(&pilha_expressao);

    examinarExpressao(&pilha_expressao, &operadores, &saida);

    printf("\n\n");
    inverterPilha(&saida);
    exibirpilha(&saida);


    return 0;
}