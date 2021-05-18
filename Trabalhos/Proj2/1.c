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

/*
De acordo com o enunciado, é preciso, pra sair do estacionamento, verificar se
o carro existe no estacionamento, depois, identificar o seu lugar na fila, depois,
desenfileirar até chegar onde está o carro e colocar os elementos, que foram
desenfileirados, em uma fila auxiliar, e depois, remover o carro solicitado.
Assim, termino de enfileirar os elementos restantes da a fila auxiliar, para que
sejam, por sua vez, retornados a fila original.

muito trabalho para coisa coisa, mas, vai ser preciso.
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
int cadastro(Carro *carro,int placa, char status[]);
void imprimir(FilaCarro *fila);
int filaVazia(FilaCarro *fila);


int removerPlaca(FilaCarro *fila,FilaCarro *aux, Carro carro, int placa){
	int c,i;
	if(filaVazia(fila) != 0){
		//c = fila->carros[0];
		for(i = 0; i < fila->fim; i++){
			if(placa == fila->carros[i].placa_carro){
				fila->carros[i] = fila->carros[i+1];
			}
		}
		inserir(aux,carro);
		fila->fim--;
	}
	return c;
}

int busca_carro(FilaCarro *fila,int placa){
	//se a função retornar 0 é porque o carro existe na lista

	int busca;
	for(int count = 0; count < fila->fim; count++){
		if(placa == fila->carros[count].placa_carro){
			busca = 0;
		}
	}
	return busca;
}

int main(int argc, char *argv[])
{
	FilaCarro fila;
	Carro carro;
	FilaCarro auxiliar; /*Fila auxiliar para a saida dos carros*/
	int op,placa;
	char status[1];
	do{
		menu();
		scanf("%d",&op);
		if(op == 0) exit(1); /*Se op == 0 o programa encerra*/
		else{
			printf("Cadastro de carro!\n\n");
			printf("Placa do carro :: ");
			scanf("%d",&placa);
			printf("Entrar(e)	ou	Sair(s) :: ");
			scanf("%s",status);
			printf("\n");
			int r = cadastro(&carro,placa,status);
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
					if(busca_carro(&fila,placa) == 0) /* essa linha ainda não foi terminada!*/
					{
						printf("carro encontrado!\n");
						removerPlaca(&fila,&auxiliar,carro,placa);
					}
					else{
						printf("Esse carro não foi encontrado aqui!\n");
					}
					/*
					Acho que tenho que mudar a forma que leio os dados do carro.
					Não posso passar o último elemento, pois, não qual carro que devo procurar
					*/
				}
			}
		}
		imprimir(&fila);

	}while(op != 0);
	return 0;
}


int cadastro(Carro *carro,int placa, char status[])
{
	int ret = 0; /*Se ret = 0 é pq o carro vai sair!*/
	//printf("Cadastro de carro!\n\n");
	//printf("Placa do carro :: ");
	carro->placa_carro = placa;
	//printf("Entrar(e)	ou	Sair(s) :: ");
	strcpy(carro->status,status);
	//carro->status = status;
	printf("\n");
	/*
	Aqui é feito essa comparação para que eu saiba se o carro vai sair ou não.
	Preciso saber disso pela forma que o enunciado foi feito, assim, na main é
	importante saber se o carro vai sair(ret = 0) ou entrar(ret = 1)
	*/
	if(strcmp(carro->status,"e") == 0) ret = 1;
	return ret;
}

int inserir( FilaCarro *fila, Carro carro)
{

	int s = 0;
	if(fila->fim == NCARRO)
  {
		s = -1; /*Se a fila estiver cheia*/
	}
	else
  {
		fila->carros[fila->fim] = carro; /*Passando os elementos para o vetor de carro na fila*/
		fila->fim += 1;
	}
	return s; /*Se a fila não tiver cheia s = 0*/
}

void imprimir(FilaCarro *fila){
	/*Função para imprimir os dados do carro que estão na fila*/
	/*Essa função está errada!*/
  int i;
  printf("Imprimindo dados da fila\n\n");
  for(i = 0; i < fila->fim; i++){
    printf("%d ",fila->carros[i].placa_carro);
		printf("%s",fila->carros[i].status);
  }
  printf("\n");
}

int filaVazia(FilaCarro *fila){
	/* retorna 1 se a fila não for vazia e 0 se for vazia*/
	int vazio = 1;
	if(fila->fim == 0) vazio = 0;
	return vazio;
}
