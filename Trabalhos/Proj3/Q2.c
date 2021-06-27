#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>

typedef struct ListaCDE* ListaCDE;
typedef struct Dado* Dado;

typedef struct
{
	int codigo;
	char descricao[40];
	int quantidade;

} Premio;

struct Dado
{
	Premio premio;
	Dado proximo;
	Dado anterior;
};

struct ListaCDE
{
	int qtd_dados;
	Dado inicio;
	Dado fim;
};

Dado novoDado(int codigo, char *descricao, int quantidade)
{
	Dado dado = malloc(sizeof(struct Dado));

	dado->premio.codigo = codigo;
	strcpy(dado->premio.descricao, descricao);
	dado->premio.quantidade = quantidade;

	dado->proximo = NULL;
	dado->anterior = NULL;

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
	printf("\n\n >>> %s <<< codigo: %d, quantidade restante: %d", dado->premio.descricao, dado->premio.codigo, dado->premio.quantidade);
}

ListaCDE criarLista()
{
	ListaCDE lista = malloc(sizeof(struct ListaCDE));

	lista->qtd_dados = 0;
	lista->inicio = NULL;
	lista->fim = NULL;

	return lista;
}

bool lista_eh_vazia(ListaCDE lista)
{
	return lista->inicio == NULL;
}

void inserirEntre(ListaCDE lista, Dado atual, Dado dado, bool eh_primeiro)
{

	dado->proximo = atual;
	atual->anterior->proximo = dado;
	dado->anterior = atual->anterior;
	atual->anterior = dado;

	if(eh_primeiro)
	{
		lista->inicio = dado;
	}
	else if (atual == lista->fim)
	{
		lista->fim = dado;
	}

}

void inserirOrdenado(ListaCDE lista, Dado dado)
{

	Dado atual = lista->inicio;

	if(atual == NULL)
	{
		dado->anterior = dado->proximo = dado;
		lista->inicio = lista->fim = dado;
	}
	else
	{
		bool eh_primeiro = atual->premio.codigo >= dado->premio.codigo;

		do
		{
			if(atual->premio.codigo >= dado->premio.codigo)
			{
				break;
			}

			atual = atual->proximo;

		}
		while(atual != lista->inicio);

		inserirEntre(lista, atual, dado, eh_primeiro);
	}

	lista->qtd_dados++;
}

void mostrarLista(ListaCDE lista)
{
	if (lista_eh_vazia(lista))
	{
		printf("\nlista vazia...");
	}
	else
	{
		Dado dado = lista->inicio;
		do
		{
			mostrarDado(dado);
			dado = dado->proximo;
		}
		while(dado != lista->inicio);
	}
}

Dado removerDoInicio(ListaCDE lista)
{
	Dado atual = lista->inicio;

	if(atual != NULL)
	{
		if(atual == lista->fim)
		{
			lista->inicio = lista->fim = NULL;
		}
		else
		{
			lista->fim->proximo = lista->inicio = atual->proximo;
			lista->inicio->anterior = lista->fim;

		}

		atual->anterior = atual->proximo = NULL;

		lista->qtd_dados--;
	}

	return atual;
}

Dado removerApartirDe(ListaCDE lista, Dado atual, bool eh_primeiro)
{
	if (eh_primeiro)
	{
		return removerDoInicio(lista);
	}

	atual->anterior->proximo = atual->proximo;
	atual->proximo->anterior = atual->anterior;

	if(atual == lista->fim)
		lista->fim = atual->anterior;

	lista->qtd_dados--;

	atual->proximo = atual->anterior = NULL;

	return atual;
}


Dado removerPorCodigo(ListaCDE lista, int codigo)
{

	Dado atual = lista->inicio;

	if (atual != NULL)
	{
		bool eh_primeiro = atual->premio.codigo == codigo;

		do
		{
			if (atual->premio.codigo == codigo) break;

			atual = atual->proximo;

		}
		while (atual != lista->inicio);

		atual = (atual->premio.codigo == codigo) ? removerApartirDe(lista, atual, eh_primeiro) : NULL;
	}

	return atual;
}

Dado girarRoleta(int *flag, Dado dado)
{

	int roleta_voltas = rand() % 100;
	int i;

	printf("\n girando apartir de >>> %s <<<", dado->premio.descricao);

	if(dado != NULL)
	{
		if((*flag) == 1)
		{
			printf("\n girando em sentido Horario");

			(*flag) = 0;

			for(i = 0; i < roleta_voltas; i++)
			{
				dado = dado->proximo;
			}
		}
		else if ((*flag == 0))
		{
			printf("\n girando em sentido ANTI Horario");

			(*flag) = 1;

			for(i = 0; i < roleta_voltas; i++)
			{
				dado = dado->anterior;
			}
		}
	}

	return dado;
}

void menu()
{
	printf("\n\n0 - Sair");
	printf("\n1 - Cadastrar premio");
	printf("\n2 - Girar roleta");
	printf("\n3 - Mostrar lista de premios\n> ");
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");

	Dado dado;
	ListaCDE lista;

	lista = criarLista();

	/*

	dado = novoDado(333, "camisa", 2);
	inserirOrdenado(lista, dado);

	dado = novoDado(111, "bone", 3);
	inserirOrdenado(lista, dado);

	dado = novoDado(222, "frango", 1);
	inserirOrdenado(lista, dado);

	removerPorCodigo(lista, 222);

	dado = novoDado(666, "10% de desconto", 5);
	inserirOrdenado(lista, dado);

	dado = novoDado(444, "nokia lanterninha", 6);
	inserirOrdenado(lista, dado);

	dado = novoDado(555, "botijao de gas", 4);
	inserirOrdenado(lista, dado);

	*/

	int op = 1;


	Dado premio;

	int flag = 1;

	int codigo = 0;
	char descricao[40];
	int qtd = 0;

	do
	{
		menu();
		scanf("%d", &op);

		switch(op)
		{

		case 1:
			printf("\n codigo: ");
			scanf("%d", &codigo);
			printf("\n descri��o do premio: ");
			setbuf(stdin, NULL);
			scanf(" %[^\n]s", descricao);
			printf("\n quantidade: ");
			scanf("%d", &qtd);

			dado = novoDado(codigo, descricao, qtd);

			inserirOrdenado(lista, dado);

			if (lista->qtd_dados == 1)
			{
				premio = lista->inicio;
			}

			printf("\n Premio cadastrado com sucesso...");
			break;

		case 2:

			if(!lista_eh_vazia(lista))
			{
				premio = girarRoleta(&flag, premio);
				printf("\n\n Premio ganho: ");
				premio->premio.quantidade--;
				mostrarDado(premio);

				if(premio->premio.quantidade == 0)
				{
					int codigo_remover = premio->premio.codigo;
					premio = premio->proximo;
					removerPorCodigo(lista, codigo_remover);
					printf("\n Quantidade desse premio chegou a 0 !!. Retirado da roleta");
				}

			}
			else
			{
				printf("\n roleta vazia !!");
			}

			break;

		case 3:
			mostrarLista(lista);
			break;
		}

	}
	while(op != 0);


	return 0;
}
