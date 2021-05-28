#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

typedef struct 
{
    int topo;
    char dados[100][5];

}Pilha;

void empilhar(Pilha *expressoes, char *str)
{
    strcpy(expressoes->dados[expressoes->topo], str);
    expressoes->topo += 1;
}

char* desempilhar(Pilha *expressoes)
{
    expressoes->topo -=1;

    return expressoes->dados[expressoes->topo];
}

bool vazia(Pilha *expressoes)
{
    if (expressoes->topo > 0)
        return false;
    else
        return true;
}

void inverterPilha(Pilha *expressoes)
{
    Pilha expressoes_temp;
    expressoes_temp.topo = 0;

    int i=0;

    for(i= expressoes->topo-1; i>=0; i--)
    {
        empilhar(&expressoes_temp, expressoes->dados[i]);
    }

    *expressoes = expressoes_temp;

}

void exibirpilha(Pilha *expressoes)
{
    int i=0;

    for(i=expressoes->topo -1; i>=0; i--)
    {
        printf("%s ", expressoes->dados[i]);
    }
}

char * dadoTopo(Pilha *pilha)
{
    return pilha->dados[pilha->topo-1];
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

bool expressaoValida(Pilha *pilha, char *str, int *QtdAbreparenteses, int *QtdFechaparenteses)
{
    bool valida = true;

    if (!isalpha(*str) || !ehOperador(str) )
    {
        valida = false;
    }
    else if (str[0] == '(' || str[0] == ')')
    {
        if (str[0] == '(')
            *QtdAbreparenteses +=1;
        else if (str[0] == ')')
            *QtdFechaparenteses +=1;
    }
}

bool fragmentarStringEmPilha(char *str_expressao, Pilha *expressoes)
{
    int i;

    char string_composta[5];
    int k = 0;

    int QtdAbreparenteses = 0, QtdFechaparenteses = 0;

    bool expressao_valida = false;

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
            expressao_valida = expressaoValida(expressoes, string_composta, &QtdAbreparenteses, &QtdFechaparenteses);
            if(expressao_valida)
                empilhar(expressoes, string_composta);
            else
            {
                break;
            }
        }
    }
    empilhar(expressoes, string_composta);

    if (QtdAbreparenteses != QtdFechaparenteses)
        expressao_valida = false;

    return expressao_valida;
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
    case ')':
        peso = 1;
        break;
    }

    return peso;
}

void converterPosfixa(Pilha *expressoes, Pilha *operadores, Pilha *pilha_pos_fixa)
{
    int i = 0;

    for(i=expressoes->topo-1; i>0; i--)
    {
        if(!ehOperador(expressoes->dados[i]))
        {
            empilhar(pilha_pos_fixa, expressoes->dados[i]);
        }
        else if (expressoes->dados[i][0] == '(')
        {
            empilhar(operadores, expressoes->dados[i]);
        }
        else if (expressoes->dados[i][0] == ')')
        {
            char *operador = desempilhar(operadores); // retornando uma string
            
            while (strcmp(operador, "(") != 0 && !vazia(expressoes))
            {
                empilhar(pilha_pos_fixa, operador);
                operador = desempilhar(operadores); //facila a comparação
            }
        }
        else
        {
            while (!vazia(operadores) && 
            pesoOperadores(operadores->dados[operadores->topo-1]) >= 
            pesoOperadores(expressoes->dados[i]))
            {
                empilhar(pilha_pos_fixa, desempilhar(operadores));
            }

            empilhar(operadores, expressoes->dados[i]);
        }
    }

    while (!vazia(operadores))
    {
        empilhar(pilha_pos_fixa, desempilhar(operadores));
    }

}

int main()
{
    setlocale(LC_ALL, "");

    Pilha pilha_expressao;
    pilha_expressao.topo = 0;

    Pilha operadores; operadores.topo = 0;

    Pilha pilha_pos_fixa; pilha_pos_fixa.topo = 0;

    char expressao[100];
    printf("\nDigite a expressão: "); scanf(" %[^\n]s", expressao);
    strcat(expressao, " ");

    if(fragmentarStringEmPilha(expressao, &pilha_expressao) == true)
    {
        inverterPilha(&pilha_expressao);
        converterPosfixa(&pilha_expressao, &operadores, &pilha_pos_fixa);
        inverterPilha(&pilha_pos_fixa);
        printf("\nExpressão posfixa: ");
        exibirpilha(&pilha_pos_fixa);
    }
    else
    {
        printf("\nExpressão invalida !");
    }
   

    return 0;
}