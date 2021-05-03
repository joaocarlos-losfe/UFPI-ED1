/*
	João Carlos de Sousa Fé - 26/03/2021
	Estrutura de Dados I
*/

#include <stdio.h>
#include <stdlib.h>

void numeroDeVogaisParametro(char *str, int *qtd)
{
	//declaração inicial das vogais conhecidas, 
	//tanto em minúsculas, quanto em maisculas
	char vogais_conhecidas[] = {'a','A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};

	int i = 0;
	
	//repete ate achar o caractere de escape '\0'
	while(*str!='\0')
	{
		//vasculha todo o array de caractres, obtendo o seu tamanho
		//total em bytes atraves do operador "zizeof"
		for (i=0; i < sizeof(vogais_conhecidas); i++)
		{
			//compara o conteudo da string com o conteudo de cada
			//posição no array de caracteres. Se for igual, incrementa o contador
			if(*str == vogais_conhecidas[i])
			{
				//incrementa por parametro a variavel repassada
				*qtd = *qtd + 1;
				break;
			}	
		}
			
		//avança para o proximo endereço de memoria da cadeia de caracteres
		str++;
	}
	
	
}

int numeroDeVogaisPorFuncao(char *str)
{
	//declaração inicial das vogais conhecidas, 
	//tanto em minúsculas, quanto em maisculas
	
	char vogais_conhecidas[] = {'a','A', 'e', 'E', 'i', 'I', 'o', 'O', 'u', 'U'};
	
	//quantidade inicial ainda é zero(0)
	int qtd_vogais = 0;
	
	int i = 0;
	
	//repete ate achar o caractere de escape '\0'
	while(*str!='\0')
	{
		//vasculha todo o array de caractres, obtendo o seu tamanho
		//total em bytes atraves do operador "zizeof"
		for (i=0; i < sizeof(vogais_conhecidas); i++)
		{
			//compara o conteudo da string com o conteudo de cada
			//posição no array de caracteres. Se for igual, incrementa o contador
			if(*str == vogais_conhecidas[i])
			{
				qtd_vogais++;
				break;
			}	
		}
			
		//avança para o proximo endereço de memoria da cadeia de caracteres
		str++;
	}
	
	//retorna a quantidade
	return qtd_vogais;
}

int main(int argc, char** argv)
{							
	//exemplo de implementação
	
	int qtd_vogais = 0;
	numeroDeVogaisParametro("AeIou", &qtd_vogais);
	printf("Por Parametro: %d vogais\n", qtd_vogais);
	
	int numero_de_vogais_por_retorno = numeroDeVogaisPorFuncao("joao carlos de sousa fe");
	printf("Por funcao %d vogais\n", numero_de_vogais_por_retorno);
	
	return 0;
}