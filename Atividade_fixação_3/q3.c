#include <stdio.h>
#include <stdlib.h>

void ordena(int *v1, int n)
{
	int i = 0, chave, j=0;

	for (i = 1; i < n; i++)
	{
		chave = v1[i];
		j = i - 1;
		while (j >= 0 && v1[j] > chave)
		{
			v1[j + 1] = v1[j];
			j -= 1;
		}
		v1[j + 1] = chave;
	}
}

int existe(int *v, int tam, int verifica_n)
{
	int existe = 0;
	int i = 0;
	for(i=0; i<tam; i++)
	{
		if(v[i] == verifica_n)
		{
			existe = 1;
			return existe;
		}
	}
	
	return existe;
}

//união usando recursão
void uniao(int *v1, int *v2, int *v3, int q1, int q2, int q3, int i, int j, int *total)
{
	//junta os elementos do array 1 no array 3;
	if(i < q1)
	{
		v3[i] = v1[i];
		*total += 1;
		uniao(v1,v2,v3,q1,q2,q3,i+1,j,total);
			
	}//junta os elementos do array 2 no array 3;
	else if(j<q2)
	{
		//verifica se ja existe um elemento no array 3, repassando o conteudo do array 2 para verificar
		if(!existe(v3, q2, v2[j]))
		{
			v3[i] = v2[j];
			*total +=1;	
			i+=1;
		}
		uniao(v1,v2,v3,q1,q2,q3,i,j+1,total);	
	}
}


int main(int argc, char** argv)
{
	
	//teste de implementação
	
	int v1[5] = {5,2,4,3,1}; 
	
	int v2[5] = {1,2,9,3,8};
	
	int v3[5*5];
	
	ordena(v1, 5);
	ordena(v2, 5);
	
	int i=0, j =0, t = 0; 
	
	uniao(v1,v2,v3,5,5,10,i,j, &t);
	
	
	for(i=0; i<t; i++)
	{
		printf("%d\n", v3[i]);
	}

	return 0;
}
