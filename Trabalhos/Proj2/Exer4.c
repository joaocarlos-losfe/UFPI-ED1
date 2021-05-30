#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct aux
{
  char dados[20];
  struct PilhaExpressoes *proximo;

}PilhaExpressoes, *PontPilha;

typedef struct
{
  PontPilha topo_pilha;
}Pilha;

int tamanhoPilha(Pilha *pilha)
{
  int cont = 0;

  PontPilha end = pilha->topo_pilha;

  while(end!=NULL)
  {
    cont++;
    end = end->proximo;
  }
  return cont;
}

bool pilhaVazia(Pilha* pilha)
{
  if(pilha->topo_pilha == NULL)
    return true;
  else
    return false;
}

void empilhar(Pilha *pilha, char *str){
  PontPilha expressao = (PontPilha) malloc(sizeof(PilhaExpressoes));
  strcpy(expressao->dados,str);
  expressao->proximo = pilha->topo_pilha;
  pilha->topo_pilha = expressao;
}

void desempilhar(Pilha *pilha, char *str){
  if(pilhaVazia(pilha)) return;
  else
  {
    PontPilha apagar = pilha->topo_pilha;
    strcpy(str,apagar->dados);
    pilha->topo_pilha = pilha->topo_pilha->proximo;
    free(apagar);
  }
}

void imprimir(Pilha* pilha)
{
    int count = 1;
    PontPilha end = pilha->topo_pilha;
    int t = tamanhoPilha(pilha);

    if(pilhaVazia(pilha))
    {
        printf("Pilha vazia...\n");
        return;
    }
    int i;
    for(i = t; i >= 0; i--)
    {
      printf("%s\n",end->dados);
    }
}

bool ehOperador(char *oper)
{
  char c = oper[0];
  if(c == '+' || c == '-'|| c == '*'|| c == '/'|| c == '(' || c == ')') return true;
  else return false;
}

int pesoOperadores(char *str)
{
  int peso;
  char c = str[0];
  if(c == '*'|| c == '/') peso = 3;
  else if(c == '+'|| c == '-') peso = 2;
  else peso = 1;
  return peso;
}

void fragmentarStringEmPilha(Pilha *pilha, char *str_expressao)
{
  int i, k = 0;
  char str_composta[5];
  for(i = 0; i <= strlen(str_expressao); i++){
    if(str_expressao[i] != ' '){
      str_composta[k] = str_expressao[i];
      k++;
    }
    else{
      str_composta[k] = '\0';
      k = 0;
      empilhar(pilha,str_composta);
    }
  }
  empilhar(pilha,str_composta);
}

void converterPosfixa(Pilha *pilha, Pilha *operadores, Pilha *pilha_pos_fixa)
{
  int i;
  PontPilha end = pilha->topo_pilha;
  int t = tamanhoPilha(pilha);
  char *operador;
  for(i = t; i > 0; i--)
  {
    if(!ehOperador(end->dados)){
      empilhar(pilha_pos_fixa, end->dados);
    }
    else if(end->dados == "("){
      empilhar(operadores,end->dados);
    }
    else if(end->dados == ")")
    {
      desempilhar(operadores,operador);
      while(strcmp(operador, "(") != 0 && !pilhaVazia(pilha))
      {
        empilhar(pilha_pos_fixa,operador);
        desempilhar(operadores,operador);
      }
    }
    else
    {
      int tamanho = tamanhoPilha(operadores);
      while (!pilhaVazia(operadores) &&
      pesoOperadores(operadores->topo_pilha->dados) >= pesoOperadores(end->dados))
      {
        desempilhar(operadores,operador);
        empilhar(pilha_pos_fixa, operador);
      }
      empilhar(operadores, end->dados);
    }
  }
  while (!pilhaVazia(operadores))
  {
    desempilhar(operadores,operador);
    empilhar(pilha_pos_fixa,operador);
  }
}

void inverterPilha(Pilha *pilha)
{
    Pilha temp;
    temp.topo_pilha = NULL;

    PontPilha end = pilha->topo_pilha;
    int t = tamanhoPilha(pilha);

    int i;

    for(i = t; i <= 0; i--)
    {
        empilhar(&temp,end->dados);
    }

    *pilha = temp;
}

int main(int argc, char *argv[]){
  Pilha pilha;
  pilha.topo_pilha = NULL;

  Pilha operadores;
  operadores.topo_pilha = NULL;

  Pilha pilha_pos_fixa;
  pilha_pos_fixa.topo_pilha = NULL;


  char str[] = "(3 + 1 * (3 * 1))";
  empilhar(&pilha,str);
  printf("tamanho = %d\n",tamanhoPilha(&pilha));
  fragmentarStringEmPilha(&pilha,str);
  printf("tamanho = %d\n",tamanhoPilha(&pilha));
  inverterPilha(&pilha);
  printf("tamanho = %d\n",tamanhoPilha(&pilha));
  converterPosfixa(&pilha,&operadores,&pilha_pos_fixa);
  imprimir(&pilha_pos_fixa);
  printf("tamanho = %d\n",tamanhoPilha(&pilha));
  inverterPilha(&pilha_pos_fixa);
  printf("tamanho = %d\n",tamanhoPilha(&pilha));
  
  return 0;
}
