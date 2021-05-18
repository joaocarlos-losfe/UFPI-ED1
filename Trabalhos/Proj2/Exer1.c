#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define NCARRO 3

typedef struct 
{
    int placa;

}Carro;

typedef struct 
{
    int inicio, fim;
    Carro carros[NCARRO];

}FilaCarro;

void menu();

bool cadastro(FilaCarro *fila_de_carros, Carro carro);
void imprimir(FilaCarro *fila_de_carros);
int buscar(FilaCarro *fila_de_carros, int placa);
void manobrar(FilaCarro *fila_de_carros, int placa);
bool filaVazia(FilaCarro *fila_de_carros);
bool filacheia(FilaCarro *fila_de_carros);

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FilaCarro fila_de_carros;
    fila_de_carros.inicio = 0;
    fila_de_carros.fim = 0;
    Carro carro;
    char E_S;
    int op;
    do
    {
        menu();
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            printf("\nPlaca do carro: ");
            scanf("%d", &carro.placa);
            printf("\nEstacionar ou Sair? E - Estacionar, S - Sair: ");
            scanf(" %c", &E_S);
            
            if(E_S == 'E')
            {
                if(buscar(&fila_de_carros, carro.placa) == -1)
                {
                    if(cadastro(&fila_de_carros, carro) == true)
                        printf("\nCarro inserido na fila...");
                    else
                        printf("\nFila cheia...");
                }
                else
                    printf("\nja existe um carro com essa placa na fila...");
            }
            else if(E_S == 'S')
            {
                int busca = buscar(&fila_de_carros, carro.placa);

                if (busca != -1)
                {
                    manobrar(&fila_de_carros, carro.placa);
                    printf("\nCarro com placa %d saiu do estacionamento...Total de vezes que foi manobrado: %d vezes", carro.placa, busca+1);
                }
                else
                    printf("\ncarro não se encontra no estacionamento...");
            }
            break;
        case 2:
            imprimir(&fila_de_carros);
            break;
        default:
            break;
        }
        
    } while (op != 0);
    

    return 0;
}

void menu()
{
	printf("\n[0] - Sair do programa\n");
	printf("[1] - Estacionamento\n");
    printf("[2] - Imprimir\n");
	printf(": ");
}

bool cadastro(FilaCarro *fila_de_carros, Carro carro)
{
    bool foi_inserido = false;

    if(fila_de_carros->fim == NCARRO)
    {
        return false;
    }
    else
    {
        fila_de_carros->carros[fila_de_carros->fim] = carro;
        fila_de_carros->fim +=1;
    }
    return true;
}

void imprimir(FilaCarro *fila_de_carros)
{
    unsigned int i=0;

    for(i=0; i<fila_de_carros->fim; i++)
    {
        printf("\n%d", fila_de_carros->carros[i]);
    }
}

int buscar(FilaCarro *fila_de_carros, int placa)
{
    int i = 0;
    int busca = -1;

    for (i= fila_de_carros->inicio; i<fila_de_carros->fim; i++)
    {
        if(placa == fila_de_carros->carros[i].placa)
        {
            busca = i;
            break;
        }
    }

    return busca;    
}

void manobrar(FilaCarro *fila_de_carros, int placa)
{
    FilaCarro fila_de_carros_aux;
    fila_de_carros_aux.inicio = 0;
    fila_de_carros_aux.fim = 0;

    while (fila_de_carros->inicio != fila_de_carros->fim)
    {
        if(placa != fila_de_carros->carros[fila_de_carros->inicio].placa)
            cadastro(&fila_de_carros_aux, fila_de_carros->carros[fila_de_carros->inicio]);

        fila_de_carros->inicio +=1;
    }

    fila_de_carros->inicio = 0;
    fila_de_carros->fim = 0;

    while (fila_de_carros_aux.inicio != fila_de_carros_aux.fim)
    {
        cadastro(fila_de_carros, fila_de_carros_aux.carros[fila_de_carros_aux.inicio]);
        fila_de_carros_aux.inicio +=1;
    }
    
}