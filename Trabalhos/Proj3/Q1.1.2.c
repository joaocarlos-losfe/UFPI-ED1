#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <locale.h>

typedef struct Monomio* Monomio;
typedef struct Polinomio* Polinomio;

struct Monomio
{
	char termo[10];
	Monomio proximo;
};

struct Polinomio
{
	int ID;
	int n_elementos;
	Monomio inicio;
	Monomio fim;
};

bool polinomioVazio(Polinomio polinomio);
bool PolinomioPossuiTermoResto(Polinomio polinomio, char* resto);
Polinomio apagarPolinomio(Polinomio polinomio);
Polinomio criarPolinomio(int id);
Polinomio somarPolinomios(Polinomio polinomio1, Polinomio polinomio2);
Polinomio strToPolinomio(char *str, int id);
void anexarNoPolinomio(Polinomio polinomio, Monomio monomio);
void anexarRestosMonomioInexistente(Polinomio destino, Polinomio p1, Polinomio p2);
void exibirPolinomio(Polinomio polinomio);

int coeficienteToInt(char * str_coeficiente);
int strToInt(char* str) ;
void extrairCoeficiente(char *monomio, char *coeficiente, char *resto);
void formatarTermo(char *termo, int coeficiente, char *resto);

Monomio apagarMonomio(Monomio monomio);
Monomio criarMonomio(char* termo);
void exibirMonomio(Monomio monomio);

int buscarIndexPolinomio(Polinomio *polinomios, int qtd, int id)
{
	int index = -1;
	int i;
	
	for(i=0; i<qtd; i++)
	{
		if(id == polinomios[i]->ID)
		{
			index = i;
			break;
		}
	}
	
	return index;
}

void menu();

