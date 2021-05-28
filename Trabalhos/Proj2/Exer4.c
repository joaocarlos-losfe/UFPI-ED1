#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <stdbool.h>

typedef struct aux
{
  char dados[100][5];
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

void empilhar(Pilha *pilha, char *str){
  PontPilha expressao = (PontPilha) malloc(sizeof(PilhaExpressoes));
  int t = tamanhoPilha(pilha);
  strcpy(expressao->dados[t],str);
  expressao->proximo = pilha->topo_pilha;
  pilha->topo_pilha = expressao->dados;
}

bool pilhaVazia(Pilha* pilha)
{
  if(pilha->topo_pilha == NULL)
    return true;
  else
    return false;
}

 char* desempilhar(Pilha *pilha){
  PontPilha apagar;
  if(pilhaVazia(pilha)) return;
  else
  {
    apagar = pilha->topo_pilha;
    pilha->topo_pilha = pilha->topo_pilha->proximo;
    free(apagar);
  }
  return apagar;
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
      printf("%s\n",end->dados[i]);
    }
}

bool ehOperador(char *oper){
  char c = oper[0];
  if(c == '+' || c == '-'|| c == '*'|| c == '/'|| c == '(' || c == ')') return true;
  else return false;
}

int pesoOperadores(char *str){
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

void converterPosfixa(Pilha *pilha, Pilha *operadores, Pilha *pilha_pos_fixa){
  int i;
  PontPilha end = pilha->topo_pilha;
  int t = tamanhoPilha(pilha);
  for(i = t; i > 0; i--)
  {
    if(!ehOperador(end->dados[i])){
      empilhar(pilha_pos_fixa, end->dados[i]);
    }
    else if(end->dados[i][0] == '('){
      empilhar(operadores,end->dados[i]);
    }
    else if(end->dados[i][0] == ')')
    {
      char *operador = desempilhar(operadores);
      while(strcmp(operador, "(") != 0 && !pilhaVazia(pilha))
      {
          empilhar(pilha_pos_fixa,operador);
          operador = desempilhar(operadores);
      }
    }
    else
    {
      int tamanho = tamanhoPilha(operadores);
      while (!pilhaVazia(operadores) &&
      pesoOperadores(operadores->topo_pilha->dados[tamanho - 1]) >= pesoOperadores(end->dados[i]))
      {
          empilhar(pilha_pos_fixa, desempilhar(operadores));
      }
      empilhar(operadores, end->dados[i]);
    }
  }
  while (!pilhaVazia(operadores))
  {
      empilhar(pilha_pos_fixa, desempilhar(operadores));
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
        empilhar(&temp,end->dados[i]);
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
  fragmentarStringEmPilha(&pilha, str);
  inverterPilha(&pilha);
  converterPosfixa(&pilha,&operadores,&pilha_pos_fixa);
  //inverterPilha(&pilha_pos_fixa);
  imprimir(&pilha_pos_fixa);


  return 0;
}
