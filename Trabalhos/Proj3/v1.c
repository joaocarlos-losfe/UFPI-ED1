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
	return lista->inicio == NULL; // se for null retorna true, se n�o, falso;
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
	printf("\n 1 - Cadastrar polin�mio");
	printf("\n 2 - Somar 2 polinomios cadastrados");
	printf("\n 3 - Multiplicar 2 polinomios cadastrados");
	printf("\n 4 - Avaliar um dos polin�mios cadastrados em fun��o de valores dados para x, y e z,");
	printf("\n 5 - Imprimir a representa��o de um dos polin�mios cadastrados");
	printf("\n 6 - Imprimir a representa��o de todos os polin�mios cadastrados ");
	printf("\n 7 - Calcular a derivada parcial de um dos polin�mios cadastrados em rela��o a qualquer uma das vari�veis");
	printf("\n> ");
}

void verPolinomio(ListaC lista, int id)
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
			if(id == lista->ID){
				mostrarDado(dado);
			}
			dado = dado->proximo;
		}
		while(dado != lista->inicio );
	}
}

//***************************************************//
// CALCULAR DERIVADA PARCIAL

/*
resolvido = função de buscaId tem que ser reformulada! A string está pegando lixo!
alocação dinâmica do vetor de string e depois a sua liberação
*/

int buscaId(ListaC lista, int id,char *str)
{
	int busca = 1;
	Dado dado = lista->inicio;
	while(dado != NULL )
	{
		if(id == lista->ID)
		{
			busca = 0;
			strcat(str,dado->termo.monomio);
		}
		dado = dado->proximo;
		if(dado == lista->inicio)
		{
			break;
		}
	}
	return busca;
}

int isnum(char c){
	int n = c - '0';
	return n;
}

char ischar(int n){
	char c = n + '0';
	return c;
}

void strderivada(char d,int i, char *str){
	str[i] = d;
	printf("derivada = %s\n",str);
}

void derivada(ListaC lista, int id, char variavel, char *str)
{
	int exp = 1, p;
	char n;
	for(int i = 0; i < strlen(str); i++){

		if(str[i] == variavel){

			if(isnum(str[i+1]))
			{
				p = isnum(str[i+1]) * isnum(str[i-1]);
				char d = ischar(p);
				strderivada(d,i-1,str);
			}
		}
	}
}

//***************************************************//
// CALCULAR VALOR DO POLINOMIO EM FUNÇÃO DAS VARIAVEIS

int potencia(int a, int b){
	int pot = 1;
	for(int i = 0; i < b; i++){
		pot *= a;
	}
	return pot;
}

void retiraEspaco(char *string){
	int len = strlen(string);
  for (int i = 0, posicao = 0; i < len; i++, posicao++) {
    if (string[posicao] == ' ') posicao++;
    string[i] = string[posicao];
  }
}
int valorFuncao(char *polinomio,int x, int y, int z){
	int tamanho = strlen(polinomio), i;
	char varX = ischar(x);
	char varY = ischar(y);
	char varZ = ischar(z);
	int p1,p2,p3;
	int k = 0,r;
	for(i = 0; i < tamanho; i++)
	{
		if(polinomio[i] == 'x' && i != 0)
		{
			p1 = potencia(x,isnum(polinomio[i + 1])) * isnum(polinomio[i - 1]);
		}
		else if(polinomio[i] == 'x' && i == 0)
		{
			p1 = potencia(x,isnum(polinomio[i + 1]));
		}
		else if(polinomio[i] == 'y' && (polinomio[i-1] != '+' && polinomio[i-1] != '-'))
		{
			p2 = potencia(y,isnum(polinomio[i + 1])) * isnum(polinomio[i - 1]);
		}
		else if(polinomio[i] == 'y' && (polinomio[i-1] == '+' || polinomio[i-1] == '-'))
		{
			p2 = potencia(y,isnum(polinomio[i + 1]));
		}
		else if(polinomio[i] == 'z' && (polinomio[i-1] != '+' && polinomio[i-1] != '-'))
		{
			p3 = potencia(z,isnum(polinomio[i + 1])) * isnum(polinomio[i - 1]);
		}
		else if(polinomio[i] == 'z' && (polinomio[i-1] == '+' || polinomio[i-1] == '-'))
		{
			p3 = potencia(z,isnum(polinomio[i + 1]));
		}
		else if(polinomio[i] == 'y' && (polinomio[i+1] == '+' || polinomio[i+1] == '-'))
		{
			p2 = polinomio[i - 1] * y;
		}
		else if(polinomio[i] == 'z' && (polinomio[i+1] == '+' || polinomio[i+1] == '-'))
		{
			printf("aqui\n");
			p3 = polinomio[i - 1] * z;
		}
		else if(polinomio[tamanho - 2] == '+')
		{
			k = isnum(polinomio[tamanho-1]);
		}
		else if(polinomio[tamanho - 2] == '-'){
			k = isnum(polinomio[tamanho]);
		}
		else if(polinomio[i] == ' ')
		{
			i++;
		}
		else{
			continue;
		}
	}
	if(k == 0){
		r = p1 + p2 + p3;
	}
	else{
		r = p1 + p2 + p3 + k;
	}
	return r;
}

int main(int argc, char** argv)
{
	ListaC lista_polinomios[100];
	int index = 0;
	int op = 1;
	int i = 0;
	int id,poli;
	char polinomio[50],var;
	char *strPolinomio = (char *) malloc(sizeof(strPolinomio) * 10);
	int x,y,z;
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
    case 4:
			printf("\nPolinômio:  ");
			scanf("%d",&poli);
			if(buscaId(lista,id,strPolinomio) == 0){
				scanf("%d",&x);
				scanf("%d",&y);
				scanf("%d",&z);
				valorFuncao(strPolinomio,x,y,z);
				free(strPolinomio);
			}
      break;
		case 5:
			if(index > 0){
				printf("\nPolinômio: ");
				scanf("%d",&poli);
				verPolinomio(lista,poli);
				printf("\n");
			}
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
			break;
		case 7:
			printf("\nID do Polinômio: ");
			scanf("%d",&poli);
			if(buscaId(lista,id,strPolinomio) == 0){
        printf("\nVariável: ");
        scanf(" %c",&var);
				derivada(lista,poli,var,strPolinomio);
				free(strPolinomio);
			}
      else{
        printf("Polinomio não encontrado!\n");
      }
			break;
		default:
			break;
		}

	}
	while(op != 0);

	return 0;
}
