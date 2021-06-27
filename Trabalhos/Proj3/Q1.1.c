#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

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

int indexPolinomiolista(ListaC* lista_polinomios, int qtd_polinomios, int ID)
{
	int i = 0;
	int index = -1;

	for (i = 0; i < qtd_polinomios; i++)
	{
		if(ID == lista_polinomios[i]->ID)
		{
			index = i;
			break;
		}
	}
	return index;
}

void mostrarListaPolinomios(ListaC* lista_polinomios, int qtd_polinomios)
{
	int i = 0;

	if(qtd_polinomios > 0)
	{
		printf("\n");
		for(i = 0; i < qtd_polinomios; i++)
		{
			printf("id: %d\n", lista_polinomios[i]->ID);
			printf("polinomio: ");
			mostrarLista(lista_polinomios[i]);
			printf("\n\n");
		}

	}
	else
		printf("\n nenhum polinomio cadastrado\n");
}

void extrairCoeficiente(char *monomio, char *coeficiente, char *resto)
{
	int i = 0;
	strcpy(coeficiente, "");
	strcpy(resto, "");

	while(isdigit(monomio[i]) )
	{
		coeficiente[i] = monomio[i];
		i++;
	}
	coeficiente[i] = '\0';

	strcat(resto, monomio + i);

}

int strtoint(char* str)
{
	if(strcmp(str, "") == 0)
	{
		return 0;
	}
	return atoi(str);
}
int possuiTermoResto(ListaC polinomio, char* resto)
{

	Dado monomio = polinomio->inicio;
	char coeficiente[10];
	char resto_monomio[10];
	int possui_resto = 0;

	do
	{
		extrairCoeficiente(monomio->termo.monomio, coeficiente, resto_monomio);
		if(strcmp(resto, resto_monomio) == 0)
		{
			possui_resto = 1;
			break;
		}
		monomio = monomio->proximo;

	}
	while(monomio != polinomio->inicio);

	return possui_resto;
}
void formatarTermo(char *termo, int coeficiente, char *resto)
{
	if(coeficiente == 0)
	{
		strcpy(termo, resto);
	}
	else
	{
		sprintf(termo, "%d%s", coeficiente, resto); // converte pra string de volta
	}
}
void somarPolinomios(ListaC polinomio1, ListaC polinomio2)
{
	printf("\npolinomio 1: ");
	mostrarLista(polinomio1);

	printf("\npolinomio 2: ");
	mostrarLista(polinomio2);

	Dado monomio1 = polinomio1->inicio;
	Dado monomio2 = polinomio2->inicio;

	char coeficientes[2][10];
	char restos[2][10];

	int coeficiente_numerico[2];

	Dado dado;

	ListaC polinomio_resultante;
	polinomio_resultante = criarLista(0);

	char termo_resultante[10];

	do
	{
		extrairCoeficiente(monomio1->termo.monomio, coeficientes[0], restos[0]);

		coeficiente_numerico[0] = strtoint(coeficientes[0]);

		do
		{
			extrairCoeficiente(monomio2->termo.monomio, coeficientes[1], restos[1]);
			coeficiente_numerico[1] = strtoint(coeficientes[1]);

			if(strcmp(restos[0], restos[1]) == 0)
			{
				coeficiente_numerico[0] += coeficiente_numerico[1];
			}
			monomio2 = monomio2->proximo;

		}
		while(monomio2 != polinomio2->inicio);

		formatarTermo(termo_resultante, coeficiente_numerico[0], restos[0]);

		dado = criarDado(termo_resultante);
		anexarNaLista(polinomio_resultante, dado);

		monomio1 = monomio1->proximo;

	}
	while(monomio1 != polinomio1->inicio);

	/*verifica se algum resto de termo do segundo nao existe no primeiro*/

	do
	{
		extrairCoeficiente(monomio2->termo.monomio, coeficientes[1], restos[1]);

		if(possuiTermoResto(polinomio1, restos[1]))
		{

			formatarTermo(termo_resultante, coeficiente_numerico[1], restos[1]);
			dado = criarDado(termo_resultante);
			anexarNaLista(polinomio_resultante, dado);
		}

		monomio2 = monomio2->proximo;
	}
	while(monomio2 != polinomio2->inicio);


	printf("\n\n");
	mostrarLista(polinomio_resultante);
}

int main(int argc, char** argv)
{
	ListaC lista_polinomios[100];
	int index = 0;
	int op = 1;

	int id;
	char polinomio[50];
	int id1, id2;
	int index_busca1 = -1;
	int index_busca2 = -1;

	ListaC lista = criarLista(111);
	framentarPolinomio("3xy + 2x + z", lista);
	lista_polinomios[index] = lista;
	index++;

	lista = criarLista(222);
	framentarPolinomio("3x2 + x + 4z + 5", lista);
	lista_polinomios[index] = lista;
	index++;

	lista = criarLista(333);
	framentarPolinomio("53x2 + 8y3 + 2z4", lista);
	lista_polinomios[index] = lista;
	index++;

	char coeficiente[10];
	char resto[10];

	somarPolinomios(lista_polinomios[0], lista_polinomios[1]);

	/*

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

		case 2:

			mostrarListaPolinomios(lista_polinomios, index);
			printf("digite o id para selecionar o primeiro polinomio: ");
			scanf("%d", &id1);
			printf("digite o id para selecionar o segundo polinomio: ");
			scanf("%d", &id2);

			index_busca1 = indexPolinomiolista(lista_polinomios, index, id1);
			index_busca2 = indexPolinomiolista(lista_polinomios, index, id2);

			if(index_busca1 != -1 && index_busca2 != -1)
			{
				somarPolinomios(lista_polinomios[index_busca1], lista_polinomios[index_busca2]);
			}

			break;

		case 6:

			mostrarListaPolinomios(lista_polinomios, index);

		default:
			break;
		}

	}
	while(op != 0);

	*/


	return 0;
}
