/*
	Segunda quest�o referente a primeira avalia��o da discpina de Estrurura de dados I.

	Autores: Jo�o Carlos de Sousa F� && Vitor Jos� Ferreira dos Santos de Santana.

	Data de inicio da resolu��o deste exercicio: 10/05/2021

	Quest�o 2. Implementa��o dinamica

        O estacionamento Picoense cont�m uma �nica alameda que guarda at� 10 carros. Existe uma entrada e
        uma sa�da, de tal forma que quando um determinado carro entra ele fica no final da fila e o primeiro
        que chegou sempre fica pr�ximo a sa�da, ou seja, todas as vezes que um carro sai todos os outros
        devem ser manobrados um espa�o para frente. Fa�a um programa em C, onde o usu�rio entrar� com o
        n�mero da placa do carro e 'E' se estiver entrando no estacionamento e 'S' se estiver saindo do
        estacionamento. O programa deve emitir uma mensagem sempre que um carro entrar ou sair do
        estacionamento. Quando um carro chegar, a mensagem deve especificar se existe ou n�o vaga no
        estacionamento, esse n�o tiver vaga, simplesmente o carro vai embora, n�o existe fila de espera.
        Quando um carro sair, a mensagem dever� incluir o n�mero de vezes em que o carro foi manobrado
        para fora do estacionamento para permitir que outros carros sa�ssem, al�m de mostrar quantos carros
        foram manobrados para que ele sa�sse.
        Obs.: N�o se esque�a que todas as vezes que um carro vai sair os que est�o na frente devem ser
        manobrados para o final da fila, mas ao final os carros que estava na frente do carro que saiu devem
        continuar no mesmo lugar de antes, ou seja, todos os demais carros devem ir para o fim da fila, mas
        n�o deve ser contabilizado como manobra.

*/

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
// estruturas

typedef struct
{
    int placa;

}CarroInfo;


typedef struct aux
{
	CarroInfo carro;
	struct aux* proximo_carro;

}Carro,  *PontCarro; // mesma coisa que Carro * (ponteiro para um carro)

typedef struct
{
	PontCarro inicio;
	PontCarro fim;
    int maximo_de_carros;
    int total_de_carros_estacionados;

}FilaCarros;

// operc��es basicas de fila

int numeroDeCarrosFila(FilaCarros *fila_carros);
bool inserirCarroFila(FilaCarros *fila_carros, CarroInfo carro);
bool removerCarroFila(FilaCarros *fila_carros, CarroInfo *carro, int *movido);
void exibirCarrosFila(FilaCarros *fila_carros);
int buscar(FilaCarros *fila_carros, int placa);
void debug(FilaCarros *fila_carros);
int menu(int *op, FilaCarros *fila_de_carros);

int main()
{
    setlocale(LC_ALL, "");
    FilaCarros fila_de_carros;
    fila_de_carros.inicio = fila_de_carros.fim = NULL;
    fila_de_carros.maximo_de_carros = 10;
    fila_de_carros.total_de_carros_estacionados = 0;
    int op;
    //debug(&fila_de_carros);
    while(menu(&op, &fila_de_carros) != 0);

    return 0;
}

int menu(int *op, FilaCarros *fila_de_carros)
{
    char E_S;
    CarroInfo carro;

    int carros_movidos = 0;

    printf("\n0 - Sair do programa");
	printf("\n1 - Estacionamento");
    printf("\n2 - Mostrar fila de carros \n");
	printf(": "); scanf("%d", op);

    switch (*op)
    {
    case 1:
        printf("\nPlaca do Carro: "); scanf("%d", &carro.placa);
        printf("\nEntrar ou Sair do estacionamento: E - Entrar S - Sair: "); scanf(" %c", &E_S);

        if(E_S == 'E' || E_S == 'e')
        {
            if (fila_de_carros->total_de_carros_estacionados == fila_de_carros->maximo_de_carros)
                printf("\nFila de carros cheia...");
            else
            {
                inserirCarroFila(fila_de_carros, carro);

                fila_de_carros->total_de_carros_estacionados +=1;

                printf("\nCarro %d entrou na fila...", fila_de_carros->total_de_carros_estacionados);
            }

        }
        else if (E_S == 'S' || E_S == 's')
        {
          printf("ttese\n");
            int busca = buscar(fila_de_carros,carro.placa);
            removerCarroFila(fila_de_carros, &carro, &carros_movidos);
            printf("\nCarro com placa %d saiu do estacionamento...Total de vezes que foi manobrado: %d vezes", carro.placa, busca);
            printf("\nCarros manobrados %d carros\n", carros_movidos - busca);
        }
        else
            printf("\nOpera��o cancelada...");

        printf("\n");
        break;
    case 2:
        if(fila_de_carros->inicio == NULL)
            printf("\nFila vazia...");
        else
            exibirCarrosFila(fila_de_carros);

        printf("\n");
        break;
    default:
        break;
    }

    return *op;
}

