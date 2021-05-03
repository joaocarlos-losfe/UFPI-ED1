#include <stdio.h>
#include <stdlib.h>

#define TAM 10

//função original com erros corrigidos
void inter(int V1[TAM], int V2[TAM], int V3[TAM], int i, int j, int q1, int q2, int *q3)
{
	if(i < q1 || j < q2)
	{
		if(V1[i] == V2[j])
		{
			V3[*q3] = V1[j];
			(*q3)++;
			
		}
		if(j == q2)
		{
			j = 0;
			i += 1;
		}
		
		inter(V1, V2, V3, i, j + 1, q1, q2, q3);
	}

}

//requista por mais posições no array que guarda as intersecções (perdece a nova função de intersecção)
int * requisitar_mais_memoria(int *vetor)
{
	vetor = (int*)realloc(vetor, sizeof (vetor));

	return vetor;
}

//Nova função sem usar recursividade

int intercect(int *v1, int tv1, int *v2, int tv2, int *v3)
{
	int i, j, t = 0;

	for(i = 0; i < tv1; i++)
	{
		for(j = 0; j < tv2; j++)
		{
			if(v1[i] == v2[j])
			{
				v3[t] = v1[i];
				v3 = requisitar_mais_memoria(v3);
				t += 1;
			}
		}
	}

	return t;
}


int main(int argc, char** argv)
{
	/*	teste da nova função. somente para fins de teste, os vetores ja
		são inicializados com valores
	*/

	//vetores inicializados (necessario estarem ordenados)
	
	//função inter
	int v1[] = {1, 2, 8, 4, 5, 6, 7};
	int v2[] = {1, 2, 4, 7, 5, 8, 9};

	int v3[10];

	int i = 0, j = 0, q3 = 0;

	inter(v1, v2, v3, i, j, 7, 6, &q3);

	for(i = 0; i < q3; i++)
		printf("%d ", v3[i]);

	return 0;
}
