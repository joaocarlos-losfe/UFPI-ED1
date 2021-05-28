/*
	Segunda questão referente a primeira avaliação da discpina de Estrurura de dados I.
	
	Autores: João Carlos de Sousa Fé && Vitor José Ferreira dos Santos de Santana.
	Data de inicio da resolução dos exercicios: 20/04/2021
	
	Questão 2. 
		Faça um programa em C que tenha um menu de opções com as seguintes opções: para ler uma 
		matriz de strings; uma opção para ordenar cada uma das colunas da matriz, lembre-se 
		que o usuário pode entrar com letras maiúsculas e minúsculas e que as mesmas não 
		podem ser alteradas para o usuário; outra para mostrar cada coluna da matriz antes 
		de ordenar e outra depois de ordenar; uma opção que dado uma linha e uma coluna, 
		conte o número de dígitos e de letras maiúsculas; outra que dado uma coluna conte 
		o número de strings dessa coluna que iniciam com consoante.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define maximo_caracteres 100
typedef char string[maximo_caracteres]; //define um string padrão de 100 caractres
char*** alocarMatrizStrings(int l, int c);
char ** alocarVetorString(int ordem);
void lerMatriz(int l, int c, char ***matriz, int i, int j);
void mostrarMatrizOriginal(int l, int c, char ***matriz, int i, int j);
void copiarMatrizParaVetor(int l, int c, char ***matriz, char **vetor_strings);
void copiarVetorOrdenadoParaMatriz(int l, int c, char ***matriz, char **vetor_strings);
void swap(char **a, char **b);
void quicksort(char **arr, int length);
void mostrarMatriOrdenada(int l, int c, char ***matriz, int i, int j);
void contarDigitosLetrasMaiuculas(char *string, int i, int len_string, int n_digitos, int l_maiusculas);
void contarColunasStringConsoante(int l, int i, char ***matriz, int coluna, int count);
void tolowerAll(char *str, char *str_copy);
void ordenarFinal(int l, int c, char ***matriz, char **vetor_string);
void ok();

int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	
	int op = 0, linhas = 0, colunas = 0;
	char ***matriz, **vetor_strings;

	int linfo = 0, cinfo = 0;

	int matriz_foi_ordenada = 0;

	while(1)
	{
		printf("\n\n1 - ler uma matriz de strings\n");
		printf("2 - mostrar cada coluna da matriz (nao ordenada)\n");
		printf("3 - ordenar cada uma das colunas da matriz\n");
		printf("4 - mostrar matriz ordenada\n");
		printf("5 - contar numero de digitos e de letras maiusculas dado uma linha e coluna\n");
		printf("6 - contar o número de strings da coluna que iniciam com consoante\nopcao: ");

		scanf("%d", &op);

		switch(op)
		{
		case 1:
			do
			{
				printf("\nLinhas da matriz: ");
				scanf("%d", &linhas);

				printf("\nColunas da matriz: ");
				scanf("%d", &colunas);
				if(linhas == 0 || colunas == 0)
					printf("linha ou coluna não podem ser 0");
			}
			while(linhas == 0 || colunas == 0);

			matriz = alocarMatrizStrings(linhas, colunas);
			//aloca uma dimensão so com linha * colunas para definir a quantidade de colunas
			vetor_strings = alocarVetorString(linhas * colunas);
			lerMatriz(linhas, colunas, matriz, 0, 0);
			
			break;

		case 2:
			if(linhas == 0 || colunas == 0)
				printf("Matriz não preenchida ou definida");
			else
			{
				mostrarMatrizOriginal(linhas, colunas, matriz, 0, 0);
			}
			ok();
			break;

		case 3:
			if(linhas == 0 || colunas == 0)
				printf("Matriz não preenchida ou definida");
			else
			{
				ordenarFinal(linhas, colunas, matriz, vetor_strings);
				printf("\nA matriz foi ordenada");
				matriz_foi_ordenada = 1;
				
			}
			ok();
			break;

		case 4:
			if(linhas == 0 || colunas == 0)
				printf("Matriz não preenchida ou definida");
			else
			{
				if(matriz_foi_ordenada)
				{
					printf("\nMostrando matriz ordenada: \n\n");
					mostrarMatriOrdenada(linhas, colunas, matriz, 0, 0);
				}
				else
				{
					printf("Matriz ainda não foi ordenda...");
				}
			}
			ok();
			break;
		case 5:

			printf("\nInforme a linha ");
			scanf("%d", &linfo);
			printf("\ninforme a coluna: ");
			scanf("%d", &cinfo);
			contarDigitosLetrasMaiuculas(matriz[linfo][cinfo], 0, strlen(matriz[linfo][cinfo]), 0, 0);

			ok();
			break;
		case 6:
			printf("\ninforme a coluna: ");
			scanf("%d", &cinfo);
			contarColunasStringConsoante(linhas, 0, matriz, cinfo, 0);
			ok();
			break;
		default:
			printf("\nopcao invalida");
			break;
		}
	}
	return 0;
}

void ordenarFinal(int l, int c, char ***matriz, char **vetor_string)
{
	int i = 0, j = 0, k = 0;
	
	for(j=0; j<c; j++)
	{
		for(i=0; i<l; i++)
		{
			strcpy(vetor_string[i], matriz[i][j]);
		}
		
		quicksort(vetor_string, l);
		
		for(k = 0; k < l; k++)
		{
			strcpy(matriz[k][j], vetor_string[k]);
		}
	}
}

void contarColunasStringConsoante(int l, int i, char ***matriz, int coluna, int count)
{
	if(i < l)
	{
		if(isalpha(matriz[i][coluna][0]) > 0)
		{
			switch(toupper(matriz[i][coluna][0]))
			{
			case 'A':
			case 'E':
			case 'I':
			case 'O':
			case 'U':
				break;
			default:
				count += 1;
			}
		}

		contarColunasStringConsoante(l, i + 1, matriz, coluna, count);
	}
	else
	{
		printf("total de consoantes: %d", count);
	}

}

void contarDigitosLetrasMaiuculas(char *string, int i, int len_string, int n_digitos, int l_maiusculas)
{
	if(i < len_string)
	{
		if(isdigit(string[i])) n_digitos += 1;

		if((int)string[i] >= 65 && (int)string[i] <= 90) l_maiusculas += 1;

		contarDigitosLetrasMaiuculas(string, i + 1, len_string, n_digitos, l_maiusculas);
	}
	else
	{
		printf("A string %s contem %d digitos e %d letras maiusculas", string, n_digitos, l_maiusculas);
	}

}

void copiarVetorOrdenadoParaMatriz(int l, int c, char ***matriz, char **vetor_strings)
{
	int i, j;
	
	for (i=0; i<l; i++)
	{
		for(j=0; j<c; j++)
		{
			strcpy(matriz[i][j], vetor_strings[i*c + j]);
		}
	}
}

void lerMatriz(int l, int c, char ***matriz, int i, int j)
{
	char temp_string[30];

	if(i < l)
	{
		printf("\npreenchendo a linha %d", i + 1);
		if(j < c)
		{
			setbuf(stdin, NULL);
			printf("\nEntre com os caracteres da coluna %d: ", j + 1);
			scanf("%s", temp_string);
			strcpy(matriz[i][j], temp_string);
			lerMatriz(l, c, matriz, i, j + 1);
		}
		else
		{
			j = 0;
			lerMatriz(l, c, matriz, i + 1, j);
		}
	}
	
}

void mostrarMatrizOriginal(int l, int c, char ***matriz, int i, int j)
{
	printf("\nMostrando as colunas da matriz original: \n\n");
	for(i = 0; i < l; i++)
	{
		for(j = 0; j < c; j++)
		{
			printf("%s ", matriz[i][j]);
		}

		printf("\n");
	}

}

char*** alocarMatrizStrings(int l, int c)
{
	int i, j;
	char*** matriz_aloc = (char ***)malloc(l * sizeof(char**));
	for(i = 0; i < l; ++i)
	{
		matriz_aloc[i] = (char **)malloc( l * sizeof(char *));
		for(j = 0; j < c; j++)
		{
			matriz_aloc[i][j] = (char*)calloc(1, sizeof(string));
		}
	}

	return matriz_aloc;
}

char ** alocarVetorString(int ordem)
{
	char **vect_aloc = (char **)malloc(ordem * sizeof(char**));

	int i = 0;

	for(i = 0; i < ordem; i++)
	{
		vect_aloc[i] = (char *)malloc(100 * sizeof(char));
	}

	return vect_aloc;
}

void copiarMatrizParaVetor(int l, int c, char ***matriz, char **vetor_strings)
{
	int i = 0, j = 0, k = 0;

	printf("\nordem : %d %d ", l, c);

	for(i = 0; i < l; i++)
	{
		for(j = 0; j < c; j++)
		{
			strcpy(vetor_strings[k], matriz[i][j]);
			k++;
		}
	}

	printf("%d\n", k);

}

void swap(char **a, char **b)
{	
	char temp[100];
	strcpy(temp, *a);
	strcpy(*a, *b);
	strcpy(*b, temp);
}

void tolowerAll(char *str, char *str_copy)
{
	int i = 0;
	
	for(i=0; i<=strlen(str); i++)
	{
		str_copy[i] = tolower(str[i]);
	}
}
void quicksort(char **arr, int length)
{
	int i, piv = 0;
	if (length <= 1)
		return;

	for (i = 0; i < length; i++)
	{
		
		char temp_string1[100];
		char temp_string2[100];
		
		tolowerAll(arr[i], temp_string1);
		tolowerAll(arr[length - 1], temp_string2);
		
		if (strcmpi(temp_string1, temp_string2) < 0)
			swap(arr + i, arr + piv++);// repassa as originais para trocar
	}

	swap(arr + piv, arr + length - 1);

	quicksort(arr, piv++);
	quicksort(arr + piv, length - piv);
}

void mostrarMatriOrdenada(int l, int c, char ***matriz, int i, int j)
{
	if(i < l)
	{
		if(j < c)
		{
			printf("%s ", matriz[i][j]);
			mostrarMatriOrdenada(l, c, matriz, i, j + 1);
		}
		else
		{
			j = 0;
			printf("\n");
			mostrarMatriOrdenada(l, c, matriz, i + 1, j);
		}
	}
}

void ok()
{
	printf("\n\npressione enter para continuar...\n");
	getchar();
	getchar();
}
