#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct Dado* Dado;
typedef struct ListaCDE* ListaCDE;


typedef struct
{
	int codigo;
	char descricao[40];
	int qtd;

} Premio;

struct Dado
{
	Premio premio;
	Dado prox;
	Dado anterior;
};

struct ListaCDE
{
	Dado inicio;
	Dado fim;
	int qtd_dados;
};

ListaCDE iniciarLista()
{
	ListaCDE nova_lista = malloc(sizeof(struct ListaCDE));

	nova_lista->inicio = NULL;
	nova_lista->inicio = NULL;
	nova_lista->qtd_dados = 0;

	return nova_lista;
}

void inserir_final(ListaCDE lista, Premio premio)
{

	Dado novo_dado = malloc(sizeof(struct Dado));
	novo_dado->premio = premio;

	if (lista->qtd_dados == 0)
	{
		lista->inicio = novo_dado;
		lista->fim = novo_dado;
		lista->qtd_dados = lista->qtd_dados + 1;

	}
	else if (lista->qtd_dados == 1)
	{
		lista->inicio->prox = novo_dado;
		lista->inicio->anterior = novo_dado;
		lista->fim = novo_dado;
		novo_dado->anterior = lista->inicio;
		novo_dado->prox = lista->inicio;
		lista->qtd_dados = lista->qtd_dados + 1;
	}
	else
	{
		lista->inicio->anterior = novo_dado;
		novo_dado->prox = lista->inicio;
		novo_dado->anterior = lista->fim;
		lista->fim->prox = novo_dado;
		lista->fim = novo_dado;
		lista->qtd_dados = lista->qtd_dados + 1;
	}
}

void buscar_remove(ListaCDE lista, int codigo)
{
	Dado dado_end = lista->inicio;

	while(dado_end->prox != lista->inicio)
	{
		if(dado_end->premio.codigo == codigo)
		{

			if(dado_end == lista->inicio)
			{
				lista->inicio = dado_end->prox;
				lista->fim->prox = lista->inicio;
				lista->inicio->anterior = lista->fim;
				lista->qtd_dados -= 1;
				free(dado_end);
				return;
			}
			else
			{
				dado_end->anterior->prox = dado_end->prox;
				dado_end->prox->anterior = dado_end->anterior;
				lista->qtd_dados -= 1;
				free(dado_end);
				return;
			}

		}

		dado_end = dado_end->prox;
	}

	if(dado_end->premio.codigo == codigo && dado_end == lista->fim)
	{
		lista->inicio->anterior = lista->fim->anterior;
		lista->fim = lista->inicio->prox;
		lista->fim->prox = lista->inicio;
		lista->qtd_dados -= 1;
		free(dado_end);
		return;
	}
}

void imprimeLista(ListaCDE lista)
{
	Dado dado_end = lista->inicio;
	printf("\ncodigo: %d, descrição: %s, quantidade: %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
	dado_end = dado_end->prox;

	while(dado_end != lista->inicio)
	{
		printf("\ncodigo: %d, descrição %s, quantidade %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
		dado_end = dado_end->prox;
	}
}

void imprimeListaAoContrario(ListaCDE lista)
{
	Dado dado_end = lista->fim;
	printf("\ncodigo: %d, descrição: %s, quantidade: %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
	dado_end = dado_end->anterior;

	while(dado_end != lista->fim)
	{
		printf("\ncodigo: %d, descrição %s, quantidade %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
		dado_end = dado_end->anterior;
	}
}

int main()
{
	setlocale(LC_ALL, "");

	ListaCDE lista = iniciarLista();

	Premio premio;

	premio.codigo = 111;
	strcpy(premio.descricao, "20 reais desconto");
	premio.qtd = 5;

	inserir_final(lista, premio);

	premio.codigo = 222;
	strcpy(premio.descricao, "camiseta");
	premio.qtd = 3;

	inserir_final(lista, premio);

	premio.codigo = 333;
	strcpy(premio.descricao, "caminhão de cajarana");
	premio.qtd = 2;

	inserir_final(lista, premio);

	premio.codigo = 555;
	strcpy(premio.descricao, "um carro do leite cheio de leite");
	premio.qtd = 6;

	inserir_final(lista, premio);

	imprimeLista(lista);

	printf("\n\n");
	
	imprimeListaAoContrario(lista);

	Dado dd = lista->fim;

	printf("\ndado do fim %d apontando para o primeiro %d\n", dd->premio.codigo, dd->prox->premio.codigo);

	dd = lista->inicio;
	printf("\ndado do inicio %d apontando para o ultimo %d\n", dd->premio.codigo, dd->anterior->premio.codigo);

	buscar_remove(lista, 222);
	buscar_remove(lista, 111);
	buscar_remove(lista, 555);

	printf("\n");

	imprimeLista(lista);

	dd = lista->inicio;

	printf("\n%d", dd->premio.codigo);
	printf("\n%d", dd->prox->prox->premio.codigo);

	return 0;
}
