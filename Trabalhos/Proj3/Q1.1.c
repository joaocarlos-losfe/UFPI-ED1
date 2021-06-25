#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

typedef struct Dado* Dado;
typedef struct ListaC* ListaC;

typedef struct
{
	char monomio[10];
} Termo;

struct Dado
{
	Termo termo;
	Dado proximo;
};

struct ListaC
{
	int ID;
	int n_elementos;
	Dado inicio;
	Dado fim;

};

Dado criarDado(char* monomio)
{
	Dado dado = malloc(sizeof(struct Dado));
	dado->termo.monomio[0] = ' ';

	strcpy(dado->termo.monomio, monomio);

	dado->proximo = NULL;
	return dado;
}

Dado apagarDado(Dado dado)
{
	free(dado);
	dado = NULL;
	return dado;
}

void mostrarDado(Dado dado)
{
	printf("%s ", dado->termo.monomio);
}

bool listaVazia(ListaC lista)
{
	return lista->inicio == NULL; // se for null retorna true, se não, falso;
}

ListaC criarLista(int id)
{
	ListaC lista = malloc(sizeof(struct ListaC));

	lista->n_elementos = 0;
	lista->inicio = NULL;
	lista->fim = NULL;
	lista->ID = id;

	return lista;
}

void anexarNaLista(ListaC lista, Dado monomio)
{
	Dado atual = lista->inicio;

	if(atual == NULL)
	{
		lista->inicio = lista->fim = monomio->proximo = monomio;
	}
	else
	{
		monomio->proximo = lista->inicio;
		lista->fim = lista->fim->proximo = monomio;
	}

	lista->n_elementos++;
}

void mostrarLista(ListaC lista)
{
	if (listaVazia(lista))
	{
		printf("lista vazia\n");
	}
	else
	{
		Dado dado = lista->inicio;
		do
		{
			mostrarDado(dado);
			dado = dado->proximo;
		}
		while(dado != lista->inicio );
	}
}


void framentarPolinomio(char *polinomio, ListaC lista)
{
	char monomio_composto[10];
	int i = 0;
	int j = 0;

	while(polinomio[i] != '\0')
	{
		if(polinomio[i] != ' ')
		{
			if (polinomio[i] == '+')
			{
				monomio_composto[j] = '\0';
				Dado dado = criarDado(monomio_composto);
				anexarNaLista(lista, dado);
				j = 0;
			}
			else if (polinomio[i] == '-')
			{
				monomio_composto[j] = '\0';
				Dado dado = criarDado(monomio_composto);
				anexarNaLista(lista, dado);
				monomio_composto[0] = '-';
				j = 1;
			}
			else
			{
				monomio_composto[j] = polinomio[i];
				j++;
			}
		}

		i++;
	}

	if(polinomio[i] == '\0')
	{
		monomio_composto[j] = '\0';
		Dado dado = criarDado(monomio_composto);
		anexarNaLista(lista, dado);
	}
}

void menu()
{
	printf("\n 0 - encerrar programa");
	printf("\n 1 - Cadastrar polinômio");
	printf("\n 2 - Somar 2 polinomios cadastrados");
	printf("\n 3 - Multiplicar 2 polinomios cadastrados");
	printf("\n 4 - Avaliar um dos polinômios cadastrados em função de valores dados para x, y e z,");
	printf("\n 5 - Imprimir a representação de um dos polinômios cadastrados");
	printf("\n 6 - Imprimir a representação de todos os polinômios cadastrados ");
	printf("\n 7 - Calcular a derivada parcial de um dos polinômios cadastrados em relação a qualquer uma das variáveis");
	printf("\n> ");
}


int main(int argc, char** argv)
{
	ListaC lista_polinomios[100];
	int index = 0;
	int op = 1;
	int i = 0;


	int id;
	char polinomio[50];

	do
	{
		menu();
		scanf("%d", &op);

		switch(op)
		{
		case 1:

			printf("\nID da lista: ");
			scanf("%d", &id);
			ListaC lista = criarLista(id);

			printf("\ndigite o polinomio(ex: 2x2 + y4 + 3z2): ");
			setbuf(stdin, NULL);
			scanf(" %[^\n]s", polinomio);
			framentarPolinomio(polinomio, lista);

			lista_polinomios[index] = lista;
			index++;
			break;

		case 6:

			if(index > 0)
			{
				printf("\n");
				for(i = 0; i < index; i++)
				{
					printf("%d ", lista_polinomios[i]->ID);
					mostrarLista(lista_polinomios[i]);
					printf("\n");
				}
			}
			else
				printf("\n nenhum polinomio cadastrado");

		default:
			break;
		}

	}
	while(op != 0);

	return 0;
}
