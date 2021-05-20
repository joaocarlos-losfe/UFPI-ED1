/*
playlist boa sobre lista
https://www.youtube.com/watch?v=biTMaMxWLRc&list=PLqJK4Oyr5WSgPpLg-lZJfJZN0DQ5bwrfP&index=1
*/

#include<stdio.h>
#include<stdlib.h>

void menu(){
  printf("0 - Sair\n");
  printf("1 - Inserir no final\n");
  printf("2 - Imprimir Normal\n");
  printf("3 - Imprimir Invertido\n");
  printf("4 - Soma dos elementos pares\n");
  printf("5 - Multiplos de 3 menores que 60\n");
  printf("6 - Remova um elemento\n");
  //printf("7 - Alterar um número\n");
}

typedef struct No{
	int valor;
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
	int tam;
}Lista;

void inserirInicio(Lista *lista, int valor);
void inserirFinal(Lista *lista, int valor);
void imprimir(Lista *lista);
int somaDosParesIter(Lista *lista);
int prodMulti3Iter(Lista *lista);
int remover(Lista *lista, int numero);
void imprimir_lista_inverso (No *aux);

int main(int argc, char *argv[]){
	Lista lista;
	lista.inicio = NULL;
	lista.tam = 0;
  No *inicio = lista.inicio;
	int op,valor;
	do{
    menu();
		scanf("%d",&op);
		switch(op){
			case 0:
				break;
			case 1:
				printf("Valor: ");
				scanf("%d",&valor);
				inserirFinal(&lista,valor);
        break;
      case 2:
        imprimir(&lista);
        break;
      case 3:
        imprimir_lista_inverso(lista.inicio);
        break;
      case 4:
        printf("Soma dos elementos pares (Iterativa)= %d\n",somaDosParesIter(&lista));
        break;
      case 5:
        printf("Produto dos Multiplos de 3 menores que 60 (Iterativa) = %d\n",prodMulti3Iter(&lista));
        break;
      case 6:
        printf("Digite um número para remover: ");
        int numero;
        scanf("%d",&numero);
        if(remover(&lista,numero) == 0){
          printf("Elemento não encontrado!\n");
        }
        else{
          printf("%d foi removido!\n",numero);
        }
        break;
      default:
        break;
		}
	}while(op != 0);

	return 0;
}



int remover(Lista *lista, int numero)
{
  No *inicio = lista->inicio;
  No *ptr, *antes;
  int status;
  if(inicio == NULL){
    status = 0;
  }
  else{
    ptr = inicio;
    antes = inicio;
    while(ptr != NULL)
    {
      if(ptr->valor == numero) // achei o numero pra remover
      {
        if(ptr == inicio){ //remover o primeiro da lista
          inicio = inicio->proximo;
          free(ptr);
          status = 1;
        }
        else{
          antes->proximo = ptr->proximo; // refazer o encadeamento
          free(ptr); // libera o espaço do nó
          status = 1;
        }
      }
      else{
        antes = ptr;
        ptr = ptr->proximo;
      }
    }
  }
  return status; // retorna 0 se n achar
}

int somaDosParesIter(Lista *lista){
  int soma = 0;
  No *inicio = lista->inicio;
  while(inicio != NULL)
  {
    if(inicio->valor % 2 == 0){
      soma += inicio->valor;
    }
    inicio = inicio->proximo;
  }
  return soma;
}

int prodMulti3Iter(Lista *lista){
  int produto = 1;
  No *inicio = lista->inicio;
  while(inicio != NULL)
  {
    if(inicio->valor % 3 == 0 && inicio->valor < 60){
      produto *= inicio->valor;
    }
    inicio = inicio->proximo;
  }
  return produto;
}

int somaDosParesRec(Lista *lista,int soma){
  /*Ainda não feita!*/
}

//inserir elementos sempre no inicio da lista
void inserirInicio(Lista *lista, int valor){
	No *novo = (No*)malloc(sizeof(No));
	novo->valor = valor; // (*novo).valor = valor
	novo->proximo = lista->inicio; //(*novo).proximo = NULL
	lista->inicio = novo;
	lista->tam++;

}
void inserirFinal(Lista *lista, int valor){
	No *no,*novo = (No*)malloc(sizeof(No));
	novo->valor = valor;
	novo->proximo = NULL;

	if(lista->inicio == NULL){
		lista->inicio = novo;
		//lista->tam++;
	}
	else{
		no = lista->inicio;
		while(no->proximo != NULL){
			no = no->proximo;
		}
		no->proximo = novo;
		//lista->tam++;
	}
	lista->tam++;
}

void imprimir_lista_inverso (No *aux)
{
    if(aux == NULL)
        return;
    imprimir_lista_inverso(aux->proximo);
    printf ("Dado = %d\n", aux->valor);
}

// imprimir elementos na lista
void imprimir(Lista *lista){
	No *inicio = lista->inicio;
  imprimir_lista_inverso(inicio);
	printf("Tamanho da lista: %d\n",lista->tam);
	while(inicio != NULL){
		printf("%d ", inicio->valor);
    inicio = inicio->proximo;
	}
	printf("\n\n");
}
