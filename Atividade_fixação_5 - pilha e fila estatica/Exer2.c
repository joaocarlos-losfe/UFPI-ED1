#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <stdbool.h>

#define max 4

typedef struct
{
	char chassi[30];
	int placa;
	char modelo[30];
	char marca[15];
	char cor[15];
	int ano_fabricacao;

} Carro;

typedef struct
{
	int in, fn; //inicio e fim
	Carro carros[max];

} FilaCarros;

void inserirCarroNaFila(FilaCarros *fila_de_carros, Carro carro)
{
	if(fila_de_carros->fn == max - 1)
	{
		printf("\n fila cheia");
	}
	else
	{
		fila_de_carros->carros[fila_de_carros->fn] = carro;
		fila_de_carros->fn += 1;
	}

}

void imprimirCarros(FilaCarros *fila_de_carros)
{
	int i;
	int count = 0;
	if((fila_de_carros->fn == 0 && fila_de_carros->in == 0) || (fila_de_carros->fn  == fila_de_carros->in ) )
	{
		printf("\nnenhum carro inserido\n");
	}
	else
	{
		printf("\nTotal de carros na fila: %d\n", fila_de_carros->fn);

		for(i = fila_de_carros->in; i < fila_de_carros->fn; i++)
		{
			printf("\nCarro %d \n", count + 1);
			printf("\n%s", fila_de_carros->carros[i].chassi);
			printf("\n%d", fila_de_carros->carros[i].placa);
			printf("\n%s", fila_de_carros->carros[i].modelo);
			printf("\n%s", fila_de_carros->carros[i].marca);
			printf("\n%s", fila_de_carros->carros[i].cor);
			printf("\n%d\n------------\n", fila_de_carros->carros[i].ano_fabricacao);
			count++;
		}
	}
}

void removerCarro(FilaCarros *fila_de_carros, int placa)
{
	FilaCarros temp_fila_de_carros;

	temp_fila_de_carros.in = 0;
	temp_fila_de_carros.fn = 0;

	bool carro_encontrado = false;

	if(fila_de_carros->fn == 0)
		printf("\na fila não possui nenhum carro...");
	else
	{
		while(fila_de_carros->in != fila_de_carros->fn)
		{
			if(fila_de_carros->carros[fila_de_carros->in].placa != placa)
			{
				temp_fila_de_carros.carros[temp_fila_de_carros.fn] = fila_de_carros->carros[fila_de_carros->in];
				temp_fila_de_carros.fn += 1;
			}
			else
			{
				carro_encontrado = true;
				printf("\nChasi do carro removido: %s", fila_de_carros->carros[fila_de_carros->in].chassi);
			}
			fila_de_carros->in += 1;
		}
	}

	fila_de_carros->in = 0; // fila não tem nenhum carro
	fila_de_carros->fn = 0;

	while(temp_fila_de_carros.in != temp_fila_de_carros.fn)
	{
		fila_de_carros->carros[fila_de_carros->fn] =  temp_fila_de_carros.carros[temp_fila_de_carros.in];
		fila_de_carros->fn += 1;

		temp_fila_de_carros.in += 1;
	}

	if(carro_encontrado)
		printf("\ncarro encontrado e removido\n");
	else
		printf("\ncarro não encontrado\n");

	imprimirCarros(fila_de_carros);
}

void separarParImpar(FilaCarros *filaPrincipal, FilaCarros *filaImp, FilaCarros *filaPar)
{
	if(filaPrincipal->in != filaPrincipal->fn)
	{
		if(filaPrincipal->carros[filaPrincipal->in].placa % 2 == 0)
		{
			filaPar->carros[filaPar->fn] = filaPrincipal->carros[filaPrincipal->in];
			filaPar->fn += 1;
		}
		else
		{
			filaImp->carros[filaImp->fn] = filaPrincipal->carros[filaPrincipal->in];
			filaImp->fn += 1;
		}

		filaPrincipal->in += 1;

		separarParImpar(filaPrincipal, filaImp, filaPar);
	}
}

int main(int argc, char** argv)
{
	FilaCarros fila_de_carros;

	fila_de_carros.in = 0;
	fila_de_carros.fn = 0;

	FilaCarros filaImp,  filaPar;

	filaImp.in = 0;
	filaImp.fn = 0;

	filaPar.in = 0;
	filaPar.fn = 0;

	//Carro carro;

	//dados de teste

	strcpy(fila_de_carros.carros[fila_de_carros.fn].chassi, "bbbb555");
	fila_de_carros.carros[fila_de_carros.fn].placa = 111;
	strcpy(fila_de_carros.carros[fila_de_carros.fn].modelo, "tesla cyber truck");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].marca, "tesla motors");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].cor, "azul");
	fila_de_carros.carros[fila_de_carros.fn].ano_fabricacao = 2017;

	fila_de_carros.fn += 1;

	strcpy(fila_de_carros.carros[fila_de_carros.fn].chassi, "aaa2323");
	fila_de_carros.carros[fila_de_carros.fn].placa = 222;
	strcpy(fila_de_carros.carros[fila_de_carros.fn].modelo, "honda cv 3");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].marca, "Honda");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].cor, "vermelho");
	fila_de_carros.carros[fila_de_carros.fn].ano_fabricacao = 2012;

	fila_de_carros.fn += 1;

	strcpy(fila_de_carros.carros[fila_de_carros.fn].chassi, "ddd333");
	fila_de_carros.carros[fila_de_carros.fn].placa = 333;
	strcpy(fila_de_carros.carros[fila_de_carros.fn].modelo, "corola y");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].marca, "corola");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].cor, "preto");
	fila_de_carros.carros[fila_de_carros.fn].ano_fabricacao = 2015;

	fila_de_carros.fn += 1;

	strcpy(fila_de_carros.carros[fila_de_carros.fn].chassi, "eee777");
	fila_de_carros.carros[fila_de_carros.fn].placa = 444;
	strcpy(fila_de_carros.carros[fila_de_carros.fn].modelo, "tesla model s");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].marca, "tesla");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].cor, "preto");
	fila_de_carros.carros[fila_de_carros.fn].ano_fabricacao = 2015;

	fila_de_carros.fn += 1;

	strcpy(fila_de_carros.carros[fila_de_carros.fn].chassi, "fff666");
	fila_de_carros.carros[fila_de_carros.fn].placa = 555;
	strcpy(fila_de_carros.carros[fila_de_carros.fn].modelo, "yamarra y 10");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].marca, "yamarra");
	strcpy(fila_de_carros.carros[fila_de_carros.fn].cor, "preto");
	fila_de_carros.carros[fila_de_carros.fn].ano_fabricacao = 2015;

	fila_de_carros.fn += 1;

	imprimirCarros(&fila_de_carros);

	removerCarro(&fila_de_carros, 555);

	separarParImpar(&fila_de_carros, &filaImp, &filaPar);

	printf("\n\nmostrando a fila par");

	imprimirCarros(&filaPar);

	printf("\n\nmostrando a fila impar");

	imprimirCarros(&filaImp);

	printf("\n\nprintando a fila original");

	imprimirCarros(&fila_de_carros);


	/*

	while(1)
	{
		printf("\n1 - inserir carro");
		printf("\n2 - mostrar todos os carros da fila");
		printf("\n3 - remover carro");
		printf("\n4 - inserir carro");
	}
	*/

	return 0;
}
