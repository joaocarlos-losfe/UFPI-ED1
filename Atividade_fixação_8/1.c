#include<stdio.h>
#include<stdlib.h>

void menu(){
  printf(" [ 0 ] - Sair\n");
  printf(" [ 1 ] - Inserir\n");
  printf(" [ 2 ] - Imprimir \n");
  printf(" [ 3 ] - Imprimir contrária\n");
  printf(" [ 4 ] - Ver vizinhos\n");
  printf(" [ 5 ] - Produto dos vizinhos\n");
  printf(" [ 6 ] - Remover\n");
}

#define MSG "Erro na alocação"

typedef struct no{
  int valor;
  struct no *proximo;
  struct no *anterior;
}No;

void inserirOrdenado(No **lista, int num, int *tamanho);
No *ultimoNoLista(No **lista);
void imprimirContratio(No *no);
No *buscar(No **lista, int num,int *posicao, int *antes, int *depois, int *r);
No *remover(No **lista, int num);
void imprimir(No *no);
int produtoDosVizinhos(No *no, int num,int antes,int depois,int r);
void zeraTudo(int *n1,int *n2,int *n3 );

int main(int argc, char *argv[]){
  int op,valor,anterior,posicao = 0,tamanho = 0;
  int antes = 0,depois = 0,r = 0;
  No *buscado,*lista = NULL;;
  do{
    menu();
    printf(": ");
    scanf("%d",&op);
    printf("\n");
    switch (op) {
      case 1:
        printf("Valor: ");
        scanf("%d",&valor);
        inserirOrdenado(&lista,valor,&tamanho);
        break;
      case 2:
        imprimir(lista);
        break;
      case 3:
        imprimirContratio(ultimoNoLista(&lista));
        break;
      case 4:
        printf("Valor: ");
        scanf("%d",&valor);
        zeraTudo(&posicao,&antes,&depois);
        buscado = buscar(&lista,valor,&posicao,&antes,&depois,&r);
        if(buscado){
          printf("Elemento procurado: %d\n",buscado->valor);
          printf("Posição = %d\n",posicao);
          if(r == 1){
            printf("Vizinhos antes: %d\n",antes);
          }
          else if(r == 2){
            printf("Vizinhos depois: %d\n",depois);
          }
          else{
            printf("Vizinhos antes: %d\n",antes);
            printf("Vizinhos depois: %d\n",depois);
          }
        }
        else{
          printf("%s\n",MSG);
        }
        break;
      case 5:
        printf("Valor: ");
        scanf("%d",&valor);
        zeraTudo(&posicao,&antes,&depois);
        buscado = buscar(&lista,valor,&posicao,&antes,&depois,&r);
        int p = produtoDosVizinhos(lista,buscado->valor,antes,depois,r);
        printf("Produto = %d\n",p);
        break;
      case 6:
        printf("Valor: ");
        scanf("%d",&valor);
        buscado = remover(&lista,valor);
        if(buscado){
          printf("Elemento encontrado: %d\n",buscado->valor);
          free(buscado);
          tamanho--;
        }
        else{
          printf("%s",MSG);
        }
        break;
      default:
        if(op != 0) printf("Opação inválida\n");
    }
    printf("\n");
  }while(op != 0);
}

void inserirOrdenado(No **lista, int num,int *tamanho){
  No *aux,*novo = malloc(sizeof(No));
  if(novo){
    novo->valor = num;
    if(*lista == NULL){
      novo->proximo = NULL;
      novo->anterior = NULL;
      *lista = novo;
    }
    else if(novo->valor < (*lista)->valor){
      novo->proximo = *lista;
      (*lista)->anterior = novo;
      *lista = novo;
    }
    else{
      aux = *lista;
      while(aux->proximo && novo->valor > aux->proximo->valor){
        aux = aux->proximo;
      }
      novo->proximo = aux->proximo;
      if(aux->proximo)
        aux->proximo->anterior = novo;
      novo->anterior = aux;
      aux->proximo = novo;
    }
    (*tamanho)++;
  }
  else{
    printf("%s\n",MSG);
  }
}

int produtoDosVizinhos(No *no, int num, int antes, int depois, int r){
  int produto = 1;
  if(r == 1){
    produto = antes;
  }
  else if(r == 2){
    produto = depois;
  }
  else{
    produto = antes * depois;
  }
  return produto;
}

void imprimir(No *no){
  printf("lista: ");
  while(no != NULL){
    printf("%d ",no->valor);
    no = no->proximo;
  }
  printf("\n");
}

No *ultimoNoLista(No **lista){
  No *aux = *lista;
  while(aux->proximo != NULL){
    aux = aux->proximo;
  }
  return aux;
}

void imprimirContratio(No *no){
  printf("lista contrária\n");
  while(no){
    printf("%d ",no->valor);
    no = no->anterior;
  }
  printf("\n");
}

No *remover(No **lista, int num){
  No *aux, *remover = NULL;
  if(*lista){
    if((*lista)->valor == num){
      remover = *lista;
      *lista = remover->proximo;
      if(*lista){
        (*lista)->anterior = NULL;
      }
    }
    else{
      aux = *lista;
      while(aux->proximo && aux->proximo->valor != num){
        aux = aux->proximo;
      }
      if(aux->proximo){
        remover = aux->proximo;
        aux->proximo = remover->proximo;
        if(aux->proximo){
          aux->proximo->anterior = aux;
        }
      }
    }
  }
  return remover;
}

No *buscar(No **lista, int num,int *posicao, int *antes, int *depois, int *r){
  No *aux,*no = NULL;
  aux = *lista;
  aux->anterior = NULL;
  int status = 0;
  while(aux != NULL){
    if(aux->valor == num){
      if(aux->proximo == NULL){
        no = aux;
        (*antes) = aux->anterior->valor;
        (*r) = 1;
      }
      else if(aux->anterior == NULL){
        no = aux;
        (*depois) = aux->proximo->valor;
        (*r) = 2;
      }
      else{
        no = aux;
        (*antes) = aux->anterior->valor;
        (*depois) = aux->proximo->valor;
        (*r) = 3;
      }
      status = 1;
    }
    if(status == 0) (*posicao)++;
    aux = aux->proximo;
  }
  return no;
}
void zeraTudo(int *n1,int *n2,int *n3 ){
  *n1 = 0;
  *n2 = 0;
  *n2 = 0;
}
