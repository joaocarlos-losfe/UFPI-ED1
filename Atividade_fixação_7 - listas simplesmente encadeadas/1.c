#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

void menu(){
  printf("0 - Sair\n");
  printf("1 - Inserir elemento\n");
  printf("2 - Imprimir Normal\n");
  printf("3 - Imprimir Invertido\n");
  printf("4 - Soma dos elementos pares\n");
  printf("5 - Multiplos de 3 menores que 60\n");
  printf("6 - Remova um elemento\n");
  printf("7 - Alterar um número\n");
}

typedef struct No{
	int valor;
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
	int tam;
}Lista;

void inserir(Lista *lista,int valor);
void imprimir(Lista *lista);
void imprimir_lista_inverso (No *aux);
int somaDosParesIter(Lista *lista);
int somaDosParesRec(No *inicio);
int prodMulti3Iter(Lista *lista);
void prodMulti3Rec(No *inicio, int *produto);
int remover(Lista *lista, int numero);
int alterar(Lista *lista, int numero,int n_alterar);
void ordena(Lista *lista);

int main(int argc, char *argv[]){
	Lista lista;
	lista.inicio = NULL;
	lista.tam = 0;
  No *inicio = lista.inicio;
	int op,valor,numero_alterar,numero,produto = 1;
	do{
    menu();
		scanf("%d",&op);
		switch(op){
			case 0:
				break;
			case 1:
				printf("Valor: ");
				scanf("%d",&valor);
        inserir(&lista,valor);
        break;
      case 2:
        imprimir(&lista);
        break;
      case 3:
        imprimir_lista_inverso(lista.inicio);
        break;
      case 4:
        printf("Soma dos elementos pares (Iterativa)= %d\n",somaDosParesIter(&lista));
        printf("Soma dos elementos pares (Recursiva)= %d\n",somaDosParesRec(lista.inicio));
        break;
      case 5:
        printf("Produto dos Multiplos de 3 menores que 60 (Iterativa) = %d\n",prodMulti3Iter(&lista));
        prodMulti3Rec(lista.inicio,&produto);
        printf("Produto dos Multiplos de 3 menores que 60 (Recursiva) = %d\n",produto);
        break;
      case 6:
        printf("Digite um número para remover: ");
        //int numero;
        scanf("%d",&numero);
        if(remover(&lista,numero) == 0){
          printf("Elemento não encontrado!\n");
        }
        else{
          printf("%d foi removido!\n",numero);
        }
        break;
      case 7:
        printf("Numero para alterar: ");
        scanf("%d",&numero);
        printf("Numero para botar no lugar: ");
        scanf("%d",&numero_alterar);
        if(alterar(&lista,numero,numero_alterar)){
          printf("Elemento não encontrado\n");
        }
        else{
          printf("%d foi alterado por %d",numero,numero_alterar);
        }
        break;
      default:
        break;
		}
	}while(op != 0);

	return 0;
}

int alterar(Lista *lista, int numero,int n_alterar)
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
          ptr->valor = n_alterar;
      }
      else{
        antes = ptr;
        ptr = ptr->proximo;
      }
    }
    ordena(lista);
  }
  return status; // retorna 0 se n achar
}

void ordena(Lista *lista){
	//assert(lista != NULL);
	if(lista->inicio != NULL){
		for(No *i = lista->inicio; i->proximo != NULL; i = i->proximo){
			No *menor = i;
			for(No *j = i->proximo; j != NULL; j = j->proximo){
				if(j->valor < menor->valor){
					menor = j;
				}
			}
		int aux = i->valor;
		i->valor = menor->valor;
		menor->valor = aux;
		}
	}
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

int somaDosParesRec(No *inicio){
    if(inicio != NULL){
      if(inicio->valor % 2 == 0){
        return somaDosParesRec(inicio->proximo) + inicio->valor;
      }
      else{
        somaDosParesRec(inicio->proximo);
      }
    }
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

void prodMulti3Rec(No *inicio, int *produto){
  if(inicio != NULL){
    if(inicio->valor % 3 == 0 && inicio->valor < 60){
      (*produto) *= inicio->valor;
    }
    prodMulti3Rec(inicio->proximo,produto);
  }
}

void inserir(Lista *lista,int valor)
{
	No *atual, *novo, *anterior;

	novo = (No *) malloc(sizeof(No));

	atual = lista->inicio;
	anterior = NULL;

	novo->valor = valor;
	novo->proximo = NULL;

	if(atual == NULL){
		novo->proximo = NULL;
		lista->inicio = novo;
	}
	else{
		while(atual != NULL && atual->valor < valor){
			anterior = atual;
			atual = atual->proximo;
		}

		novo->proximo = atual;

		if(anterior == NULL){
			lista->inicio = novo;
		} else{
			anterior->proximo = novo;
		}
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
	printf("Tamanho da lista: %d\n",lista->tam);
	while(inicio != NULL){
		printf("%d ", inicio->valor);
    inicio = inicio->proximo;
	}
	printf("\n\n");
}
