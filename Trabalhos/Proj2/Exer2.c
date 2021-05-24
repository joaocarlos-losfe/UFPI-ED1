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

}FilaCarros;

// opercções basicas de fila

int numeroDeCarrosFila(FilaCarros *fila_carros);
bool inserirCarroFila(FilaCarros *fila_carros, CarroInfo carro);
bool removerCarroFila(FilaCarros *fila_carros, CarroInfo *carro);
void exibirCarrosFila(FilaCarros *fila_carros);

void debug(FilaCarros *fila_carros);

int main()
{
    FilaCarros fila_de_carros;
    fila_de_carros.inicio = fila_de_carros.fim = NULL;

    debug(&fila_de_carros);

    return 0;
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
        *carro = fila_carros->inicio->carro; // salvar o carro que se quer excluir para poder fazer algo posteriormente

        PontCarro carro_remover = fila_carros->inicio; // guarda o endereço para quem inicio apontava para posterior exclusão

        fila_carros->inicio = fila_carros->inicio->proximo_carro; // inicio passa a apontar para o proximo carro

        free(carro_remover); // libera mememoria do inicio salva anteriormente 

        if (fila_carros->inicio == NULL) // se não tiver nenhum dado apontado por inicio
            fila_carros->fim = NULL; // fim passa tambem a apontar para null

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
