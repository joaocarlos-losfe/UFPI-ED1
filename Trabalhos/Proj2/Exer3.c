#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <malloc.h>
#include <locale.h>

typedef struct 
{
    char expressao[50][100];
    int topo;

}Expressao;

typedef struct 
{
    char operadores[50];
    int topo;

}Operadores;

typedef struct 
{
    int valores[50];
    int topo;

}Valores;

void menu();
void empilhar(char *str, Expressao *pilha);

int main()
{
    setlocale(LC_ALL,"");

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
            setbuf(stdin, NULL);
            printf("\ndigite uma expressão: ");
            scanf("%[^\n]s", strexpressao);
            empilhar(strexpressao, &expressao);
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
    printf("\n2 - mostrar expressão");
    printf("\n3 - converter para pos fixa\n: ");
}

void empilhar(char *str, Expressao *pilha)
{
    char str_valor[5];
    int i=0;

    Operadores operadores;
    operadores.topo = 0;

    Valores valores;
    valores.topo = 0;

    while (*str!= '\0')
    {
        if(*str != ' ')
        {
            str_valor[i] = *str;
            i++;
        }
        else
        {
            str_valor[i] = '\0';
            i = 0;
            
            switch (str_valor[0])
            {
                case '+':
                case '-':
                case '*':
                case '/':
                case '(':
                case ')': operadores.operadores[operadores.topo] = str_valor[0];
                operadores.topo ++;
                break;

                default:
                    valores.valores[valores.topo] = atoi(str_valor);
                    valores.topo++;
                break;
            }
 
        }

        ++str;
    }
    
    valores.valores[valores.topo] = atoi(str_valor);
    valores.topo++;

    printf("\nmostrando as expressoes...\n");

 
    for(i=operadores.topo -1; i>=0; i--)
    {
        printf("\n%c", operadores.operadores[i]);
    }

    printf("\nmostrando os valores...\n");

    for(i=valores.topo -1; i>=0; i--)
    {
        printf("\n%d", valores.valores[i]);
    }

}