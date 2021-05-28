/*
	terceira questão referente a primeira avaliação da discpina de Estrurura de dados I.
	
	Autores: João Carlos de Sousa Fé && Vitor José Ferreira dos Santos de Santana.
	Data de inicio da resolução dos exercicios: 20/04/2021
	
	Questão 3. 
		Faça um programa em C que tenha um menu de opções para cadastrar, buscar e 
		imprimir cursos e suas disciplinas. Para isto, crie um vetor de curso, onde 
		cada curso deve ter: código do curso, nome, quantidade de períodos e carga 
		horária total, turno(manhã, tarde, noite, integral). Além disso, um vetor 
		de disciplinas contendo: código da disciplina, código do Curso, nome, período 
		a qual ela pertence, carga horária da disciplina(valor múltiplo de 15). 
		Os vetores devem ser ordenados pelo seus códigos
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define max_disciplinas 10
#define max_cursos 10

typedef struct
{
	int codigo_da_disciplina;
	int codigo_curso;
	char nome_disciplina[50];
	int periodo_da_disciplina;
	int carga_horaria;

} Disciplina;

typedef struct
{
	int codigo_curso;
	char nome_curso[50];
	int qtd_periodos;
	int carga_horaria;
	char turno[10];

	Disciplina disciplinas[max_disciplinas];
	int qtdD; // quantidade de disciplinas e index

} Curso;

void cadastrarCurso(Curso *curso, int *cc);
void cadastrarDisciplina(Curso *cursos, int *cc);
void mostrarCurso(Curso *cursos, int *cc);
void mostrarDiciplina(Curso *cursos, int *cc);
void mostrarDisciplinasCurso(Curso *cursos, int *cc);
void mostrarCursosTurno(Curso *cursos, int *cc);
void mostrarDisciplinasPeriodo(Curso *cursos, int *cc);
void removerDisciplina(Curso *cursos, int *cc);
void removerCurso(Curso *cursos, int *cc);

int PesquisarCurso(Curso *cursos, int chave, int Tam);
int PesquisarDisciplina(Disciplina *disciplinas, int chave, int Tam);

void quicksortCursos(Curso *cursos, int began, int length);
void quicksortDisciplinas(Disciplina *Disciplinas, int began, int length);


int main(int argc, char** argv)
{
	setlocale(LC_ALL, "");
	fflush(stdin);
	Curso cursos[max_cursos];
	int count_cursos = 0; //numero de cursos e tambem funciona como incremento ou decremento de indice
	char op;

	while(1)
	{
		fflush(stdin);
		printf("\na - Cadastrar curso");
		printf("\nb - Cadastrar disciplina");
		printf("\nc - mostrar um curso");
		printf("\nd - mostrar uma disciplina");
		printf("\ne - mostrar todos os cursos de um turno");
		printf("\nf - Mostrar todas as disciplinas de um Curso");
		printf("\ng - Mostrar disciplinas de um período");
		printf("\nh - Remover uma disciplina");
		printf("\ni - Remover um curso\nopção: ");
		scanf(" %c", &op);
		
		switch(op)
		{
		case 1:
			cadastrarCurso(cursos, &count_cursos);
			break;
		case 2:
			cadastrarDisciplina(cursos, &count_cursos);
			break;
		case 3:
			mostrarCurso(cursos, &count_cursos);	
			break;
		case 4:
			mostrarDiciplina(cursos, &count_cursos);
			break;
		case 5:
			mostrarCursosTurno(cursos, &count_cursos);
			break;
		case 6:
			mostrarDisciplinasCurso(cursos, &count_cursos);
			break;
		case 7:
			mostrarDisciplinasPeriodo(cursos, &count_cursos);
			break;
		case 8:
			removerDisciplina(cursos, &count_cursos);
			break;
		case 9:
			removerCurso(cursos, &count_cursos);
			break;
		default:
			break;
		}
	}

	return 0;
}

void removerCurso(Curso *cursos, int *cc)
{
	int temp_codigo;

	if(*cc == 0)
	{
		printf("nenhum curso cadastrado");
	}
	else
	{
		printf("\nCódigo do curso: ");
		scanf("%d", &temp_codigo);
		int indexCurso = PesquisarCurso(cursos, temp_codigo, *cc);

		if(indexCurso != -1)
		{
			if(cursos[indexCurso].qtdD == 0)
			{
				int op = 0;
				printf("\nCurso que sera removido: %s", cursos[indexCurso].nome_curso);
				printf("\n confirmar exclusão: 1 - excluir, outro valor para cancelar: ");
				scanf("%d", &op);
				if(op == 1)
				{
					Curso cursos_temp[(*cc) - 1];
					int j = 0;
					int i = 0;

					if(indexCurso == 0)
					{
						(*cc) -= 1;
					}
					else
					{
						for(i = 0; i < *cc; i++)
						{
							if(i != indexCurso) // não copia o indice que pretende excluir
							{
								cursos_temp[j] = cursos[i];
								j++;
							}
						}

						for(i = 0; i < j; i++)
						{
							cursos[i] = cursos_temp[i];
						}

						(*cc) -= 1;
					}

					printf("\ncurso excluido...\n");
				}
				else
				{
					printf("\noperação de exclusão cancelada...\n");
				}
			}
			else
			{
				printf("\nCurso ainda possui disciplinas cadastradas\n");
			}
		}
		else
		{
			printf("\nCurso não encontrado\n");
		}
	}
}

void removerDisciplina(Curso *cursos, int *cc)
{
	int temp_codigo, i, l = 0, c = 0;
	printf("\nCódigo do curso: ");
	scanf("%d", &temp_codigo);
	int indexCurso = PesquisarCurso(cursos, temp_codigo, *cc);

	if(indexCurso != -1)
	{
		if(cursos[indexCurso].qtdD == 0)
		{
			printf("\n O curso não tem nenhuma disciplina cadastrada\n");
		}
		else
		{
			printf("\nCódigo da disciplina que deseja remover: ");
			scanf("%d", &temp_codigo);

			i = PesquisarDisciplina(cursos[indexCurso].disciplinas, temp_codigo, cursos[indexCurso].qtdD);

			if(i != -1)
			{
				if(cursos[indexCurso].qtdD == 1 || (cursos[indexCurso].qtdD - 1) == i)
				{
					cursos[indexCurso].qtdD -= 1;
				}
				else
				{
					for(l = i; l < cursos[indexCurso].qtdD; i++)
					{
						cursos[indexCurso].disciplinas[i] = cursos[indexCurso].disciplinas[i + 1];
						c++;
					}

					cursos[indexCurso].qtdD -= c;
				}

				printf("disciplina removida...");
			}
			else
			{
				printf("\nDisciplina não encontrada\n");
			}
		}
	}
	else
	{
		printf("\nCurso não encontrado");
	}

}

void mostrarDisciplinasPeriodo(Curso *cursos, int *cc)
{
	int temp_codigo, periodo, c = 0;
	printf("\nCódigo do curso: ");
	scanf("%d", &temp_codigo);
	int i;
	int indexCurso = PesquisarCurso(cursos, temp_codigo, *cc);

	if(indexCurso != -1)
	{
		printf("\nPeriodo: ");
		scanf("%d", &periodo);

		for(i = 0; i < cursos[indexCurso].qtdD; i++)
		{
			if(cursos[indexCurso].disciplinas[i].periodo_da_disciplina == periodo)
			{
				printf("Dsiciplina %s \n", cursos[indexCurso].disciplinas[i].nome_disciplina);
				c++;
			}
		}
		if(c == 0)
			printf("\nNenhuma disciplina encontrada para o periodo informado\n");
	}
	else
	{
		printf("\nCurso não encontrado...\n");
	}
}

void mostrarCursosTurno(Curso *cursos, int *cc)
{
	char turno[20];
	printf("\nTurno: ");
	fflush(stdin);
	scanf(" %[^\n]s", turno);
	int i, c = 0;

	for(i = 0; i < *cc; i++)
	{
		if(strcmp(turno, cursos[i].turno) == 0)
		{
			printf("\nNome do curso: %s", cursos[i].nome_curso);
			printf("\nQuantidade de periodos: %d", cursos[i].qtd_periodos);
			printf("\nCarga horaria: %d", cursos[i].carga_horaria);
			printf("\nTurno: %s\n", cursos[i].turno);
			c++;
		}
	}

	if(c == 0)
		printf("\nCursos no turno informado não encontrado\n");
}

void mostrarDisciplinasCurso(Curso *cursos, int *cc)
{
	int temp_codigo;
	printf("\nCódigo do curso: ");
	scanf("%d", &temp_codigo);

	int i = 0;
	int index = PesquisarCurso(cursos, temp_codigo, *cc);

	if(index != -1)
	{
		if(cursos[index].qtdD == 0)
		{
			printf("\nNenhuma disciplina para o curso informado foi cadastrada\n");
		}
		else
		{
			printf("%d disciplinas encontradas para o curso de %s", cursos[index].qtdD, cursos[index].nome_curso);

			for(i = 0; i < cursos[index].qtdD; i++)
			{
				printf("\ncurso %d\n", i + 1);
				printf("\nNome disciplina: %s", cursos[index].disciplinas[i].nome_disciplina);
				printf("\nCódigo: %d", cursos[index].disciplinas[i].codigo_da_disciplina);
				printf("\nCódigo do curso da disciplina: %d", cursos[index].disciplinas[i].codigo_curso);
				printf("\nPeriodo da disciplina: %d", cursos[index].disciplinas[i].periodo_da_disciplina);
				printf("\nCarga horaria: %d\n", cursos[index].disciplinas[i].carga_horaria);
			}
		}
	}
}

int PesquisarDisciplina(Disciplina *disciplinas, int chave, int Tam)
{
	int inf = 0;     // limite inferior (o primeiro índice de vetor em C é zero          )
	int sup = Tam - 1; // limite superior (termina em um número a menos. 0 a 9 são 10 números)
	int meio;
	while (inf <= sup)
	{
		meio = (inf + sup) / 2;
		if (chave == disciplinas[meio].codigo_da_disciplina)
			return meio; //encontrado o indice correspondente a disciplina
		if (chave < disciplinas[meio].codigo_da_disciplina)
			sup = meio - 1;
		else
			inf = meio + 1;
	}
	return -1;   // não encontrado
}

void mostrarDiciplina(Curso *cursos, int *cc)
{
	int i, index = -1, c = 0;

	int temp_codigo;
	printf("\nCódigo da disciplina: ");
	scanf("%d", &temp_codigo);
	printf("\n\nDisciplina(s) encontrada(s) com o codigo informado!!");

	for(i = 0; i < *cc; i++)
	{
		index = PesquisarDisciplina(cursos[i].disciplinas, temp_codigo, cursos[i].qtdD);

		if(index != -1)
		{
			printf("\nCódigo: %d", cursos[i].disciplinas[index].codigo_da_disciplina);
			printf("\nCódigo do curso da disciplina: %d", cursos[i].disciplinas[index].codigo_curso);
			printf("\nNome disciplina: %s", cursos[i].disciplinas[index].nome_disciplina);
			printf("\nPeriodo da disciplina: %d", cursos[i].disciplinas[index].periodo_da_disciplina);
			printf("\nCarga horaria: %d\n", cursos[i].disciplinas[index].carga_horaria);
			c++;
			//break;
		}
	}

	if(c == 0)
		printf("\nNenhuma disciplina correspondente ao condigo informado foi encontrada\n");
}

void mostrarCurso(Curso *cursos, int *cc)
{
	int temp_codigo;
	printf("\nCódigo do curso: ");
	scanf("%d", &temp_codigo);

	int i = PesquisarCurso(cursos, temp_codigo, *cc);

	if(i == -1)
	{
		printf("\n\nCurso não encontrado");
	}
	else
	{
		printf("\n\nCurso encontrado !!!");
		printf("\nCódigo: %d", cursos[i].codigo_curso);
		printf("\nNome do curso: %s", cursos[i].nome_curso);
		printf("\nQuantidade de periodos: %d", cursos[i].qtd_periodos);
		printf("\nCarga horaria: %d", cursos[i].carga_horaria);
		printf("\nTurno: %s\n", cursos[i].turno);

	}
}

void cadastrarDisciplina(Curso *cursos, int *cc)
{
	printf("\nCadastrar disciplina\n");
	int temp_codigo, i, ld = 0;

	printf("\nCódigo do curso: ");
	scanf("%d", &temp_codigo);

	i = PesquisarCurso(cursos, temp_codigo, *cc);

	if(i == -1)
	{
		printf("\ncurso não encontrado");
	}
	else
	{
		printf("\nCurso encontrado: %s. Turno: %s. Total de disciplinas cadastradas: %d", cursos[i].nome_curso, cursos[i].turno, cursos[i].qtdD);

		ld = cursos[i].qtdD; // lista diciplina == ultimo index

		printf("\nCódigo disciplina: ");
		scanf("%d", &cursos[i].disciplinas[ld].codigo_da_disciplina);

		cursos[i].disciplinas[ld].codigo_curso = cursos[i].codigo_curso;
		
		printf("\nNome da disciplina: ");
		fflush(stdin);
		scanf("%29[^\n]s*c", cursos[i].disciplinas[ld].nome_disciplina);

		printf("\nPeriodo da disciplina: ");
		scanf("%d", &cursos[i].disciplinas[ld].periodo_da_disciplina);

		while(cursos[i].disciplinas[ld].periodo_da_disciplina > cursos[i].qtd_periodos || cursos[i].disciplinas[ld].periodo_da_disciplina < 1)
		{
			printf("\nerro !! ");
			printf("\no curso de %s tem %d períodos, logo uma disciplina não pode ser cadastrada no %d período", cursos[i].nome_curso, cursos[i].qtd_periodos, cursos[i].disciplinas[ld].periodo_da_disciplina);
			printf("\nVerifique o periodo da disciplina e digite novamente: ");
			scanf("%d", &cursos[i].disciplinas[ld].periodo_da_disciplina);
		}

		printf("\nCarga horaria da disciplina: ");
		scanf("%d", &cursos[i].disciplinas[ld].carga_horaria);
		
		fflush(stdin);
		while(cursos[i].disciplinas[ld].carga_horaria % 15 != 0)
		{
			printf("\nerro !! digite um valor multiplo de 15 (15, 30, 45, 60...)");
			printf("\nDigite a carga horaria da disciplina novamente: ");
			scanf("%d", &cursos[i].disciplinas[ld].carga_horaria);
		}

		quicksortDisciplinas(cursos[i].disciplinas, 0, cursos[i].qtdD);

		cursos[i].qtdD += 1;

		printf("\nDiciplina cadastrada\n");

	}

	printf("\n");
}


void quicksortDisciplinas(Disciplina *Disciplinas, int began, int length)
{
	int i, j, pivo;
	Disciplina disciplina_aux;
	i = began;
	j = length;
	pivo = Disciplinas[(began + length) / 2].codigo_da_disciplina;

	while(i <= j)
	{
		while(Disciplinas[i].codigo_da_disciplina < pivo && i < length)
		{
			i++;
		}
		while(Disciplinas[j].codigo_da_disciplina > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			disciplina_aux = Disciplinas[i];
			//aux = values[i];
			Disciplinas[i] = Disciplinas[j];
			Disciplinas[j] = disciplina_aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quicksortDisciplinas(Disciplinas, began, j + 1);
	if(i < length)
		quicksortDisciplinas(Disciplinas, i, length);
}

void quicksortCursos(Curso *cursos, int began, int length)
{
	int i, j, pivo;
	Curso curso_aux;
	i = began;
	j = length;
	pivo = cursos[(began + length) / 2].codigo_curso;

	while(i <= j)
	{
		while(cursos[i].codigo_curso < pivo && i < length)
		{
			i++;
		}
		while(cursos[j].codigo_curso > pivo && j > began)
		{
			j--;
		}
		if(i <= j)
		{
			curso_aux = cursos[i];
			//aux = values[i];
			cursos[i] = cursos[j];
			cursos[j] = curso_aux;
			i++;
			j--;
		}
	}
	if(j > began)
		quicksortCursos(cursos, began, j + 1);
	if(i < length)
		quicksortCursos(cursos, i, length);
}

int PesquisarCurso(Curso *cursos, int chave, int Tam)
{
	int inf = 0;     // limite inferior (o primeiro índice de vetor em C é zero          )
	int sup = Tam - 1; // limite superior (termina em um número a menos. 0 a 9 são 10 números)
	int meio;
	while (inf <= sup)
	{
		meio = (inf + sup) / 2;
		if (chave == cursos[meio].codigo_curso)
			return meio; //encontrado o indice correspondente ao curso
		if (chave < cursos[meio].codigo_curso)
			sup = meio - 1;
		else
			inf = meio + 1;
	}
	return -1;   // não encontrado
}

void cadastrarCurso(Curso *cursos, int *cc)
{
	printf("\ncursos cadastrados: %d\n\n", *cc);

	if(*cc > max_cursos)
	{
		printf("\nnumero maximo de cursos cadastrados");
	}
	else
	{
		printf("\nCódigo do curso: ");
		scanf("%d", &cursos[*cc].codigo_curso);

		if(*cc > 0)
		{
			while(PesquisarCurso(cursos, cursos[*cc].codigo_curso, *cc) != -1)
			{
				printf("\njá existe um curso cadastrado. tente novamente!");
				printf("\n\nCódigo do curso: ");
				scanf("%d", &cursos[*cc].codigo_curso);
			}
		}

		printf("\nNome do curso: ");
		fflush(stdin);
		scanf("%29[^\n]s", cursos[*cc].nome_curso);
		printf("\nQuantidade de periodos: ");
		scanf("%d", &cursos[*cc].qtd_periodos);
		printf("\nCarga horaria: ");
		scanf("%d", &cursos[*cc].carga_horaria);
		fflush(stdin);
		printf("\nTurno do curso (manhã, tarde, noite, integral): ");
		scanf("%[^\n]s", cursos[*cc].turno);
		
		cursos[*cc].qtdD = 0;

		printf("\ncurso cadastrado\n");

		//após um curso ser adicionado, ele ja é ordenado com os cursos ja cadastrados
		quicksortCursos(cursos, 0, *cc);
		(*cc) += 1;
	}
}