int main(int argc, char** argv)
{

	setlocale(LC_ALL,"");
	Polinomio polinomios[100];
	int qtd = 0;

	int op, i=0;

	int id;
	char str_polinomio[10];
	
	int id_1, id_2;
	int index1, index2;
	
	
	do
	{
		menu();
		scanf("%d", &op);

		switch(op)
		{
		case 1:
			printf("\nID da lista: ");
			scanf("%d", &id);
			
			printf("\ndigite o polinomio: ");
			setbuf(stdin, NULL);
			scanf(" %[^\n]s", str_polinomio);
			
			Polinomio novo_polinomio = strToPolinomio(str_polinomio, id);
			
			polinomios[qtd] = novo_polinomio;
			
			qtd++;
			
			break;
		
		case 2:
			
			
			printf("digite o id para selecionar o primeiro polinomio: ");
			scanf("%d", &id_1);
			printf("digite o id para selecionar o segundo polinomio: ");
			scanf("%d", &id_2);
			
			index1 = buscarIndexPolinomio(polinomios, qtd, id_1);
			index2 = buscarIndexPolinomio(polinomios, qtd, id_2);
			
			if(index1 == -1 || index2 == -1)
				printf("\nUm ou mais ids não encontrados");
			else
			{
				Polinomio resultado = somarPolinomios(polinomios[index1], polinomios[index2]);
				
				printf("\nResultado:");
				exibirPolinomio(resultado);
				resultado = apagarPolinomio(resultado);
			}
			
			break;
		
		case 5:
			printf("\nDigite o id do polinomio: ");
			scanf("%d", &id);
			
			int index = buscarIndexPolinomio(polinomios, qtd, id);
			
			if(index == -1)
				printf("\npolinomio solicitado não encontrado");
			else
				exibirPolinomio(polinomios[index]);
			
			break;
		
		case 6:
			for (i=0; i<qtd; i++)
			{
				exibirPolinomio(polinomios[i]);	
			}
		
			break;
		}

	}
	while(op != 0);



	return 0;
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

Monomio criarMonomio(char* termo)
{
	Monomio monomio = malloc(sizeof(struct Monomio));
	strcpy(monomio->termo, termo);
	monomio->proximo = NULL;
	return monomio;
}

Monomio apagarMonomio(Monomio monomio)
{
	free(monomio);
	monomio = NULL;
	return monomio;
}

void exibirMonomio(Monomio monomio)
{
	if(monomio->termo[0] == '-')
	{
		printf("- %s ", monomio->termo + 1);
	}
	else
	{
		printf("+ %s ", monomio->termo);
	}
}

bool polinomioVazio(Polinomio polinomio)
{
	return polinomio->inicio == NULL; // se for null retorna true, se não, falso;
}

Polinomio criarPolinomio(int id)
{
	Polinomio polinomio = malloc(sizeof(struct Polinomio));

	polinomio->n_elementos = 0;
	polinomio->inicio = NULL;
	polinomio->fim = NULL;
	polinomio->ID = id;

	return polinomio;
}

Polinomio apagarPolinomio(Polinomio polinomio)
{
	Monomio monomio = polinomio->inicio;
	Monomio temp = monomio->proximo;
	do
	{
		monomio = apagarMonomio(monomio);
		monomio = temp;
		temp = temp->proximo;
	}
	while(temp != polinomio->inicio );
	polinomio->inicio = polinomio->fim = NULL;
	free(polinomio);
	return NULL;
}

void anexarNoPolinomio(Polinomio polinomio, Monomio monomio)
{
	Monomio atual = polinomio->inicio;

	if(atual == NULL)
	{
		polinomio->inicio = polinomio->fim = monomio->proximo = monomio;
	}
	else
	{
		monomio->proximo = polinomio->inicio;
		polinomio->fim = polinomio->fim->proximo = monomio;
	}

	polinomio->n_elementos++;
}

void exibirPolinomio(Polinomio polinomio)
{
	if (polinomioVazio(polinomio))
	{
		printf("Polinomio vazio.");
	}
	else
	{
		Monomio monomio = polinomio->inicio;
		do
		{
			exibirMonomio(monomio);
			monomio = monomio->proximo;
		}
		while(monomio != polinomio->inicio );

	}
	printf("\n\n");
}


Polinomio strToPolinomio(char *str, int id)
{

	char termo[10];
	int i = 0;
	int j = 0;

	Polinomio polinomio = criarPolinomio(id);

	while(str[i] != '\0')
	{
		if(str[i] != ' ')
		{
			if (str[i] == '+')
			{
				termo[j] = '\0';
				anexarNoPolinomio(polinomio, criarMonomio(termo));
				j = 0;
			}
			else if (str[i] == '-')
			{
				termo[j] = '\0';
				anexarNoPolinomio(polinomio, criarMonomio(termo));
				termo[0] = '-';
				j = 1;
			}
			else
			{
				termo[j] = str[i];
				j++;
			}
		}

		i++;
	}

	if(str[i] == '\0')
	{
		termo[j] = '\0';
		anexarNoPolinomio(polinomio, criarMonomio(termo));
	}
	return polinomio;
}

void extrairCoeficiente(char *monomio, char *coeficiente, char *resto)
{
	int i = 0;

	strcpy(coeficiente, "");
	strcpy(resto, "");

	if(monomio[0] == '-')
	{
		coeficiente[0] = '-';
		i = 1;
	}

	while(isdigit(monomio[i]) )
	{
		coeficiente[i] = monomio[i];
		i++;
	}
	coeficiente[i] = '\0';

	strcat(resto, monomio + i);

}

int strToInt(char* str)
{
	if(strcmp(str, "") == 0)
	{
		return 0;
	}
	return atoi(str);
}

int coeficienteToInt(char * str_coeficiente)
{
	int coeficiente = strToInt(str_coeficiente);
	if(coeficiente == 0)
	{
		coeficiente = 1;
	}
	return coeficiente;
}

bool PolinomioPossuiTermoResto(Polinomio polinomio, char* resto)
{

	Monomio monomio = polinomio->inicio;
	char coeficiente[10];
	char resto_monomio[10];
	bool possui_resto = false;

	do
	{
		extrairCoeficiente(monomio->termo, coeficiente, resto_monomio);
		if(strcmp(resto, resto_monomio) == 0)
		{
			possui_resto = true;
			break;
		}
		monomio = monomio->proximo;

	}
	while(monomio != polinomio->inicio);

	return possui_resto;
}

void formatarTermo(char *termo, int coeficiente, char *resto)
{
	if(coeficiente == 1)
	{
		strcpy(termo, resto);
	}
	else
	{
		sprintf(termo, "%d%s", coeficiente, resto); // converte pra string de volta
	}
}

void anexarRestosMonomioInexistente(Polinomio destino, Polinomio p1, Polinomio p2)
{

	Monomio iterador = p1->inicio;
	Monomio monomio;
	char termo_resultante[10];
	char coeficiente[10];
	char resto[10];
	int coeficiente_numerico = 0;

	do
	{

		extrairCoeficiente(iterador->termo, coeficiente, resto);
		coeficiente_numerico = strToInt(coeficiente);

		if(!PolinomioPossuiTermoResto(p2, resto))
		{

			coeficiente_numerico = coeficienteToInt(coeficiente);
			formatarTermo(termo_resultante, coeficiente_numerico, resto);
			monomio = criarMonomio(termo_resultante);
			anexarNoPolinomio(destino, monomio);
		}

		iterador = iterador->proximo;
	}
	while(iterador != p1->inicio);
}

Polinomio somarPolinomios(Polinomio polinomio1, Polinomio polinomio2)
{

	Monomio monomio1 = polinomio1->inicio;
	Monomio monomio2 = polinomio2->inicio;

	char coeficientes[2][10];
	char restos[2][10];

	int coeficiente_numerico[2];

	Monomio monomio;

	Polinomio polinomio_resultante = criarPolinomio(0);

	char termo_resultante[10];

	do
	{
		extrairCoeficiente(monomio1->termo, coeficientes[0], restos[0]);

		coeficiente_numerico[0] = coeficienteToInt(coeficientes[0]);


		do
		{
			extrairCoeficiente(monomio2->termo, coeficientes[1], restos[1]);
			coeficiente_numerico[1] = coeficienteToInt(coeficientes[1]);

			if(strcmp(restos[0], restos[1]) == 0)
			{
				coeficiente_numerico[0] += coeficiente_numerico[1];
			}

			monomio2 = monomio2->proximo;

		}
		while(monomio2 != polinomio2->inicio);

		formatarTermo(termo_resultante, coeficiente_numerico[0], restos[0]);
		monomio = criarMonomio(termo_resultante);
		anexarNoPolinomio(polinomio_resultante, monomio);

		monomio1 = monomio1->proximo;

	}
	while(monomio1 != polinomio1->inicio);

	anexarRestosMonomioInexistente(polinomio_resultante, polinomio2, polinomio1);
	return polinomio_resultante;

}
