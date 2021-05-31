/*
	Segunda questão referente a primeira avaliação da discpina de Estrurura de dados I.

	Autores: João Carlos de Sousa Fé && Vitor José Ferreira dos Santos de Santana.

	Data de inicio da resolução deste exercicio: 10/05/2021

	Questão 2. Implementação dinamica
    
        O estacionamento Picoense contém uma única alameda que guarda até 10 carros. Existe uma entrada e 
        uma saída, de tal forma que quando um determinado carro entra ele fica no final da fila e o primeiro 
        que chegou sempre fica próximo a saída, ou seja, todas as vezes que um carro sai todos os outros 
        devem ser manobrados um espaço para frente. Faça um programa em C, onde o usuário entrará com o 
        número da placa do carro e 'E' se estiver entrando no estacionamento e 'S' se estiver saindo do 
        estacionamento. O programa deve emitir uma mensagem sempre que um carro entrar ou sair do 
        estacionamento. Quando um carro chegar, a mensagem deve especificar se existe ou não vaga no 
        estacionamento, esse não tiver vaga, simplesmente o carro vai embora, não existe fila de espera. 
        Quando um carro sair, a mensagem deverá incluir o número de vezes em que o carro foi manobrado 
        para fora do estacionamento para permitir que outros carros saíssem, além de mostrar quantos carros 
        foram manobrados para que ele saísse.
        Obs.: Não se esqueça que todas as vezes que um carro vai sair os que estão na frente devem ser 
        manobrados para o final da fila, mas ao final os carros que estava na frente do carro que saiu devem 
        continuar no mesmo lugar de antes, ou seja, todos os demais carros devem ir para o fim da fila, mas 
        não deve ser contabilizado como manobra.
    
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

// opercções basicas de fila

int numeroDeCarrosFila(FilaCarros *fila_carros);
bool inserirCarroFila(FilaCarros *fila_carros, CarroInfo carro);
bool removerCarroFila(FilaCarros *fila_carros, CarroInfo *carro);
void exibirCarrosFila(FilaCarros *fila_carros);

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
            removerCarroFila(fila_de_carros, &carro);
        }
        else
            printf("\nOperação cancelada...");
        
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

bool removerCarroFila(FilaCarros *fila_carros, CarroInfo *carro)
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
    removerCarroFila(fila_carros, &carro);
    exibirCarrosFila(fila_carros);
}
