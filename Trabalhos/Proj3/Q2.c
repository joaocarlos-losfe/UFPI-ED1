#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>

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
	nova_lista->fim = NULL;
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
				lista->qtd_dados --;
				free(dado_end);
				return;
			}
			else
			{
				dado_end->anterior->prox = dado_end->prox;
				dado_end->prox->anterior = dado_end->anterior;
				lista->qtd_dados --;
				free(dado_end);
				return;
			}

		}

		dado_end = dado_end->prox;
	}

	if( (dado_end->premio.codigo == codigo) && (dado_end == lista->fim))
	{
		lista->inicio->anterior = lista->fim->anterior;
		lista->fim = lista->inicio->anterior;
		lista->fim->prox = lista->inicio;

		lista->qtd_dados --;
		free(dado_end);
		return;
	}
	
	if (lista->qtd_dados == 0)
	{
		lista->inicio = NULL;	
		lista->fim = NULL;
	}
		
		
}

void imprimeLista(ListaCDE lista)
{

	if(lista->qtd_dados > 0)
	{
		Dado dado_end = lista->inicio;

		printf("\ncodigo: %d, descrição: %s, quantidade: %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);

		dado_end = dado_end->prox;

		if(lista->qtd_dados > 1)
		{
			while(dado_end != lista->inicio)
			{
				printf("\ncodigo: %d, descrição %s, quantidade %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
				dado_end = dado_end->prox;
			}
		}

	}

}

void imprimeListaAoContrario(ListaCDE lista)
{
	if(lista->qtd_dados > 0)
	{
		Dado dado_end = lista->fim;

		printf("\ncodigo: %d, descrição: %s, quantidade: %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
		dado_end = dado_end->anterior;

		if(lista->qtd_dados > 1)
		{
			while(dado_end != lista->fim)
			{
				printf("\ncodigo: %d, descrição %s, quantidade %d", dado_end->premio.codigo, dado_end->premio.descricao, dado_end->premio.qtd);
				dado_end = dado_end->anterior;
			}
		}

	}
}

Dado girar_roleta(ListaCDE lista, int *flag, Dado aux)
{
	int i = 0;
	srand(time(NULL));

	if(lista->qtd_dados > 0)
	{
		printf("\n Rodando apartir de >>> %s <<<", aux->premio.descricao);

		if(*flag == 0)
		{
			printf("\n Girando em sentido horario");
			for (i = 0; i < rand() % 10; i++)
			{
				aux = aux->prox;	
			}

			*flag = 1;
		}
		else if (*flag == 1)
		{
			printf("\n Girando em sentido anti horario");
			for (i = 0; i < rand() % 10; i++)
			{
				aux = aux->anterior;
			}

			*flag = 0;
		}

		printf("\n Ganhador !!! Premio: %s, codigo: %d, quantidade restante: %d\n", aux->premio.descricao, aux->premio.codigo, aux->premio.qtd);
		aux->premio.qtd--;
	}


	return aux;

}

int main()
{
	setlocale(LC_ALL, "");

	ListaCDE lista = iniciarLista();

	Premio premio;

	premio.codigo = 111;
	strcpy(premio.descricao, "camisa");
	premio.qtd = 3;
	inserir_final(lista, premio);

	premio.codigo = 222;
	strcpy(premio.descricao, "bone do pernalonga");
	premio.qtd = 5;
	inserir_final(lista, premio);

	premio.codigo = 333;
	strcpy(premio.descricao, "10% de desconto em salsicha");
	premio.qtd = 2;
	inserir_final(lista, premio);


	premio.codigo = 444;
	strcpy(premio.descricao, "3 coxinhas de frango");
	premio.qtd = 2;
	inserir_final(lista, premio);

	premio.codigo = 555;
	strcpy(premio.descricao, "tesla 0km");
	premio.qtd = 4;
	inserir_final(lista, premio);


	premio.codigo = 666;
	strcpy(premio.descricao, "carteira de motorista");
	premio.qtd = 3;
	inserir_final(lista, premio);


	premio.codigo = 777;
	strcpy(premio.descricao, "notebook dell");
	premio.qtd = 2;
	inserir_final(lista, premio);


	premio.codigo = 888;
	strcpy(premio.descricao, "smarphone galaxy s20 ultra");
	premio.qtd = 3;
	inserir_final(lista, premio);


	premio.codigo = 999;
	strcpy(premio.descricao, "nokia lanterinha a prova de balas");
	premio.qtd = 2;
	inserir_final(lista, premio);

	int flag = 0;
	Dado aux = lista->inicio;

	int op;

	while(1)
	{
		printf("\n 1 - girar roleta, 2 - mostrar lista: ");
		scanf("%d", &op);
		
		if(op == 2)
		{
			printf("\n");
			imprimeLista(lista);
		}

		if (lista->qtd_dados > 0)
		{
			aux = girar_roleta(lista, &flag, aux);

			if (aux->premio.qtd == 0)
			{
				int id = aux->premio.codigo;
				printf("\n premio >>>> %s <<<< RETIRADO DA ROLETA ", aux->premio.descricao);
				aux = aux->prox;
				buscar_remove(lista, id);
			}
		}
		else
		{
			printf("\n Roleta vazia");
		}


	}


	return 0;
}
