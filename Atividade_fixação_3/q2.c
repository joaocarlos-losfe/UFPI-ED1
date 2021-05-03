#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TAM 10

/* A função misterio 1, captura somente os "numeros" contido na string respassada
   "concatenando" os valores INTEIROS (numeros) encontrados na string. 
   a variavel "valor" (passada por referencia) passa ser um novo numero, caso 
   alguns caracteres na string seja numeros.
*/
void misterio1(char str[TAM], int i, int uni, int *valor)
{
	int n;
	if(i >= 0)
	{
		if(isdigit(str[i]))
		{
			n = str[i] - 48;
			*valor = *valor + (n * uni);
			misterio1(str, i - 1, uni * 10, valor);
		}
		else misterio1(str, i - 1, uni, valor);
	}
}

//refazendo a função misterio sem usar recursividade
void novo_misterio(char str[TAM], int *valor)
{
	int i = 0;
	
	for(i=0; i<strlen(str); i++)
	{
		if(isdigit(str[i]))
		{	
			*valor = *valor * 10 + str[i] - 48;
		}	
	}
}

int main(int argc, char** argv)
{
	
	char nome[TAM] = "5gt6e34wy";
	
	int i = strlen(nome) - 1;
	int uni = 1;
	int valor = 0;
	
	misterio1(nome, i, uni, &valor);
	
	printf("%d\n", valor);
	
	
	valor = 0;
	novo_misterio(nome, &valor);
	printf("\n%d\n", valor);
	
	return 0;
}