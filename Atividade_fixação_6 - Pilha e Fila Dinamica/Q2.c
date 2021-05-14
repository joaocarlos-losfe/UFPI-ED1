#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>
#include <string.h>

typedef struct
{
    int matricula;
    char nome[10];
    int idade;
    int ano_escolar;

}Aluno;

typedef struct aux
{
	Aluno aluno;
	struct aux* proximo;

} Elemento,  *DadosPont;

typedef struct
{
	DadosPont inicio;
	DadosPont fim;

}FilaPrincipal;

int contarElementosFila(FilaPrincipal *fila)
{
    
    if(fila->inicio == NULL)
        return 0;

    unsigned int count = 0;
    DadosPont end = fila->inicio;

    while (end != NULL )
    {
        count++;
        end = end->proximo;
    }
    
    free(end);

    return count;
}

void inserirAluno(FilaPrincipal *fila, Aluno aluno)
{
    DadosPont novo_aluno = (DadosPont) malloc(sizeof(Elemento));

    novo_aluno->aluno = aluno;
    novo_aluno->proximo = NULL;

    if(fila->inicio == NULL) 
        fila -> inicio = novo_aluno;
    else 
        fila->fim->proximo = novo_aluno;

    fila->fim = novo_aluno;
}

void removerAlunoDaFila(FilaPrincipal *fila)
{
	if(fila->inicio == NULL)
	{
		printf("impsivel excluir, fila ja esta vazia");
	}
	else
	{
		DadosPont apagar = fila->inicio;
		
		fila -> inicio = fila->inicio->proximo;

		free(apagar);

		if(fila->inicio == NULL)
		{
			fila -> fim = NULL;
		}
	}

}

void exibirAlunos(FilaPrincipal *fila)
{
    
    if(fila->inicio == NULL || fila->fim == NULL)
        printf("\nNenhum aluno inserido na fila...\n");
    else
    {
        DadosPont temp_aluno = fila->inicio;

        while (temp_aluno != NULL )
        {
            printf("\nMatricula do aluno: %d", temp_aluno->aluno.matricula);
            printf("\nNome: %s", temp_aluno->aluno.nome);
            printf("\nIdade: %d", temp_aluno->aluno.idade);
            printf("\nAno escolar: %d\n", temp_aluno->aluno.ano_escolar);
            temp_aluno = temp_aluno->proximo;
        }
    }
}

void sairDaFila(FilaPrincipal *fila, int matricula)
{
    FilaPrincipal tempFila;
    tempFila.inicio = NULL;
    tempFila.fim = NULL;

    DadosPont end = fila->inicio;

    bool achou_aluno = false;

    while (end != NULL) // inserir dados (execeto oque se quer remover) 
    {
       
       if(end->aluno.matricula != matricula)
       {
           inserirAluno(&tempFila, end->aluno);
       }
       else
       {
           achou_aluno = true;
       }

       removerAlunoDaFila(fila);

       end = end->proximo;

    }
    
    end = tempFila.inicio;

    while (end != NULL) // copia de volta sem os alunos removidos...
    {
        inserirAluno(fila, end->aluno);

        removerAlunoDaFila(&tempFila);

        end = end->proximo;
    }
    
    if (achou_aluno)
        printf("\naluno %d encontrado removido da fila\n", matricula);
    else
        printf("\nAluno nao encotrado....");
    
}

void distribuirAlunos(FilaPrincipal *fila_principal, FilaPrincipal *fila1, FilaPrincipal *fila2, FilaPrincipal *fila3, FilaPrincipal *fila4, FilaPrincipal *fila5)
{
    DadosPont end = fila_principal->inicio;

    if(fila_principal->inicio != NULL)
    {
        while (end !=NULL)
        {
            switch (end->aluno.ano_escolar)
            {
            case 5:
                inserirAluno(fila1, end->aluno);
                
                break;
            case 6:
                inserirAluno(fila2, end->aluno);

                break;
            case 7:
                inserirAluno(fila3, end->aluno);
 
                break;
            case 8:
                inserirAluno(fila4, end->aluno);
                break;
            case 9:
                inserirAluno(fila5, end->aluno);
                break;
            default:
                break;
            }

            removerAlunoDaFila(fila_principal);
        
            end = end->proximo;
        }
    }
    
}

int main()
{
    FilaPrincipal fila_alunos;
    fila_alunos.inicio = fila_alunos.fim = NULL;

    FilaPrincipal fila1, fila2, fila3, fila4, fila5, fila6;

    fila1.inicio = fila2.inicio = fila3.inicio = fila4.inicio =  fila5.inicio =  NULL; 
    
    fila1.fim = fila2.fim = fila3.fim = fila4.fim =  fila5.fim =  NULL; 

    Aluno aluno;
    
    aluno.matricula = 111;
    strcpy(aluno.nome, "joao");
    aluno.idade = 15;
    aluno.ano_escolar = 5;

    inserirAluno(&fila_alunos, aluno);

    aluno.matricula = 222;
    strcpy(aluno.nome, "jose");
    aluno.idade = 15;
    aluno.ano_escolar = 6;
    
    inserirAluno(&fila_alunos, aluno);

    aluno.matricula = 333;
    strcpy(aluno.nome, "antonio");
    aluno.idade = 15;
    aluno.ano_escolar = 7;
    
    inserirAluno(&fila_alunos, aluno);

    aluno.matricula = 444;
    strcpy(aluno.nome, "marcos");
    aluno.idade = 15;
    aluno.ano_escolar = 8;
    
    inserirAluno(&fila_alunos, aluno);

    aluno.matricula = 555;
    strcpy(aluno.nome, "antonio");
    aluno.idade = 15;
    aluno.ano_escolar = 9;
    
    inserirAluno(&fila_alunos, aluno);

    int op;
    while (1)
    {
        printf("\n1 - exibir alunos\n");
        printf("\n2 - sair da fila de acordo com a matricula\n");
        printf("\n3 - distribuir alunos\n: ");
        scanf("%d", &op);

        switch (op)
        {
        case 1:
            exibirAlunos(&fila_alunos);
            break;
        case 2:
            int matricula;
            printf("\nEntre com a matricula: ");
            scanf("%d", &matricula);
        case 3:
            distribuirAlunos(&fila_alunos, &fila1, &fila2, &fila3, &fila4, &fila5);
            printf("\nMostrando a fila distribuida: \n");

            printf("\n5 ano: ");
            exibirAlunos(&fila1);

            printf("\n6 ano: ");
            exibirAlunos(&fila2);

            printf("\n7 ano: ");
            exibirAlunos(&fila3);

            printf("\n8 ano: ");
            exibirAlunos(&fila4);

            printf("\n9 ano: ");
            exibirAlunos(&fila5);

        default:
            break;
        }
    }
    return 0;
}