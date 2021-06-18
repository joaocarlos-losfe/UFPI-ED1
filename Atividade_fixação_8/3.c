#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<math.h>

typedef struct No{
	int valor;
  int escolhido;
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
  No *fim;
	int tam;
}Lista;

void menu();
void criar_lista(Lista *lista);
void inserirOrdenado(Lista *lista,int num);
void inserirInicio(Lista *lista, int num);
void inserirFinal(Lista *lista, int num);
int buscar(Lista *lista, int num,int *rep);
void imprimir(Lista lista);
void numProximos(Lista *lista, int num, int *proximo1,int *proximo2);
void jogo(Lista *lista,int valor);
void geraJogo(Lista *lista);

int main(int argc, char *argv[]){
	Lista lista;
	criar_lista(&lista);
	int op,valor;
  geraJogo(&lista);
	do{
    menu();
		scanf("%d",&op);
		switch(op){
			case 1:
				printf("Número: ");
				scanf("%d",&valor);
        jogo(&lista,valor);
				break;
      default:
        break;
		}
	}while(op != 0);
	return 0;
}

void geraJogo(Lista *lista){
  int numJogo,i;
  srand(time(NULL));
  for(i = 0; i < 100; i++){
    numJogo = rand() % 500; //
    inserirOrdenado(lista,numJogo);
  }
}

void jogo(Lista *lista,int valor){
  int proximo1 = 0,proximo2 = 0,rep = 0;
  int num = buscar(lista,num,&rep);
  printf("\n");
  if(num == 0){
    printf("Número %d não está na lista\n",num);
    numProximos(lista,valor,&proximo1,&proximo2);
    printf("Números próximos:  %d e %d\n",proximo1, proximo2);
  }
  else{
    printf("Número %d encontrado\n",valor);
    printf("Número %d escolhido %d vezes\n",num,rep);
  }
  printf("\n\n");
}

void menu(){
  printf("0 - Sair\n");
  printf("1 - Jogar um número\n");
  printf(": ");
}

void numProximos(Lista *lista, int num, int *proximo1,int *proximo2)
{
  No *aux = lista->inicio;
  int p1,p2;
  p1 = aux->valor;
  p2 = aux->proximo->valor;
  do{
    if(abs(aux->valor - num ) + abs(aux->proximo->valor - num ) < abs(num - p1) + abs(num - p2) ){
      p1 = aux->valor;
      p2 = aux->proximo->valor;
    }
    aux = aux->proximo;
  }while (aux != lista->inicio);
  (*proximo1) = p1;
  (*proximo2) = p2;
}

void criar_lista(Lista *lista){
  lista->inicio = NULL;
  lista->fim = NULL;
  lista->tam = 0;
}

int buscar(Lista *lista, int num,int *rep){
  No *aux = lista->inicio;
  int retorno = 0;
  if(aux){
    do{
      if(aux->valor == num){
        retorno = aux->valor;
        (*rep)++;
      }
      aux = aux->proximo;
    }while (aux != lista->inicio);
  }
  return retorno;
}

void imprimir(Lista lista){
	No *no;
	no = lista.inicio;
	if(no != NULL){
    do{
      printf("%d ",no->valor);
      no = no->proximo;
    }while(no != lista.inicio);
  }
}

void inserirInicio(Lista *lista, int num){
	No *novo = malloc(sizeof(No));
	if(novo){
    novo->valor = num;
		novo->proximo = lista->inicio;
		lista->inicio = novo;
    if(lista->fim == NULL){
      lista->fim = novo;
    }
    lista->fim->proximo = lista->inicio;
    lista->tam++;
  }
  else{
    printf("Erro na alocação\n");
  }
}

void inserirFinal(Lista *lista, int valor){
	No *no,*novo = (No*)malloc(sizeof(No));
	novo->valor = valor;
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

void inserirOrdenado(Lista *lista,int num){
	No *aux,*novo = malloc(sizeof(No));
  if(novo){
    novo->valor = num;
    if(lista->inicio == NULL){
      inserirInicio(lista,num);
    }
    else if(novo->valor < lista->inicio->valor){
      inserirInicio(lista,num);
    }
    else{
      aux = lista->inicio;
      while(aux->proximo != lista->inicio && novo->valor > aux->proximo->valor){
        aux = aux->proximo;
      }
      if(aux->proximo == lista->inicio){
        inserirFinal(lista,num);
      }
      else{
        novo->proximo = aux->proximo;
        aux->proximo = novo;
        lista->tam++;
      }
    }
  }
  else{
    printf("Erro na alocação\n");
  }
}
