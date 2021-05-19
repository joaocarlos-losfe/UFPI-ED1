#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

#define NCARRO 10 //qunatidade maxima de carros permitidada na fila

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
void manobrar(FilaCarro *fila_de_carros, int placa, int *contador);
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
    int contador = 0; /* Faz a contagem dos carros para a fila auxiliar*/
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
            scanf(" %c", &E_S); //Estacionar ou Sair

            if(E_S == 'E' || E_S == 'e')
            {
                if(buscar(&fila_de_carros, carro.placa) == -1) // se retorna -1, significa que não encontrou
                {
                    if(cadastro(&fila_de_carros, carro) == true) // retorna true se a fila ainda tem vaga
                        printf("\nCarro inserido na fila...");
                    else
                        printf("\nFila cheia...");
                }
                else
                    printf("\nja existe um carro com essa placa na fila...");
            }
            else if(E_S == 'S' || E_S == 's') // sair da fila
            {
                int busca = buscar(&fila_de_carros, carro.placa);

                if (busca != -1)
                {
                    manobrar(&fila_de_carros, carro.placa,&contador); //retira o carro da fina
                    printf("\nCarro com placa %d saiu do estacionamento...Total de vezes que foi manobrado: %d vezes", carro.placa, busca+1);
                    printf("\nPara o carro sair foi preciso manobrar %d carros\n",contador - 1);
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

    if(fila_de_carros->fim == NCARRO) // verifica se a quantidade "fim" da fila é igual ao numero de carros permitido
    {
        return false; //não é possivel inserir mais carros
    }
    else
    {
        fila_de_carros->carros[fila_de_carros->fim] = carro; //insere o carro no fim da fila
        fila_de_carros->fim +=1; //deixa uma vaga disponivel
    }
    return true; // o carro foi inserido com sucesso
}

void imprimir(FilaCarro *fila_de_carros)
{
    int i=0;

    for(i=0; i<fila_de_carros->fim; i++)
    {
        printf("\n%d", fila_de_carros->carros[i].placa); // imprime os carros na posição da fila
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
            busca = i; // guarda a posição do carro na fila
            break;
        }
    }

    return busca; // se retorna -1, nenhum carro foi encontrado. se não for encontrado, retorna a posição do carro na fila
}

void manobrar(FilaCarro *fila_de_carros, int placa, int *contador)
{
    FilaCarro fila_de_carros_aux;
    fila_de_carros_aux.inicio = 0;
    fila_de_carros_aux.fim = 0;

    while (fila_de_carros->inicio != fila_de_carros->fim)
    {
        if(placa != fila_de_carros->carros[fila_de_carros->inicio].placa)
            cadastro(&fila_de_carros_aux, fila_de_carros->carros[fila_de_carros->inicio]); // move os carros temporariamente para outra fila caso a placa seja diferente
            (*contador)++;
        fila_de_carros->inicio +=1; //retira o carro do inicio da fila
    }

    fila_de_carros->inicio = 0;
    fila_de_carros->fim = 0;

    while (fila_de_carros_aux.inicio != fila_de_carros_aux.fim) //insere de volta na fila horiginal
    {
        cadastro(fila_de_carros, fila_de_carros_aux.carros[fila_de_carros_aux.inicio]);
        fila_de_carros_aux.inicio +=1;
    }

}
