#include<stdio.h>
#include<stdlib.h>

void menu(){
  printf("0 - Sair\n");
  printf("1 - inserir\n");
}

#define MSG "Erro na alocação"

typedef struct{
  int cpf;
  char nome[30];
  int idade;
}Pessoa;

typedef struct no{
  Pessoa pessoa;
  struct no *proximo;
  struct no *anterior;
}No;


void imprimir(No *no){
  printf("lista: ");
  while(no){
    printf("%d ",no->cpf);
    no = no->proximo;
  }
  printf("\n");
}

void inserirOrdenado(No **lista, int num,int *tamanho){
  No *aux,*novo = malloc(sizeof(No));
  if(novo){
    novo->->cpf = num;
    if(*lista == NULL){
      novo->proximo = NULL;
      novo->anterior = NULL;
      *lista = novo;
    }
    else if(novo->cpf < (*lista)->cpf){
      novo->proximo = *lista;
      (*lista)->anterior = novo;
      *lista = novo;
    }
    else{
      aux = *lista;
      while(aux->proximo && novo->cpf > aux->proximo->cpf){
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

void cadastroPessoa(Pessoa *p){
  printf("CPF: ");
  scanf("%d",&p->cpf);
  printf("Nome: ");
  scanf("%s",p->nome);
  printf("Idade: ");
  scanf("%d",&p->idade);
}

int main(int argc, char *argv[]){
  int op,valor,anterior,posicao = 0,tamanho = 0;
  No *removido,*lista = NULL;
  Pessoa p = NULL;
  do{
    menu();
    printf(": ");
    scanf("%d",&op);
    printf("\n");
    switch (op) {
      case 1:
        cadastroPessoa(&p);
        //inserirOrdenado(&lista,p,&tamanho);
        break;
      case 2:
        imprimir(lista);
        break;
      default:
        if(op != 0) printf("Opação inválida\n");
    }
  }while(op != 0);
}
