#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

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


int main(int argc, char** argv)
{
	ListaC lista_polinomios[100];
	int index = 0;
	
	ListaC lista = criarLista(111);
	
	char polinomio[] = "3x2 + 5x - 3x3 + 5";
	
	framentarPolinomio(polinomio, lista);
	
	lista_polinomios[index] = lista;
	index++;
	
	lista = criarLista(222);
	
	char polinomio2[] = "4x2 + 7x4 - 6x2 + 6";
	
	framentarPolinomio(polinomio2, lista);
	
	lista_polinomios[index] = lista;
	
	index++;
	
	//mostrarLista(lista_polinomios[0]);
	
	int i;
	
	for(i=0; i<index; i++)
	{
		mostrarLista(lista_polinomios[i]);
		printf("\n");
	}
	
	return 0;
}
