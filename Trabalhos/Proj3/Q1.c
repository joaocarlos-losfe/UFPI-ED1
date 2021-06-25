#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	int coeficiente;
	char variavel;
	int expoente;
} Termo;

typedef struct No
{
	Termo polinomio;
	struct No *proximo;
} No;

typedef struct
{
	No *inicio;
	No *fim;
	int tam;
} Lista;

void menu();
void inserirFinal(Lista *lista, Termo t);
void criar_lista(Lista *lista);
void imprimir(Lista lista);
void cadastroMonomio(Termo *t);
void imprimirNo(No *no);

void somaPolinomios(No *no1, No *no2)
{
	int i = 0;
	int soma;
  imprimirNo(no1);
  printf("+\n");
  imprimirNo(no2);
  printf("-------------------------------------------");
  if(no1 != NULL || no2 != NULL)
  {
    while(i < 4)
    {
      if(no1->polinomio.variavel == no2->polinomio.variavel){
        soma = no1->polinomio.coeficiente + no2->polinomio.coeficiente;

        if(no1->polinomio.expoente == no2->polinomio.expoente)
        {
          if(soma >= 0){
            printf("+");
            printf("%d%c^%d\n", soma,no1->polinomio.variavel,no1->polinomio.expoente);
          }
        }
        else{
          if(i > 0){
            if(no1->polinomio.expoente >= 0 || no2->polinomio.expoente >= 0) printf("+");
            printf("%d%c^%d\n", soma,no1->polinomio.variavel,no1->polinomio.expoente);
          }
        }
      }
      i++;
    }
    no1 = no1->proximo;
    no2 = no2->proximo;
  }
}



void imprimirNo(No *no)
{
	if(no != NULL)
	{
			printf("%d", no->polinomio.coeficiente);
			printf("%c", no->polinomio.variavel);
			if(no->polinomio.expoente != 0)
			{
				printf("%d", no->polinomio.expoente);
			}
			no = no->proximo;
		}
	printf("\n");
}

int main(int argc, char **argv[])
{

	Lista lista;
  No *vetorPoli[100];
	Termo t;
	criar_lista(&lista);
	int termos, op, contador = 1, p1, p2;

	do
	{
		menu();
		scanf("%d", &op);
		if(op == 0)
		{
			exit(1);
		}
		else if(op == 1)
		{
			printf("termos do polinomio:	");
			scanf("%d", &termos);
			for(int i = 0; i < termos; i++)
			{
				cadastroMonomio(&t);
				inserirFinal(&lista, t);
			}
			vetorPoli[contador] = lista.inicio;
      imprimirNo(vetorPoli[contador]);
			contador++;
		}
		else if(op == 2)
		{
			if(lista.tam >= 2)
			{
				printf("Somar polinomios\n");
				printf("Número do polinomio:	");
				scanf("%d", &p1);
				printf("Número do polinomio:	");
				scanf("%d", &p2);
				somaPolinomios(vetorPoli[p1], vetorPoli[p2]);
			}
			else
			{
				printf("Para somar é preciso ter 2 ou mais polinômios\n");
			}
		}
		else if(op == 3)
		{
			imprimir(lista);
		}
		else
		{
			printf("erro de entrada!\n");
		}
	}
	while(op != 0);
	return 0;
}


void menu()
{
	printf("[0] - Sair\n");
	printf("[1] - Cadastrar Polinomio\n");
	printf("[2] - Somar 2 polinomios\n");
	printf("[3] - Imprimir\n");
}

void inserirFinal(Lista *lista, Termo t)
{
	No *no, *novo = (No*)malloc(sizeof(No));
	novo->polinomio = t;
	if(lista->inicio == NULL)
	{
		lista->inicio = novo;
		lista->fim = novo;
		lista->fim->proximo = lista->inicio;
	}
	else
	{
		lista->fim->proximo = novo;
		lista->fim = novo;
		novo->proximo = lista->inicio;
	}
	lista->tam++;
}

void criar_lista(Lista *lista)
{
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->tam = 0;
}

void imprimir(Lista lista)
{
	No *no;
	no = lista.inicio;
	if(no != NULL)
	{
		do
		{
			printf("%d", no->polinomio.coeficiente);
			printf("%c", no->polinomio.variavel);
			if(no->polinomio.expoente != 0)
			{
				printf("%d", no->polinomio.expoente);
			}
      printf("\n");
			no = no->proximo;
		}
		while(no != lista.inicio);
	}
	printf("\n");
}

void cadastroMonomio(Termo *t)
{
	int coeficiente, expoente, ultimo;
	char sinal;
	char variavel;
	printf("Criar um Monomio\n");
	printf("Coeficiente:	");
	scanf(" %d", &t->coeficiente);
	fflush(stdin);
	printf("Variável:	");
	scanf(" %c", &t->variavel);
	fflush(stdin);
	printf("Expoente:	");
	scanf(" %d", &t->expoente);
	fflush(stdin);
}
