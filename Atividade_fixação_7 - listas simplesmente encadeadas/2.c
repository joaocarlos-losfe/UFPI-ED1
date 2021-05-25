#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void menu(){
  printf("0 - Sair\n");
  printf("1 - Inserir\n");
  printf("2 - Imprimir\n");
  printf("3 - Dividir em vogal e consoante\n");
  printf("5 - Ver strings vizinhas\n");
}

typedef struct No{
	char string[30];
	struct No *proximo;
}No;

typedef struct{
	No *inicio;
	int tam;
}Lista;
void inserir(Lista *lista,char *string);
void inserirFinal(Lista *lista,char *string);
void imprimir(Lista *lista);
int vogalIs(char c);
void vogalConsoante(Lista * lista, Lista *vogal, Lista *consoante);
int stringVizinha(Lista *lista, char *str,char *str1,char *str2);

int main(int argc, char *argv[]){

  Lista lista,lista_vogais,lista_consoantes;
  lista.inicio = NULL;
  lista.tam = 0;

  lista_vogais.inicio = NULL;
  lista_vogais.tam = 0;

  lista_consoantes.inicio = NULL;
  lista_consoantes.tam = 0;

  char string[30];
  char str1[20];
  char str2[20];

  int op;
	do{
    menu();
		scanf("%d",&op);
		switch(op){
      case 1:
        printf("String: ");
        scanf("%s",string);
        //inserirFinal(&lista,string);
        inserir(&lista,string);
        break;
      case 2:
        imprimir(&lista);
        break;
      case 3:
        vogalConsoante(&lista,&lista_vogais,&lista_consoantes);
        printf("Lista original\n");
        imprimir(&lista);
        printf("Lista vogal\n");
        imprimir(&lista_vogais);
        printf("Lista consoante\n");
        imprimir(&lista_consoantes);
        break;
      case 4:
        break;
      case 5:
        printf("String: ");
        scanf("%s",string);
        int u = stringVizinha(&lista,string,str1,str2);
        if(u == 0){
          printf("Sucessor de %s: %s\n",string,str2);
        }
        else
        if(u == 1){
          printf("Anterior de %s: %s\n",string,str1);
        }
        else
        if(u == 2){
          printf("Anterior de %s: %s\n",string,str1);
          printf("Sucessor de %s: %s\n",string,str2);
        }
        else{
          printf("%s não está na lista\n",string);
        }
        break;
      default:
        break;
    }
    printf("\n");
  }while (op!=0);
  return 0;
}

int stringVizinha(Lista *lista, char *str,char *str1,char *str2){
  No *antes,*inicio = lista->inicio;
  int status;
	while(inicio != NULL){
    if(strcmp(inicio->string,str) == 0){
      if(inicio == lista->inicio){
        inicio = inicio->proximo;
        strcpy(str2, inicio->string);
        status = 0;
      }
      else
      if(inicio->proximo == NULL){
        strcpy(str1, antes->string);
        status = 1;
      }
      else{
        strcpy(str1, antes->string);
        inicio = inicio->proximo;
        strcpy(str2, inicio->string);
        status = 2;
      }
    }
    antes = inicio;
    inicio = inicio->proximo;
	}
  return status;
}

int vogalIs(char c){
  if(c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u') return 0;
  return 1;
}

void vogalConsoante(Lista * lista, Lista *vogal, Lista *consoante){
  No *inicio = lista->inicio;
	printf("Tamanho da lista: %d\n",lista->tam);
	while(inicio != NULL){
    if(vogalIs(inicio->string[0]) == 0){
      inserirFinal(vogal,inicio->string);
    }
    else{
      inserirFinal(consoante,inicio->string);
    }
    inicio = inicio->proximo;
	}
	printf("\n");
}

void imprimir(Lista *lista){
	No *inicio = lista->inicio;
	printf("Tamanho da lista: %d\n",lista->tam);
	while(inicio != NULL){
		printf("%s ", inicio->string);
    inicio = inicio->proximo;
	}
	printf("\n\n");
}

void inserirFinal(Lista *lista,char *string){
	No *no,*novo = (No*)malloc(sizeof(No));
	strcpy(novo->string,string);
	novo->proximo = NULL;

	if(lista->inicio == NULL){
		lista->inicio = novo;
	}
	else{
		no = lista->inicio;
		while(no->proximo != NULL){
			no = no->proximo;
		}
		no->proximo = novo;
	}
	lista->tam++;
}

void inserir(Lista *lista,char *string)
{
	No *atual, *novo, *anterior;

	novo = (No *) malloc(sizeof(No));

	atual = lista->inicio;
	anterior = NULL;

	strcpy(novo->string,string);
	novo->proximo = NULL;

	if(atual == NULL){
		novo->proximo = NULL;
		lista->inicio = novo;
	}
	else{
		while(atual != NULL && strlen(atual->string) < strlen(string)){
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
