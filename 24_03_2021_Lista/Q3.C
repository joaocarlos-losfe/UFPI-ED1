/*
	João Carlos de Sousa Fé - 26/03/2021
	Estrutura de Dados I
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void maiusculasParametro(char *str1, char *str2, int *qtd_maiuscula1, int *qtd_maiuscula2)
{	
	//repete até achar o caractere de escape ('\0') da string
	
	while(*str1!='\0')
	{
		//compara o codigo ascii do caractere;
		// carateres com condigo ascii entre 65 e 90 são letras maiusculas na tabela ascii
		//"cast" da str para se obter o valor ascii
		
		if((int)*str1 >= 65 && (int)*str1<=90)
			*qtd_maiuscula1+=1;
		str1++;
	}
	
	while(*str2!='\0')
	{
		if((int)*str2 >= 65 && (int)*str2<=90)
			*qtd_maiuscula2+=1;
		str2++;
	}
	
}

int quantidadeVogais(char *str1, char *str2)
{
	char vogais_conhecidas[] = {'a','A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
	
	//concatena para uma string unica para melhor contagem
	strcat(str1, str2);
	
	int qtd_vogais = 0;
	int i = 0;
	
	while(*str1!='\0')
	{
		for(i=0; i < (int)sizeof(vogais_conhecidas); i++)
		{
			if(*str1 == vogais_conhecidas[i])
			{
				qtd_vogais++;
				break;
			}
		}
		str1++;
	}
	
	return qtd_vogais;
}

int main(int argc, char** argv)
{
	//strings de exemplo
	char str1[] = "aEIoH";
	char str2[] = "aeioU";
	
	int qtd_maiuscula1 = 0;
	int qtd_maiuscula2 = 0;
	
	maiusculasParametro(str1, str2, &qtd_maiuscula1, &qtd_maiuscula2);
	
	printf("Maiusculas (parametro):\nstring 1 - %d maiusculas.\nstring 2 - %d letras maiusculas\n", qtd_maiuscula1, qtd_maiuscula2);
	
	printf("\nRetorno por funcao:");									//retorno diretamente
																		//repassando como exemplo:
																		//str1[] = "aEIoH" e char str2[] = "aeioU" 
	printf("\nquantidade total de vogais das duas strings: %d vogais\n", quantidadeVogais(str1, str2));
	
	return 0;
}