#include<stdio.h>
#include<stdlib.h>

void menu(){
  printf("0 - Sair\n");
  printf("1 - inserir\n");
  printf("2 - imprimir contrária\n");
  printf("3 - remover\n");
  printf("4 - tamanho da lista\n");
  printf("5 - Vizinhos\n");
  printf("6 - imprimir \n");
  printf("7 - Produto dos vizinhos\n");
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
No *buscar(No **lista, int num, int *posicao);
No *remover(No **lista, int num);
void imprimir(No *no);
int produtoDosVizinhos(No *no, int num);

int main(int argc, char *argv[]){
  int op,valor,anterior,posicao = 0,tamanho = 0;
  No *removido,*lista = NULL;;
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
        imprimirContratio(ultimoNoLista(&lista));
        break;
      case 3:
        printf("Valor: ");
        scanf("%d",&valor);
        removido = buscar(&lista,valor,&posicao);
        if(removido){
          printf("Elemento encontrado: %d\n",removido->valor);
          free(removido);
          tamanho--;
        }
        else{
          printf("%s",MSG);
        }
        break;
      case 4:
        printf("tamanho = %d\n",tamanho);
        break;
      case 5:
        printf("Valor: ");
        scanf("%d",&valor);
        removido = buscar(&lista,valor,&posicao);
        if(removido){
          printf("Elemento procurado: %d\n",removido->valor);
          printf("Vizinhos antes: %d\n",posicao);
          printf("Vizinhos depois: %d\n",tamanho - (posicao + 1));
        }
        else{
          printf("%s",MSG);
        }
        break;
      case 6:
        imprimir(lista);
        break;
      case 7:
        printf("Valor: ");
        scanf("%d",&valor);
        int p = produtoDosVizinhos(lista,valor);
        printf("Produto = %d\n",p);
        break;
      default:
        if(op != 0) printf("Opação inválida\n");
    }
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

int produtoDosVizinhos(No *no, int num){
  int produto = 1;
  while(no){
    if(no->valor != num){
      produto *= no->valor;
    }
    no = no->proximo;
  }
  printf("\n");
  return produto;
}

void imprimir(No *no){
  printf("lista: ");
  while(no){
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

int remover(Lista **I, Lista **F, int numero)
{
    Lista *Aux, *No;
    int removeu = 1;

    if (busca(*I, numero))
    {
        inicializarLista(&Aux);
        No = *I;

        while (No != NULL && (*No).numero != numero)
        {
            No = (*No).Prox;
            Aux = No;
        }

        if (No == NULL)
        {
            I = (*I).Prox;
        }
        else
        {
            if ((**F).numero == (*No).numero)
            {
                *F = (*F)->Ant;
                (*F)->Prox = NULL;
            }
            else
            {
                No->Ant->Prox = (*No).Prox;
                (*No).Prox->Ant = (*No).Ant;
            }
        }

        free(Aux);
    }
    else
        removeu = 0;

    return removeu;
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

No *buscar(No **lista, int num, int *posicao){
  No *aux,*no = NULL;
  aux = *lista;
  while(aux && aux->valor != num){
    aux = aux->proximo;
  }
  if(aux){
    no = aux;
    (*posicao)++;
  }
  return no;
}
