#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct{
  char sinal;
  int coeficiente;
  char variavel;
  int expoente;
}Termo;

typedef struct No{
	Termo polinomio;
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
  No *fim;
	int tam;
}Lista;

void menu();

void inserirFinal(Lista *lista, Termo t){
	No *no,*novo = (No*)malloc(sizeof(No));
	novo->polinomio = t;
	if(lista->inicio == NULL){
		lista->inicio = novo;
    lista->fim = novo;
    lista->fim->proximo = lista->inicio;
	}
	else{
		lista->fim->proximo = novo;
    lista->fim = novo;
    novo->proximo = lista->inicio;
	}
	lista->tam++;
}

void criar_lista(Lista *lista){
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tam = 0;
}


void imprimir(Lista lista){
	No *no;
	no = lista.inicio;
	if(no != NULL){
    do{
      printf("%c",no->polinomio.sinal);
      printf("%d",no->polinomio.coeficiente);
      printf("%c",no->polinomio.variavel);
      printf("%d",no->polinomio.expoente);
      no = no->proximo;
    }while(no != lista.inicio);
  }
  printf("\n");
}

void cadastroMonomio(Termo *t){
	int coeficiente,expoente,ultimo;
	char sinal;
	char variavel;
	printf("Criar um Monomio\n");
	printf("Sinal:	");
	scanf(" %c",&t->sinal);
	fflush(stdin);
	printf("Coeficiente:	");
	scanf(" %d",&t->coeficiente);
	fflush(stdin);
	printf("Variável:	");
	scanf(" %c",&t->variavel);
	fflush(stdin);
	printf("Expoente:	");
	scanf(" %d",&t->expoente);
	fflush(stdin);

}

int main(int argc, char **argv[]){
  Lista lista, vetorPoli[100];
  Termo t;
  criar_lista(&lista);
	char *monomio;
  monomio = (char*)malloc(sizeof(char) * 30);
	int termos,op,contador = 0;
	do{
		menu();
		scanf("%d",&op);
		if(op == 0){
			exit(1);
		}
		else if(op == 1){
			printf("termos do polinomio:	");
			scanf("%d",&termos);
			for(int i = 0; i < termos; i++)
			{
				cadastroMonomio(&t);
				inserirFinal(&lista,t);
			}
      vetorPoli[contador] = lista;
      contador++;
		}
		else if(op == 2){
			imprimir(lista);
		}
		else{
			printf("erro de entrada!\n");
		}
	}while(op != 0);
  return 0;
}

void menu(){
	printf("[0] - Sair\n");
	printf("[1] - Cadastrar Polinomio\n");
  printf("[2] - Imprimir\n");
}
