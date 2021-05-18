/*
    por João Carlos de Sousa Fé e Vitor José Ferreira dos Santos de Santana

QUESTÃO - 1

 O estacionamento Picoense contém uma única alameda que guarda até 10 carros. Existe uma entrada e
uma saída, de tal forma que quando um determinado carro entra ele fica no final da fila e o primeiro
que chegou sempre fica próximo a saída, ou seja, todas as vezes que um carro sai todos os outros
devem ser manobrados um espaço para frente. Faça um programa em C, onde o usuário entrará com o
número da placa do carro e 'E' se estiver entrando no estacionamento e 'S' se estiver saindo do
estacionamento.
 O programa deve emitir uma mensagem sempre que um carro entrar ou sair do
estacionamento.
Quando um carro chegar, a mensagem deve especificar se existe ou não vaga no
estacionamento.
Quando um carro sair, a mensagem deverá incluir o número de vezes em que o carro
foi manobrado para fora do estacionamento para permitir que outros carros saíssem, além de mostrar
quantos carros foram manobrados para que ele saísse.
Obs.: Não se esqueça que todas as vezes que um carro vai sair os que estão na frente devem ser
manobrados para o final da fila, mas ao final o carro que estava no inicio da fila deve continuar como
o primeiro da fila.

*/


#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define NCARRO 10

void menu()
{
	printf("[0] - Sair do programa\n");
	printf("[1] - Continuar no estacionamento\n");
	printf(": ");
}

typedef struct
{
	int placa_carro;
	char status[1];
}Carro;

typedef struct
{
	int inicio,fim; /*Inicio e fim da fila*/
	Carro carros[NCARRO];
}FilaCarro;

int inserir(FilaCarro *fila, Carro carro);
int cadastro(Carro *carro);
void imprimir(FilaCarro *fila);
int filaVazia(FilaCarro *fila);

int remover(FilaCarro *fila, Carro carro){
	int c,i;
	if(filaVazia(fila) != 0){
		c = fila->carros[0];
		for(i = 0; i < fila->fim; i++){
			fila->carros[i] = fila->carros[i+1];
		}
		fila->fim--;
	}
	return c;
}

int main(int argc, char *argv[])
{
	FilaCarro fila;
	Carro carro;
	int op;
	do{
		menu();
		scanf("%d",&op);
		if(op == 0) exit(1);
		else{
			int r = cadastro(&carro);
			if(r == 1)
			{
				if(inserir(&fila,carro) == 0) printf("Há vagas - Carro adcionado!\n");
				else printf("Não há vagas!\n");
			}
			else
			{
				if(filaVazia(&fila) == 0) printf("Não há carros no estacionamento!\n");
				else
				{
					printf("Há carro!\n");
				}
			}
		}
		imprimir(&fila);

	}while(op != 0);
	return 0;
}


int cadastro(Carro *carro)
{
	int ret = 0; /*Se ret = 0 é pq o carro vai sair!*/
	printf("Cadastro de carro!\n\n");
	printf("Placa do carro :: ");
	scanf("%d",&carro->placa_carro);
	printf("Entrar(e)	ou	Sair(s) :: ");
	scanf("%s",carro->status);
	printf("\n");
	if(strcmp(carro->status,"e") == 0) ret = 1;
	return ret;
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

void imprimir(FilaCarro *fila){
  int i;
  printf("imprimindo\n");
  for(i = 0; i < fila->fim; i++){
    printf("%d ",fila->carros[i].placa_carro);
		//printf("%s",fila->carros[i].status);
  }
  printf("\n");
}

int filaVazia(FilaCarro *fila){
	int vazio = 1;
	if(fila->fim == 0) vazio = 0;
	return vazio;
}
