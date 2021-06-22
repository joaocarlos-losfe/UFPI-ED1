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
	
}Premio;

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
    
    premio.codigo = 444;
    strcpy(premio.descricao, "carne de cutia macho");
    premio.qtd = 6;

    inserir_final(lista, premio);
    
    premio.codigo = 555;
    strcpy(premio.descricao, "um carro do leite cheio de leite");
    premio.qtd = 6;

    inserir_final(lista, premio);
    
    imprimeLista(lista);
    
    printf("\n\n");
    
    Dado dd = lista->fim;
    
    printf("\ndado do fim %d apontando para o primeiro %d\n", dd->premio.codigo, dd->prox->premio.codigo);
       
    return 0;
}