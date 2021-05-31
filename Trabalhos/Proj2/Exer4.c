#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>
#include <stdbool.h>

// estrutura basica dos dados

typedef struct aux
{
    char elemento_expressao[10];
    struct aux* proximo_abaixo;

}ElementoOperandoOperador, *PontElementoOperandoOperador;

typedef struct
{
    PontElementoOperandoOperador topo;

}Pilha;

//opera��es basicas de pilha

void inicializarPilha(Pilha *pilha)
{
    pilha->topo = NULL;
}

bool vazia(Pilha *pilha)
{
    if(pilha->topo == NULL)
        return true;
    else
        return false;
}

void exibir(Pilha *pilha)
{
    if (!vazia(pilha))
    {
        PontElementoOperandoOperador end_topo = pilha->topo;
        printf("\n");
        while (end_topo!=NULL)
        {
            printf("%s ", end_topo->elemento_expressao);
            end_topo = end_topo->proximo_abaixo;
        }
        printf("\n");
    }
}

void empilhar(Pilha *pilha, char *elemento_expressao)
{
    PontElementoOperandoOperador novo_elemento_expressao = (PontElementoOperandoOperador) malloc(sizeof(ElementoOperandoOperador));
    strcpy(novo_elemento_expressao->elemento_expressao, elemento_expressao);
    novo_elemento_expressao->proximo_abaixo = pilha->topo;
    pilha->topo = novo_elemento_expressao;

}

bool desempilhar(Pilha *pilha, char *temp_elemento_expressao)
{
    if (!vazia(pilha))
    {
        strcpy(temp_elemento_expressao, pilha->topo->elemento_expressao);
        PontElementoOperandoOperador apagar_end = pilha->topo;
        pilha->topo = pilha->topo->proximo_abaixo;
        free(apagar_end);
        return true;
    }
    else
        return false;

}

void inverterPilha(Pilha *pilha)
{
    if(!vazia(pilha))
    {
        Pilha pilha_temp; inicializarPilha(&pilha_temp);
        char temp_elemento_expressao[10];

        while (!vazia(pilha))
        {
            desempilhar(pilha, temp_elemento_expressao);
            empilhar(&pilha_temp, temp_elemento_expressao);
        }

        pilha->topo = pilha_temp.topo;

    }
}

// fun��es para compor a posfixa

void fragmentarString(char *str, Pilha *pilha)
{
    char str_composta[10];
    int i = 0;

    strcat(str, " ");

    while (*str!= '\0')
    {
        if(*str != ' ')
        {
            str_composta[i] = *str;
            i++;
        }
        else
        {
            str_composta[i] = '\0';
            i = 0;

            empilhar(pilha, str_composta);
        }

        str++;
    }
}

bool ehOperador(char *str)
{
    bool eh_operador = false;
    switch (*str)
    {
    case '+':
    case '-':
    case '*':
    case '/':
    case '(':
    case ')':
        eh_operador = true;
        break;
    default:
        break;
    }

    return eh_operador;
}

int prioridade(char *str)
{
    int prioridade = 0;
    switch (*str)
    {
    case '+':
    case '-':
        prioridade = 2;
        break;
    case '*':
    case '/':
        prioridade = 3;
        break;
    case '(':
    case ')':
        prioridade = 1;
        break;
    }

    return prioridade;
}

void converterPosfixa(Pilha *pilha_operando_operador, Pilha *pilha_operadores, Pilha *pilha_pos_fixa)
{
    inverterPilha(pilha_operando_operador);
    exibir(pilha_operando_operador);

    while (!vazia(pilha_operando_operador))
    {
        if (!ehOperador(pilha_operando_operador->topo->elemento_expressao))
        {
            empilhar(pilha_pos_fixa, pilha_operando_operador->topo->elemento_expressao);
        }
        else if(pilha_operando_operador->topo->elemento_expressao[0] == '(')
        {
            empilhar(pilha_operadores, pilha_operando_operador->topo->elemento_expressao);
        }
        else if (pilha_operando_operador->topo->elemento_expressao[0] == ')')
        {
            char operador[10];

            desempilhar(pilha_operadores, operador);

            while (strcmp(operador, "(") != 0 && !vazia(pilha_operando_operador))
            {
                empilhar(pilha_pos_fixa, operador);
                desempilhar(pilha_operadores, operador);
            }
        }
        else
        {
            char temp_elemento_expressao[10];
            while (!vazia(pilha_operadores) &&
            prioridade(pilha_operadores->topo->elemento_expressao) >=
            prioridade(pilha_operando_operador->topo->elemento_expressao))
            {
                desempilhar(pilha_operadores, temp_elemento_expressao);
                empilhar(pilha_pos_fixa, temp_elemento_expressao);
            }

            empilhar(pilha_operadores, pilha_operando_operador->topo->elemento_expressao);

        }

        pilha_operando_operador->topo = pilha_operando_operador->topo->proximo_abaixo;
    }

    while (!vazia(pilha_operadores))
    {
        char temp_elemento[5];
        desempilhar(pilha_operadores, temp_elemento);
        empilhar(pilha_pos_fixa, temp_elemento);
    }

    inverterPilha(pilha_pos_fixa);

}


bool expressaoValida(char *str, Pilha *pilha, int *qtdParenteseAberto, int *qtdParentesefechado)
{
    bool valida  = true;

    if (str[0] == '(')
        *qtdParenteseAberto +=1;
    else if (str[0] == ')')
        *qtdParentesefechado +=1;

    if (ehOperador(str) && ehOperador(pilha->topo->elemento_expressao) && str[0] != '(')
        valida = false;


    return valida;
}

int main()
{
    Pilha pilha_operando_operador; inicializarPilha(&pilha_operando_operador);
    Pilha pilha_operadores; inicializarPilha(&pilha_operadores);
    Pilha pilha_pos_fixa; inicializarPilha(&pilha_pos_fixa);

    int qtdParenteseAberto = 0;
    int qtdParentesefechado = 0;
    char expressao[100];
    bool s;

    do{
      printf("\nDigite a express�o: ");
      scanf(" %[^\n]s", expressao);
      strcat(expressao, " ");

      s = expressaoValida(expressao,&pilha_operando_operador,&qtdParenteseAberto,&qtdParentesefechado);

      if(s == false)
        printf("Expressão Invalida\nDigite uma expressão válida\n");

    }while(s == false);


    fragmentarString(expressao, &pilha_operando_operador);

    converterPosfixa(&pilha_operando_operador, &pilha_operadores, &pilha_pos_fixa);

    exibir(&pilha_pos_fixa);
    return 0;
}
