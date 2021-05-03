#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int matricula;
	char nome[20];
	char curso[30];
	int periodo;

} Aluno;

//1)
void ordena(Aluno *alunos)
{
	int i, j;

	Aluno temp_alumo;

	for (i = 1; i < 6; i++)
	{
		temp_alumo = alunos[i];
		j = i - 1;

		while(temp_alumo.nome[0] < alunos[j].nome[0] )
		{
			alunos[j + 1] = alunos[j];
			j--;
		}
		alunos[j + 1] = temp_alumo;
	}
}

//A)
void devolver_alunos_determinado_perido(Aluno alunos[5], int periodo, Aluno *alunos_periodo, int i, int *idx)
{
	if(i < 5)
	{
		if(alunos[i].periodo == periodo)
		{
			alunos_periodo[*idx] = alunos[i];
			(*idx)++;
		}
		devolver_alunos_determinado_perido(alunos, periodo, alunos_periodo, i + 1, idx);
	}
}

//B)
void devolver_quantidade_alunos_determinado_curso(Aluno alunos[5], char *nome_curso, int i, int *qtd)
{
	if(i < 5)
	{
		if(strcmp(alunos[i].curso, nome_curso) == 0)
			(*qtd)++;

		devolver_quantidade_alunos_determinado_curso(alunos, nome_curso, i + 1, qtd);
	}
}

//C)
void devolver_aluno_por_matricula(Aluno alunos[5], Aluno *aluno, int matricula, int i)
{
	if(i < 5)
	{
		if(alunos[i].matricula == matricula)
		{
			*aluno = alunos[i];
			i = 5;
		}
		devolver_aluno_por_matricula(alunos, aluno, matricula, i+1);
	}
}

int main(int argc, char** argv)
{
	Aluno alunos[6];


	//dados de teste
	alunos[0].matricula = 2020151;
	strcpy(alunos[0].nome, "joao");
	strcpy(alunos[0].curso, "sistemas");
	alunos[0].periodo = 5;

	alunos[1].matricula = 2019171;
	strcpy(alunos[1].nome, "antonio");
	strcpy(alunos[1].curso, "sistemas");
	alunos[1].periodo = 6;

	alunos[2].matricula = 2018151;
	strcpy(alunos[2].nome, "amanda");
	strcpy(alunos[2].curso, "letras");
	alunos[2].periodo = 5;

	alunos[3].matricula = 2022121;
	strcpy(alunos[3].nome, "matheus");
	strcpy(alunos[3].curso, "biologia");
	alunos[3].periodo = 4;

	alunos[4].matricula = 2017121;
	strcpy(alunos[4].nome, "tiago");
	strcpy(alunos[4].curso, "fisica");
	alunos[4].periodo = 3;

	alunos[5].matricula = 2022391;
	strcpy(alunos[5].nome, "bia");
	strcpy(alunos[5].curso, "historia");
	alunos[5].periodo = 4;

	int i = 0;

	//mostrando sem ordenar
	for(i = 0; i < 6; i++)
	{
		printf("matricula: %d, nome: %s, curso: %s, periodo: %d\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso, alunos[i].periodo);
	}

	ordena(alunos);

	//mostrando ordenados
	printf("\n\nordenados:\n");
	for(i = 0; i < 6; i++)
	{
		printf("matricula: %d, nome: %s, curso: %s, periodo: %d\n", alunos[i].matricula, alunos[i].nome, alunos[i].curso, alunos[i].periodo);
	}

	//-------------------------------A)-------------------------------------
	printf("\ndevolvendo alunos pelo periodo especificado: \n");

	int periodo = 6;

	Aluno alunos_por_periodo[5];

	i = 0;
	int index = 0;

	devolver_alunos_determinado_perido(alunos, periodo, alunos_por_periodo, i, &index);

	for(i = 0; i < index; i++)
		printf("matricula: %d, nome: %s, curso: %s, periodo: %d\n", alunos_por_periodo[i].matricula, alunos_por_periodo[i].nome, alunos_por_periodo[i].curso, alunos_por_periodo[i].periodo);


	//--------------------------------B)------------------------------------
	printf("\ndevolvendo a quantidade de alunos pelo nome do curso: \n");
	i = 0;
	int qtd_alunos_curso = 0;

	char curso[] = "sistemas";

	devolver_quantidade_alunos_determinado_curso(alunos,  curso, i, &qtd_alunos_curso);

	printf("Quantidade de alunos para o curso de %s: %d aluno(s)\n", curso, qtd_alunos_curso);

	//--------------------------------C-------------------------------------)

	int matricula = 2022391;
	int idx = 0;
	Aluno aluno;
		
	devolver_aluno_por_matricula(alunos, &aluno, matricula, idx);
	printf("\ndevolvendo o aluno por busca de matricula %d: \n", matricula);
	printf("matricula: %d, nome: %s, curso: %s, periodo: %d\n", aluno.matricula, aluno.nome, aluno.curso, aluno.periodo);

	return 0;
}
