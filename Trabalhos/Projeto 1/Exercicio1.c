/*
	Primeira questão referente a primeira avaliação da discpina de Estrurura de dados I.

	Autores: João Carlos de Sousa Fé && Vitor José Ferreira dos Santos de Santana.
	Data de inicio da resolução dos exercicios: 12/04/2021

	Questão 1.
		Faça um programa em C que, dado uma matriz de inteiros quadrada
		no máximo de ordem 4, calcule o determinante da mesma.
		Obs. 1: Deve ser permitido ao usuário definir a ordem da matriz.
		Obs. 2: Todas as funções relacionadas a matriz devem ser recursiva.
*/


#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

void preencherMatriz(int ordem, int i, int j, double matriz[ordem][ordem]);
void mostrarMatriz(int ordem, int i, int j, double matriz[ordem][ordem]);
void transformarEmTriangulo(int ordem, double matriz[ordem][ordem], int i, int j, int k, int *count);
void espalhar(int i, int j, int k, int ordem, double matriz[ordem][ordem]);
void troca(int i, int j, int k, int ordem, double matriz[ordem][ordem]);
void factorCalc(int k, int i, int j, int ordem, double matriz[ordem][ordem]);
void multiplicarMatriz(int i, double *calc, int ordem, double matriz[ordem][ordem]);

int main(void)
{
	setlocale(LC_ALL, ""); //define o idioma para usar caracteres da lingua portuguesa (acentuações)
	
	int ordem = 0;
	double calc = 1.0;
	int count = 0;

	printf("Ordem da matriz: ");
	scanf("%d", &ordem);
	
	while(ordem > 4 || ordem < 1)
	{
		printf("\nOrdem da matriz invalida, entre com ordens de 1 até de no máximo ordem 4\n");
		printf("Ordem da matriz: ");
		scanf("%d", &ordem);
	}
	
	printf("\nPreencha a matriz: \n\n");
	
	double matriz[ordem][ordem];
	
	preencherMatriz(ordem, 0, 0, matriz);
	
	printf("\n\nMatriz preenchida: \n");
	
	mostrarMatriz(ordem, 0, 0, matriz);
	
	transformarEmTriangulo(ordem, matriz, 0, 0, 0, &count);
	
	multiplicarMatriz(0, &calc, ordem, matriz);
	
	printf("\nDeterminante da matriz: ");
	
	if(count % 2 == 0)
		printf("%1.0f \n", calc);
	else
		printf("%1.0f \n", -1.0 * calc);

	return 0;
}

void multiplicarMatriz(int i, double *multiplicar_matriz, int ordem, double matriz[ordem][ordem])
{
	if(i < ordem)
	{
		(*multiplicar_matriz) *= matriz[i][i];

		multiplicarMatriz(i + 1, multiplicar_matriz, ordem, matriz);
	}
}

void preencherMatriz(int ordem, int i, int j, double matriz[ordem][ordem])
{
	if (i < ordem)
	{
		if(j < ordem)
		{
			printf("linha %d coluna %d: ", i + 1, j + 1);
			scanf("%lf", &matriz[i][j]);
			preencherMatriz(ordem, i, j + 1, matriz);
		}
		else
		{
			j = 0;
			preencherMatriz(ordem, i + 1, j, matriz);
		}
	}
}

void mostrarMatriz(int ordem, int i, int j, double matriz[ordem][ordem])
{
	if (i < ordem)
	{
		if(j < ordem)
		{
			printf("%1.0f ", matriz[i][j]);
			mostrarMatriz(ordem, i, j + 1, matriz);
		}
		else
		{
			j = 0;
			printf("\n");
			mostrarMatriz(ordem, i + 1, j, matriz);
		}
	}
}

void troca(int i, int j, int k, int ordem, double matriz[ordem][ordem])
{
	if(j < ordem)
	{
		double temp = matriz[i][j];
		matriz[i][j] = matriz[k][j];
		matriz[k][j] = temp;
		troca(i, j + 1, k, ordem, matriz);
	}
}

void espalhar(int i, int j, int k, int ordem, double matriz[ordem][ordem])
{
	if(k < ordem)
	{
		if(matriz[k][i] != 0)
		{
			troca(i, j, k, ordem, matriz);

			k = ordem;
		}

		espalhar(i, j, k + 1, ordem, matriz);
	}
}

void factorCalc(int k, int i, int j, int ordem, double matriz[ordem][ordem])
{
	if(k < ordem)
	{
		double fator = -1.0 * matriz[k][i] / matriz[i][i];

		for(j = i; j < ordem; j++)
		{
			matriz[k][j] = matriz[k][j] + (fator * matriz[i][j]);
		}

		factorCalc(k + 1, i, j, ordem, matriz);
	}
}

void transformarEmTriangulo(int ordem, double matriz[ordem][ordem], int i, int j, int k, int *count)
{
	if(i < (ordem - 1))
	{
		if(matriz[i][i] == 0)
		{
			k = i;

			espalhar(i, j, k, ordem, matriz);

			(*count)++;
		}

		if(matriz[i][i] != 0)
		{
			k = (i + 1);

			factorCalc(k, i, j, ordem, matriz);
		}

		transformarEmTriangulo(ordem, matriz, i + 1, j, k, count);
	}
}