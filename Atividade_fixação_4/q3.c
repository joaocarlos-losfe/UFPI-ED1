#include <stdio.h>
#include <stdlib.h>

void quick_sort(int *a, int left, int right)
{
	int i, j, x, y;

	i = left;
	j = right;
	x = a[(left + right) / 2];

	while(i <= j)
	{
		while(a[i] < x && i < right)
		{
			i++;
		}
		while(a[j] > x && j > left)
		{
			j--;
		}
		if(i <= j)
		{
			y = a[i];
			a[i] = a[j];
			a[j] = y;
			i++;
			j--;
		}
	}

	if(j > left)
	{
		quick_sort(a, left, j);
	}
	if(i < right)
	{
		quick_sort(a, i, right);
	}
}

void intercecao(int *v1, int *v2, int *v3, int i, int j, int *k, int tam)
{	
	//verifica se é menor que o tamanho do vetor 1;
	if(i < tam)
	{
		//verifica se o conteudo da posição i do array é igual
		if(v1[i] == v2[j])
		{
			v3[*k] = v1[i]; // se for igual, é adicionado ao vetor 3
			(*k)++; // o indice do vetor 3 é incrementado em mais uma posição
		}
		j++; //avança o indice j
		if(j == tam)
		{
			j = 0; // zera j se j igual ao tamanho(significa que percorreu todos valores) fazendo uma busca sequencial simples
			i++; // avança o idice do vetor 1, para em seguida fazer a busca sequencia no vetor 2
		}
		intercecao(v1,v2,v3,i, j, k, tam); 
	}
}

int main(int argc, char** argv)
{
	int tam = 10;

	//dados para simulação (10 elementos)
	int v1[] = {4, 2, 1, 8, 9, 7, 10, 3, 13, 15};
	
	int v2[] = {1, 13, 3, 14, 11, 16, 5, 6, 4, 15};

	int v3[tam * tam];
	int i = 0;

	printf("vetor 1: \n");
	
	//ordena o primeiro vetor
	quick_sort(v1, 0, tam-1);

	for(i = 0; i < tam; i++)
		printf("%d ", v1[i]);
	
	//ordena o segundo vetor
	printf("\nvetor 2: \n");

	quick_sort(v2, 0, tam-1);

	for(i = 0; i < tam; i++)
		printf("%d ", v2[i]);
	
	//intercecção dos 2 vetores
	int j = 0;
	int k = 0;
	i = 0;
	
	printf("\n\nIntercecção dos dois vetores: \n");

	intercecao(v1,v2,v3, i, j, &k, tam);
	
	for(i=0; i<k; i++)
		printf("%d ", v3[i]);
	
	printf("\n");
	
	return 0;
}
