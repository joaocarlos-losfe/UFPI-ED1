#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

#define NE 10 //Numero de Elementos

typedef struct
{
	char strings[NE][50];
	int tp; // topo

} Pilha_string;

void inserirElemento(Pilha_string *str1, const char *str)
{
	str1->tp += 1;
	strcpy(str1->strings[str1->tp], str);
}

void imprimirElemento(Pilha_string *str_pilha, int i)
{
	if(i >= 0)
	{
		printf("\n %s", str_pilha->strings[i]);

		imprimirElemento(str_pilha, i - 1);
	}
}

void stringsConsoantesPilha(Pilha_string *str1, Pilha_string *str2, Pilha_string *str3)
{
	if(str1->tp != -1 && str2->tp != -1) // continua desempilhando ate as 2 pilhas serem menor que "0" - 1 siginifica que ja ï¿½ elemento inacessivel
	{

		if(isalpha(str1->strings[str1->tp][0]) > 0) // verifica se ao menos ï¿½ alpha numerico
		{
			switch(toupper(str1->strings[str1->tp][0])) //salta as letras que nï¿½o sao consoantes
			{
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
				break;
			default:
				str3->tp += 1;
				strcpy(str3->strings[str3->tp], str1->strings[str1->tp]);

			}
		}

		if(str1->tp >= 0) // impedir indexes invalidos de continuarem decrementando, vai ate o minimo de -1
		{
			str1->tp -= 1;
		}

		if(isalpha(str2->strings[str2->tp][0]) > 0)
		{
			switch(toupper(str2->strings[str2->tp][0])) //salta as letras que não são consoantes
			{
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
				break;
			default:
				str3->tp += 1;
				strcpy(str3->strings[str3->tp], str2->strings[str2->tp]);
			}
		}

		if(str2->tp >= 0) // impedir indexes invalidos de continuarem decrementando, vai ate o minimo de -1
		{
			str2->tp -= 1;
		}

		stringsConsoantesPilha(str1, str2, str3);
	}
}

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "Portuguese");

	int qtd_elementos = 0, i;
	char str[50];

	Pilha_string str1;
	str1.tp = -1;
	Pilha_string str2;
	str2.tp = -1;
	Pilha_string str3;
	str3.tp = -1;

	printf(" Quantidade de elementos da pilha 1: ");
	scanf("%d", &qtd_elementos);

	while(qtd_elementos > NE)
	{
		printf("\n A quantidade de elementos maxima é de %d", NE);
		printf("\n quantidade de elementos para a pilha 1: ");
		scanf("%d", &qtd_elementos);
	}

	for(i = 0; i < qtd_elementos; i++)
	{
		setbuf(stdin, NULL);
		printf("\n %dª string da pilha 1: ", i + 1);

		scanf(" %s", str);

		inserirElemento(&str1, str);
	}

	printf("\n\n");

	printf(" Quantidade de elementos da pilha 2: ");
	scanf("%d", &qtd_elementos);

	while(qtd_elementos > NE)
	{
		printf("\n A quantidade de elementos maxima é de %d", NE);
		printf("\n quantidade de elementos para a pilha 1: ");
		scanf("%d", &qtd_elementos);
	}

	for(i = 0; i < qtd_elementos; i++)
	{
		setbuf(stdin, NULL);
		printf("\n %dª string da pilha 2: ", i + 1);

		scanf(" %s", str);

		inserirElemento(&str2, str);
	}

	int qual_pilha;

	printf("\n\n Qual pilha deseja imprimir os elementos 1 - pilha 1, 2 - pilha 2: ");
	scanf("%d", &qual_pilha);

	if(qual_pilha == 1)
	{
		printf("\n mostrando elementos da pilha 1");
		imprimirElemento(&str1, str1.tp);
		printf("\n");
	}
	else if(qual_pilha == 2)
	{
		printf("\n mostrando elementos da pilha 2");
		imprimirElemento(&str2, str2.tp);
		printf("\n");
	}

	stringsConsoantesPilha(&str1, &str2, &str3);

	printf("\n\n Mostrando os elementos da pilha 3 que iniciam com consoantes :\n");

	imprimirElemento(&str3, str3.tp);

	printf("\n");
	return 0;
}