int numeroDeCarrosFila(FilaCarros *fila_carros)
{
    PontCarro end = fila_carros->inicio;
    int contador = 0;

    while (end != NULL)
    {
        contador++;
        end = end->proximo_carro;
    }

    return contador;

}

bool inserirCarroFila(FilaCarros *fila_carros, CarroInfo carro)
{
    PontCarro novo_carro = (PontCarro) malloc(sizeof(Carro));

    if (novo_carro == NULL)
        return false;
    else
    {
        novo_carro->carro = carro;
        novo_carro->proximo_carro = NULL;

        if (fila_carros->inicio == NULL)
            fila_carros->inicio = novo_carro;
        else
            fila_carros->fim->proximo_carro = novo_carro;

        fila_carros->fim = novo_carro;

        return true;
    }

}

int buscar(FilaCarros *fila_carros, int placa)
{
  PontCarro end = fila_carros->inicio;
  int busca = 0;

  do
  {
    if(end->carro.placa == placa){
      break;
    }
    end = end->proximo_carro;
    busca++;
  }while(end != NULL);

  return busca;
}

bool removerCarroFila(FilaCarros *fila_carros, CarroInfo *carro,int *movido)
{
    if (fila_carros->inicio == NULL)
    {
        return false; // fila vazia
    }
    else
    {
        FilaCarros fila_carros_aux;
        fila_carros_aux.inicio = fila_carros_aux.fim = NULL;

        while (fila_carros->inicio != NULL)
        {
            if (fila_carros->inicio->carro.placa != carro->placa)
            {
                inserirCarroFila(&fila_carros_aux, fila_carros->inicio->carro);
                (*movido)++;
            }

            PontCarro apagar = fila_carros->inicio;

            fila_carros->inicio = fila_carros->inicio->proximo_carro;

            free(apagar);
        }

        fila_carros->fim = NULL; // fim passa tambem a apontar para null

        while (fila_carros_aux.inicio != NULL)
        {
            inserirCarroFila(fila_carros, fila_carros_aux.inicio->carro);

            PontCarro apagar = fila_carros_aux.inicio;

            fila_carros_aux.inicio = fila_carros_aux.inicio->proximo_carro;

            free (apagar);
        }

        return true;
    }
}

void exibirCarrosFila(FilaCarros *fila_carros)
{
    PontCarro end = fila_carros->inicio;
    int i = 1;

    while (end != NULL)
    {
        printf("\nCarro %d: %d", i, end->carro.placa);
        end = end->proximo_carro;
        i++;
    }
}

void debug(FilaCarros *fila_carros)
{
    CarroInfo carro;
    int mv = 0;

    carro.placa = 111;
    inserirCarroFila(fila_carros, carro);

    carro.placa = 222;
    inserirCarroFila(fila_carros, carro);

    carro.placa = 333;
    inserirCarroFila(fila_carros, carro);

    carro.placa = 444;
    inserirCarroFila(fila_carros, carro);

    exibirCarrosFila(fila_carros);

    printf("\n\nremovendo carro do inicio da fila...\n");
    removerCarroFila(fila_carros, &carro, & mv);
    exibirCarrosFila(fila_carros);
}
