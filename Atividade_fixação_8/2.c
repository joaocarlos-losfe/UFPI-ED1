#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <locale.h>

typedef struct Dado* Dado;
typedef struct Lista* Lista;

typedef struct
{

	int cpf;
	char nome[10];
	int idade;

} Pessoa;


struct Dado
{
	Pessoa pessoa;
	Dado proximo;
	Dado anterior;
};

Dado data_create(int cpf, char *nome, int idade);
Dado data_delete(Dado dado);
void data_print(Dado dado);

struct Lista
{
	unsigned size;
	Dado inicio;
	Dado fim;
};


Lista criarLista();
Lista formatarLista(Lista lista);

void inserirnofinal(Lista lista, Dado dado);
bool listaVazia(Lista lista);
void inserirOrdenado(Lista lista, Dado dado);
void mostrarLista(Lista lista);
Dado removerPosicao(Lista lista, unsigned index);

static Dado removerDe(Lista lista, Dado anterior, Dado atual);

void menu();
void criarOutraLista(Lista principal, Lista nova, int cpf);
int buscarIndex(Lista lista, int cpf);
int devolverVizinhoMaisVelho(Lista lista, int cpf);
void devolverListaMenores(Lista lista, Lista nova, int idade);

int main()
{
	Lista lista = criarLista();
	setlocale(LC_ALL, "");

	int op = 1;
	int cpf;
	char nome[20];
	int idade;

	Lista lista_nova = criarLista();

	do
	{

		menu();
		scanf("%d", &op);

		switch (op)
		{
		case 1:

			printf("\nCPF: ");
			scanf("%d", &cpf);

			setbuf(stdin, NULL);
			printf("\nNome: ");
			scanf(" %[^\n]s", nome);

			printf("\nIdade: ");
			scanf("%d", &idade);

			dado = data_create(cpf, nome, idade);

			inserirOrdenado(lista, dado);

			printf("\nCadastrado !!\n");

			break;

		case 2:
			printf("\n");
			mostrarLista(lista);
			break;

		case 3:

			printf("CPF: ");
			scanf("%d", &cpf);
			criarOutraLista(lista, lista_nova, cpf);

			printf("\n: Nova fila: \n");

			mostrarLista(lista_nova);

			formatarLista(lista_nova);

			break;

		case 4:

			printf("Idade: ");
			scanf("%d", &idade);

			devolverListaMenores(lista, lista_nova, idade);
			printf("\n lista dos menores que a idade informada: \n");
			mostrarLista(lista_nova);

			formatarLista(lista_nova);

			break;

		case 5:
			printf("CPF: ");
			scanf("%d", &cpf);

			int mais_velho = devolverVizinhoMaisVelho(lista, cpf);

			if (mais_velho != 0)
			{
				printf("\na idade do vizinho mais velho eh %d anos\n", mais_velho);
			}
			else
			{
				printf("\nNenhum dos vizinhos é mais velho\n");
			}

		default:
			break;
		}

	}
	while (op != 0);

	return 0;
}

void devolverListaMenores(Lista lista, Lista nova, int idade)
{
	if (listaVazia(lista))
	{
		printf("lista vazia\n");
	}
	else
	{
		Dado dado = lista->inicio;

		while(dado != NULL)
		{

			if (dado->pessoa.idade < idade)
			{
				Dado temp = data_create(dado->pessoa.cpf, dado->pessoa.nome, dado->pessoa.idade);
				inserirOrdenado(nova, temp);
			}

			dado = dado->proximo;
		}

	}
}

int devolverVizinhoMaisVelho(Lista lista, int cpf)
{

	int mais_velho = 0;

	if (listaVazia(lista))
	{
		printf("lista vazia\n");
	}
	else
	{
		Dado dado = lista->inicio;

		while(dado != NULL)
		{

			if(cpf == dado->pessoa.cpf)
			{

				if (dado->proximo != NULL && dado->proximo->pessoa.idade > dado->pessoa.idade)
				{
					mais_velho = dado->proximo->pessoa.idade;
				}
				else if(dado->anterior != NULL && dado->anterior->pessoa.idade > dado->pessoa.idade)
				{
					mais_velho = dado->anterior->pessoa.idade;
				}
				else
				{
					mais_velho = 0;
				}

			}

			dado = dado->proximo;

		}

	}

	return mais_velho;
}

void criarOutraLista(Lista principal, Lista nova, int cpf)
{
	if (listaVazia(principal))
	{
		printf("lista vazia\n");
	}
	else
	{
		Dado dado = principal->inicio;

		bool achou = false;

		int index = -1;

		while(dado != NULL)
		{
			if (cpf == dado->pessoa.cpf)
				achou = true;

			if (achou && cpf != dado->pessoa.cpf)
			{
				inserirnofinal(nova, dado);

				index = buscarIndexCPF(principal, dado->pessoa.cpf);

			}

			dado = dado->proximo;

			if (achou && index != -1)
			{
				removerPosicao(principal, index);
			}

		}

	}

}

