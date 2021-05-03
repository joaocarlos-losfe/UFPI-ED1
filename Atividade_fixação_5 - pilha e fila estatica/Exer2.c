/*
	Exercicio resolvido por: 
        João Carlos de Sousa Fé.
		Vitor José Ferreira dos Santos de Santana.
*/

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
	if(fila_de_carros->fn == max)
	{
		printf("\n fila cheia");
	}
	else
	{
		fila_de_carros->carros[fila_de_carros->fn] = carro;
		fila_de_carros->fn += 1;
		
		printf("\n carro inserido...\n");
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
	setlocale(LC_ALL, "Portuguese");
	
	FilaCarros fila_de_carros;

	fila_de_carros.in = 0;
	fila_de_carros.fn = 0;

	FilaCarros filaImp,  filaPar;

	filaImp.in = 0;
	filaImp.fn = 0;

	filaPar.in = 0;
	filaPar.fn = 0;

	Carro carro;
	int placa;
	
	int op = 0;
	
	while(1)
	{
		printf("\n1 - inserir carro\n2 - imprimir fila de carros\n3 - remover carro\n4 - separar em 2 novas filas\n: ");
		scanf("%d", &op);
		
		switch(op)
		{
		case 1:
			setbuf(stdin, NULL);
			printf("\n(str) chasi do carro: "); scanf(" %[^\n]s", carro.chassi);
			printf("\n(int) placa do carro: "); scanf("%d", &carro.placa);
			setbuf(stdin, NULL);
			printf("\n(str) modelo: "); scanf(" %[^\n]s", carro.modelo);
			printf("\n(str) marca: "); scanf(" %[^\n]s", carro.marca);
			printf("\n(str) cor: "); scanf(" %[^\n]s", carro.cor);
			setbuf(stdin, NULL);
			printf("\n(int) ano de fabricação: "); scanf("%d", &carro.ano_fabricacao);
			inserirCarroNaFila(&fila_de_carros, carro);
			setbuf(stdin, NULL);
			break;
		case 2:
			imprimirCarros(&fila_de_carros);
			break;
		case 3:
			printf("\nentre com a placa do carro: "); scanf("%d", &placa);
			removerCarro(&fila_de_carros, placa);
			break;
		case 4:
			separarParImpar(&fila_de_carros, &filaImp, &filaPar);
			printf("\nCarros pares: \n");
			imprimirCarros(&filaPar);
			printf("\nCarros impares: \n");
			imprimirCarros(&filaImp);
			break;
		default:
			printf("opção invalida");
			break;
		}	
	}
	return 0;
}
