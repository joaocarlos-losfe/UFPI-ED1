#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <locale.h>


typedef struct
{
	int placa;

} Carro;

#define M 10

typedef struct
{
	Carro carros[10];
	int fim;
	
} Fila;


bool filaVazia(Fila *fila)
{
	bool vazia = false;

	if(fila->fim == 0)
		vazia = true;

	return vazia;
}

bool filaCheia(Fila *fila)
{
	bool cheia = false;

	if(fila->fim == M)
		cheia = true;

	return cheia;
}

void inserir(Fila *fila, Carro carro)
{
	if(!filaCheia(fila))
	{
		int i = fila->fim;
		fila->carros[i] = carro;
		fila->fim += 1;
	}
	else
	{
		printf("\nFila cheia !!");
	}
}



void exibirFila(Fila *fila)
{
	if(!filaVazia(fila))
	{
		int i;
		int p = 1;

		for(i = 0; i < fila->fim; i++)
		{
			printf("\nCarro %d placa: %d", p, fila->carros[i].placa);
			p++;
		}
	}
	else
	{
		printf("\nFila vazia");
	}
}

void remover(Fila *fila, Carro *carro)
{
	if(!filaVazia(fila))
	{
		int removidos = 0;
		int i;
		
		*carro = fila->carros[0];

		for(i = 0; i < fila->fim; i++)
		{
			fila->carros[i] = fila->carros[i + 1];
			removidos += 1;
		}

		fila->fim = removidos - 1;
	}
	else
	{
		printf("\nFila vazia !!");
	}
	
}

bool manobrarCarroPraFora(Fila *fila, int *total_sairam, int *total_manobrados, int placa)
{
	bool carro_saiu = false;
	*total_sairam = 0;
	*total_manobrados = 0;
	
	Fila fila_temp; fila_temp.fim = 0;
	
	Carro carro;
	
	while(!filaVazia(fila))
	{
		if(placa != fila->carros[0].placa && carro_saiu != true)
		{
			*total_sairam+=1;
		}
		else
		{
			carro_saiu = true;
		}
		
		remover(fila, &carro);
		
		if(carro.placa != placa)
			inserir(&fila_temp, carro);
	}
	
	*total_manobrados = fila_temp.fim - *total_sairam;
	
	exibirFila(&fila_temp);
	
	return carro_saiu;
}

void debug(Fila *fila)
{
	Carro carro;
	carro.placa = 111;
	inserir(fila, carro);

	carro.placa = 222;
	inserir(fila, carro);

	carro.placa = 333;
	inserir(fila, carro);
	
	carro.placa = 444;
	inserir(fila, carro);
	
	carro.placa = 555;
	inserir(fila, carro);
	
	carro.placa = 666;
	inserir(fila, carro);
	
	carro.placa = 777;
	inserir(fila, carro);
	
	carro.placa = 888;
	inserir(fila, carro);
	
	carro.placa = 999;
	inserir(fila, carro);
	
	
	//exibirFila(fila);
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
    Fila fila_carros;

	fila_carros.fim = 0;

	debug(&fila_carros);
	
	int total_sairam = 0;
	int total_manobrados = 0;
	
	bool saiu = false;
	saiu = manobrarCarroPraFora(&fila_carros, &total_sairam, &total_manobrados, 444);
	
	if(saiu)
		printf("\nTotal sairam da frente: %d. total manobrados: %d", total_sairam, total_manobrados);
	else
		printf("\nCarro não encontrado...");
	
	return 0;
}