int buscarIndexCPF(Lista lista, int cpf)
{
	int index = -1;
	int count = 0;

	if (listaVazia(lista))
	{
		printf("lista vazia!!\n");
	}
	else
	{
		Dado dado = lista->inicio;

		while(dado != NULL)
		{

			if (cpf == dado->pessoa.cpf)
			{
				index = count;
				break;
			}

			count ++;
			dado = dado->proximo;
		}
	}

	return index;
}


void menu()
{
	printf("\n 0 - encerrar programa");
	printf("\n 1 - cadastrar pessoa");
	printf("\n 2 - mostrar lista de pessoas\n");
	printf("\n 3 - crie uma outra lista contendo somente as pessoas que estão depois dela na fila");
	printf("\n 4 - Devolver uma lista ordenada contendo somente as pessoas menores do que uma idade informada");
	printf("\n 5 - devolva a idade do vizinho mais velho desta pessoa e devolva também se ele é mais velho do que a pessoa informada\n > ");
}

Dado data_create(int cpf, char *nome, int idade)
{
	Dado dado = malloc(sizeof(struct Dado));

	dado->pessoa.cpf = cpf;
	strcpy(dado->pessoa.nome, nome);
	dado->pessoa.idade = idade;

	dado->proximo = NULL;
	dado->anterior = NULL;
	return dado;
}

Dado data_delete(Dado dado)
{
	free(dado);
	dado = NULL;
	return dado;
}

void data_print(Dado dado)
{
	printf("CPF: %d, Nome: %s, Idade: %d\n", dado->pessoa.cpf, dado->pessoa.nome, dado->pessoa.idade);
}

Lista criarLista()
{
	Lista lista = malloc(sizeof(struct Lista));
	lista->size = 0;
	lista->inicio = NULL;
	lista->fim = NULL;
	return lista;
}

Lista formatarLista(Lista lista)
{

	Dado tmp = lista->inicio;

	while (tmp != NULL)
	{
		lista->inicio = tmp->proximo;
		tmp = data_delete(tmp);
		tmp = lista->inicio;
	}

	free(lista);
	lista = NULL;
	return lista;
}

void inserirnofinal(Lista lista, Dado dado)
{
	Dado ultimo = lista->fim;

	if(ultimo == NULL)
	{
		lista->inicio = lista->fim = dado;
	}
	else
	{
		dado->anterior = ultimo;
		ultimo->proximo = lista->fim = dado;
	}

	lista->size++;
}

static void inserirDentroDe(Lista lista, Dado anterior, Dado atual, Dado dado)
{
	dado->proximo = atual;
	dado->anterior = anterior;

	if (atual != NULL)
	{
		atual->anterior = dado;
	}
	else
	{
		lista->fim = dado;
	}
	if(anterior == NULL)
	{
		lista->inicio = dado;
	}
	else
	{
		anterior->proximo = dado;
	}
	lista->size++;
}

void inserirOrdenado(Lista lista, Dado dado)
{

	Dado anterior = NULL;
	Dado atual = lista->inicio;

	while ((atual != NULL) && (atual->pessoa.cpf < dado->pessoa.cpf))
	{
		anterior = atual;
		atual = atual->proximo;
	}

	inserirDentroDe(lista, anterior, atual, dado);
}


bool listaVazia(Lista lista)
{
	return lista->inicio == NULL;
}


void mostrarLista(Lista lista)
{
	if (listaVazia(lista))
	{
		printf("empty lista\n");
	}
	else
	{
		Dado dado = lista->inicio;

		while(dado != NULL)
		{
			data_print(dado);
			dado = dado->proximo;
		}
	}
}


static Dado removerDe(Lista lista, Dado anterior, Dado atual)
{
	if (anterior == NULL)
	{
		lista->inicio = atual->proximo;
	}
	else
	{
		anterior->proximo = atual->proximo;
	}
	if (atual->proximo != NULL)
	{
		atual->proximo->anterior = anterior;
	}
	else
	{
		lista->fim = anterior;
	}

	atual->anterior = atual->proximo = NULL;
	lista->size--;
	return atual;
}

Dado removerPosicao(Lista lista, unsigned index)
{

	Dado atual = lista->inicio;

	Dado anterior = NULL;

	while ((atual->proximo != NULL) && ( index > 0))
	{
		anterior = atual;
		atual = atual->proximo;
		index--;
	}

	return (atual != NULL) ? removerDe(lista, anterior, atual) : NULL;
}