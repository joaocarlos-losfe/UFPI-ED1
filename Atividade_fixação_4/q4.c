#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int codigo;
	char nome[30];
	int qtd_periodos;

} DadosCurso;

typedef struct
{
	int codigo_disciplina;
	int codigo_curso;
	char nome_displina[30];
	int periodo;
	int carga_horaria;

} InfoDiciplinas;

void quickDisciplina(InfoDiciplinas *disciplina, int inicio, int fim)
{
	int pivo, i, j, meio;
	
	int cd;
	int cc;
	char n[31];
	int p;
	int ch;
	//
	i = inicio;
	j = fim;
	meio = (int) ((i + j) / 2);
	pivo = disciplina[meio].codigo_disciplina;
	do
	{
		while (disciplina[i].codigo_disciplina < pivo) i = i + 1;
		while (disciplina[j].codigo_disciplina > pivo) j = j - 1;
		
		if(i <= j)
		{
			
			cd = disciplina[i].codigo_disciplina;
			cc = disciplina[i].codigo_curso;
			strcpy(n, disciplina[i].nome_displina);
			p = disciplina[i].periodo;
			ch = disciplina[i].carga_horaria;

			disciplina[i].codigo_disciplina = disciplina[j].codigo_disciplina;
			disciplina[i].codigo_curso = disciplina[j].codigo_curso;
			strcpy(disciplina[i].nome_displina, disciplina[j].nome_displina);
			disciplina[i].periodo = disciplina[j].periodo;
			disciplina[i].carga_horaria = disciplina[j].carga_horaria;

			disciplina[j].codigo_disciplina = cd;
			disciplina[j].codigo_curso = cc;
			strcpy(disciplina[j].nome_displina, n);
			disciplina[j].periodo = p;
			disciplina[j].carga_horaria = ch;
			//
			i = i + 1;
			j = j - 1;
		}
	}
	while(j > i);
	if(inicio < j) quickDisciplina(disciplina, inicio, j);
	if(i < fim) quickDisciplina(disciplina, i, fim);
}

void quickCurso(DadosCurso *curso, int inicio, int fim)
{
	int pivo, i, j, meio;
	// importante para a gambiarra de ordenação!
	int cd;
	char n[31];
	int p;
	//
	i = inicio;
	j = fim;
	meio = (int) ((i + j) / 2);
	pivo = curso[meio].codigo;
	do
	{
		while (curso[i].codigo < pivo) i = i + 1;
		while (curso[j].codigo > pivo) j = j - 1;
		if(i <= j)
		{
			// modo gambiarra (eu acho)
			cd = curso[i].codigo;
			strcpy(n, curso[i].nome);
			p = curso[i].qtd_periodos;

			curso[i].codigo = curso[j].codigo;
			strcpy(curso[i].nome, curso[j].nome);
			curso[i].qtd_periodos = curso[j].qtd_periodos;

			curso[j].codigo = cd;
			strcpy(curso[j].nome, n);
			curso[j].qtd_periodos = p;
			//
			i = i + 1;
			j = j - 1;
		}
	}
	while(j > i);
	if(inicio < j) quickCurso(curso, inicio, j);
	if(i < fim) quickCurso(curso, i, fim);
}

DadosCurso nome_curso_maior_qtd_periodo(DadosCurso *cursos, int idx, int n_cursos)
{
	DadosCurso curso = cursos[0];
	int i = idx;
	if(i > 0)
		curso = cursos[i];
	if(i == n_cursos)
		return curso;
	else
	{
		if(cursos[i + 1].qtd_periodos > curso.qtd_periodos)
			curso = cursos[i + 1];

		nome_curso_maior_qtd_periodo(cursos, idx + 1, n_cursos);
	}

	return curso;
}

void qtd_disciplinas_determinado_curso(DadosCurso cursos[3], int codigo_disciplina, int i, int *qtd)
{
	if(i < 3)
	{
		if(codigo_disciplina == cursos[i].codigo)
			(*qtd)++;

		qtd_disciplinas_determinado_curso(cursos, codigo_disciplina, i + 1, qtd);
	}
}

void qtd_periodos(int periodo, InfoDiciplinas disciplinas[3], int *qtd, int i)
{
	if(i<3)
	{
		if(periodo == disciplinas[i].periodo)
		{
			(*qtd)++;
		}
	}
}

int main(int argc, char** argv)
{

	DadosCurso cursos[3];
	InfoDiciplinas disciplinas[3];
	int i;

	printf("\nPreenchendo o curso: ");
	for(i = 0; i < 3; i++)
	{
		printf("\nCodigo ");
		scanf("%d", &cursos[i].codigo);

		printf("\nnome do curso: ");
		scanf("%29[^\n]s", cursos[i].nome);

		printf("\nquantidade de periodos: ");
		scanf("%d", &cursos[i].qtd_periodos);
	}

	printf("\n\nPreenchendo as disciplinas: ");
	
	quickCurso(cursos, 0, 3);

	for(i = 0; i < 3; i++)
	{
		printf("\nCodigo disciplina: ");
		scanf("%d", &disciplinas[i].codigo_disciplina);

		printf("\nCodigo do curso: ");
		scanf("%d", &disciplinas[i].codigo_curso);

		printf("\nNome da disciplina: ");
		scanf("%29[^\n]s", disciplinas[i].nome_displina);

		printf("\nPeriodo: ");
		scanf("%d", &disciplinas[i].periodo);

		printf("\nCarga horaria: ");
		scanf("%d", &disciplinas[i].carga_horaria);
	}
	
	quickDisciplina(disciplinas, 0, 3);

	//----------------------A)-----------------------------------
	DadosCurso curso = nome_curso_maior_qtd_periodo(cursos, 0, 3);

	printf("\nCurso com maior periodo: %s\n", curso.nome);

	//----------------------B)-----------------------------------

	int qtr_disciplinas = 0;

	int codigo_disciplina;

	printf("\nCodigo da disciplina: ");
	scanf("%d", &codigo_disciplina);

	qtd_disciplinas_determinado_curso(cursos, codigo_disciplina, 0, &qtr_disciplinas);

	printf("\ntotal de disciplinas: %d", qtr_disciplinas);
	printf("\n");

	//----------------------C)-----------------------------------

	int qtd_disciplinas = 0;
	int periodo = 0;

	printf("\nDigite o perido: ");
	scanf("%d", &periodo);

	qtd_periodos(periodo, disciplinas, &qtd_disciplinas, 0);
	
	printf("\nQuantidade de disciplinas: %d", qtd_disciplinas);

	return 0;
}
