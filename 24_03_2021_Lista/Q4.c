/*
	João Carlos de Sousa Fé - 26/03/2021
	Estrutura de Dados I
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define numero_maximo_de_alunos 4

typedef struct 
{
	char matricula[10];
	char nome[30];
	unsigned int idade;
	float altura;
	
}Aluno;

void alturaMaiorAlunoParametro(Aluno *aluno, float *aluno_mais_alto)
{
	int i=0;
	
	*aluno_mais_alto = aluno[0].altura;
	
	for(i=1; i<numero_maximo_de_alunos; i++)
	{
		if(aluno[i].altura > *aluno_mais_alto )
			*aluno_mais_alto = aluno[i].altura;
	}
}

float alturaMenorAlunofuncao(Aluno *aluno)
{
	int i=0;
	
	float aluno_mais_baixo = aluno[0].altura;
	
	for(i=1; i<numero_maximo_de_alunos; i++)
	{
		if(aluno[i].altura < aluno_mais_baixo)
		{
			aluno_mais_baixo = aluno[i].altura;	
		}
	}
	return aluno_mais_baixo;
}

float mediaDeAlturaFuncao(Aluno *aluno)
{
	float media = 0.00;
	int i = 0;
	
	for(i=0; i<numero_maximo_de_alunos; i++)
	{
		media = media + aluno[i].altura;
	}
	
	return (media / numero_maximo_de_alunos);
}

int main(int argc, char** argv)
{
	Aluno alunos[numero_maximo_de_alunos];
	
	float aluno_mais_alto = 0;
	
	//exemplo
	
	//aluno 1
	strcpy(alunos[0].matricula, "1sds");
	strcpy(alunos[0].nome, "jose");
	alunos[0].idade = 15;
	alunos[0].altura = 1.75;
	
	//aluno 2
	strcpy(alunos[1].matricula, "sdasadsd");
	strcpy(alunos[1].nome, "antonio");
	alunos[1].idade = 24;
	alunos[1].altura = 1.48;
	
	//aluno 3
	strcpy(alunos[2].matricula, "sadhads1dasd");
	strcpy(alunos[2].nome, "felipe");
	alunos[2].idade = 16;
	alunos[2].altura = 1.89;
	
	
	//aluno 4
	strcpy(alunos[3].matricula, "sdasdasd");
	strcpy(alunos[3].nome, "augusto");
	alunos[3].idade = 16;
	alunos[3].altura = 1.72;
	
	alturaMaiorAlunoParametro(alunos, &aluno_mais_alto);
	
	//A):
	printf("Maior altura: %.2f\n", aluno_mais_alto);
	
	//B):
	printf("Menor altura: %.2f\n", alturaMenorAlunofuncao(alunos));
	
	//C):
	printf("Media de altura dos alunos: %.2f", mediaDeAlturaFuncao(alunos));
	
	return 0;
}