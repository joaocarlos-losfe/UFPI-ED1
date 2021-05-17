/*
    por João Carlos de Sousa Fé e Vitor José Ferreira dos Santos de Santana

QUESTÃO - 1

 O estacionamento Picoense contém uma única alameda que guarda até 10 carros. Existe uma entrada e
uma saída, de tal forma que quando um determinado carro entra ele fica no final da fila e o primeiro
que chegou sempre fica próximo a saída, ou seja, todas as vezes que um carro sai todos os outros
devem ser manobrados um espaço para frente. Faça um programa em C, onde o usuário entrará com o
número da placa do carro e 'E' se estiver entrando no estacionamento e 'S' se estiver saindo do
estacionamento. O programa deve emitir uma mensagem sempre que um carro entrar ou sair do
estacionamento. Quando um carro chegar, a mensagem deve especificar se existe ou não vaga no
estacionamento. Quando um carro sair, a mensagem deverá incluir o número de vezes em que o carro
foi manobrado para fora do estacionamento para permitir que outros carros saíssem, além de mostrar
quantos carros foram manobrados para que ele saísse.
Obs.: Não se esqueça que todas as vezes que um carro vai sair os que estão na frente devem ser
manobrados para o final da fila, mas ao final o carro que estava no inicio da fila deve continuar como
o primeiro da fila.

*/


#include<stdio.h>
#include<stdlib.h>

#define NCARRO 10

void menu()
{
	printf("[0] - Sair do programa\n");
	printf("[1] - Entrar no estacionamento\n");
	printf("[2] - Sair do estacionamento\n");
	printf(": ");
}

typedef struct
{
	int placa_carro;
	char status;
}Carro;

typedef struct
{
	int inicio,fim; /*Inicio e fim da fila*/
	Carro carros[NCARRO];
}FilaCarro;

int inserir(FilaCarro *fila, Carro carro);
void cadastro(Carro *carro);

int main(int argc, char *argv[])
{
	FilaCarro fila;
	Carro carro;
	int op = 1;
	do{
		cadastro(&carro);
		if(inserir(&fila,carro) == 0) printf("Carro adcionado!\n");
		else printf("Fila cheia!\n");
	}while(op != 0);
	return 0;
}
void cadastro(Carro *carro)
{
	printf("Cadastro de carro!\n\n");
	printf("Placa do carro: ");
	scanf("%d",&carro->placa_carro);
	printf("Entrar - e\nSair - s");
	scanf("%c",carro->status);
	printf("\n");
}

int inserir( FilaCarro *fila, Carro carro)
{
	int s = 0;
	if(fila->fim == NCARRO)
  {
		s = -1;
	}
	else
  {
		fila->carros[fila->fim] = carro;
		fila->fim += 1;
	}
	return s;
}
