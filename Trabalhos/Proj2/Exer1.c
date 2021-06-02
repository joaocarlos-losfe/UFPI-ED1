/*
	Primeira questão referente a segunda avaliação da discpina de Estrurura de dados I.

	Autores: João Carlos de Sousa Fé && Vitor José Ferreira dos Santos de Santana.

	Data de inicio da resolução deste exercicio: 08/05/2021

	Questão 2. Implementação estatica

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
		printf("\nFila cheia !!\n");
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
		printf("\nFila vazia\n");
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
		printf("\nFila vazia !!\n");
	}
	
}

bool taNaFila(Fila *fila, int placa)
{
	Fila fila_temp; fila_temp.fim = 0;
	
	bool ta_na_fila = false;
	Carro carro;
	
	while(!filaVazia(fila))
	{
		remover(fila, &carro);
		
		inserir(&fila_temp, carro);
		
		if(placa == carro.placa)
			ta_na_fila = true;
	}
	
	*fila = fila_temp;
	
	return ta_na_fila;
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
	
	*fila = fila_temp;
	
	return carro_saiu;
}


void menu()
{
	printf("\n1 - estacionamento");
	printf("\n2 - exibir fila");
	printf("\n0 - encerrar programa\n> ");
	
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
    Fila fila_carros;
	
	fila_carros.fim = 0;
	
	Carro carro;
	
	int total_sairam = 0;
	int total_manobrados = 0;
	int op = 1;
	char E_S;
	bool saiu = false;
	
	do
	{
		menu();
		scanf("%d", &op);
		
		switch(op)
		{
		case 1:
			printf("\nPlaca do carro: ");
			scanf("%d", &carro.placa);
			
			printf("\nE - Entrar no estacionamento");
			printf("\nS - Sair do estacionamento\n> ");
			scanf(" %c", &E_S);
			
			if(E_S == 'E' || E_S == 'e')
			{
				if(!taNaFila(&fila_carros, carro.placa))
					inserir(&fila_carros, carro);
				else
					printf("\nCarro ja se encontra na fila. O carro é CLONADO !!\n");
			}
			else if (E_S == 'S' || E_S == 's')
			{
				saiu = manobrarCarroPraFora(&fila_carros, &total_sairam, &total_manobrados, carro.placa);
				
				if(saiu)
					printf("\nTotal sairam da frente: %d. total manobrados: %d\n", total_sairam, total_manobrados);
				else
					printf("\nCarro não encontrado...\n");
				
			}
			else
				printf("Operação cancelada");
			
			total_sairam = 0;
			total_manobrados = 0;
			
			break;
		case 2:
			exibirFila(&fila_carros);
			printf("\n");
		default:
			break;
		}
		
	}while(op!=0);
	
	return 0;
}