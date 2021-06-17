#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>

typedef struct{
  int cpf;
  char nome[10];
  int idade;
}Pessoa;

typedef struct no{
  Pessoa pessoa;
  struct no *proximo;
  struct no *anterior;
}No;

void cadastroPessoa(Pessoa *pessoa,int cpf,char *nome, int id){
  pessoa = malloc(sizeof(Pessoa));
  (pessoa)->cpf = cpf;
  strcpy((pessoa)->nome,nome);
  (pessoa)->idade = id;
}

void inserirOrdenado(No **lista, Pessoa *p,int *tamanho){
  No *aux,*novo = malloc(sizeof(No));
  if(novo){
    novo->pessoa->cpf = p->cpf;
    if(*lista == NULL){
      novo->proximo = NULL;
      novo->anterior = NULL;
      *lista = novo;
    }
    else if(novo->pessoa->cpf < (*lista)->pessoa->cpf){
      novo->proximo = *lista;
      (*lista)->anterior = novo;
      *lista = novo;
    }
    else{
      aux = *lista;
      while(aux->proximo && novo->pessoa->cpf > aux->proximo->pessoa->cpf){
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
    printf("deu erro\n");
  }
}

int main(){
  No *lista = NULL;
  Pessoa p;
  int t = 0;
  cadastroPessoa(&p,1,"vitor",21);
  return 0;
}
