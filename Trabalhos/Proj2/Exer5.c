#include <stdio.h>
#include <stdlib.h>
#include <locale.h>

#define alta 1
#define media 2
#define baixa 3

typedef struct 
{
    int numero_processo;
    int tempo_processamento;
    int prioridade;
    int qtd_vezes_passou_na_fila;

}ProcessoInfo;

typedef struct aux
{
	ProcessoInfo processo;
	struct aux* proximo_processo;

}Processo,  *DadosProcesso;

typedef struct
{
	DadosProcesso inicio;
	DadosProcesso fim;

}FilaProcessos;

int numeroDeProcessoNaFila(FilaProcessos *fila_processos);
void inserirProcessoNaFila(FilaProcessos *fila_processos, ProcessoInfo processo_info);
void removerProcessoDaFila(FilaProcessos *fila_processos);
void exibirProcessos(FilaProcessos *fila_processos);


int menu();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FilaProcessos processos_prioridade_1; processos_prioridade_1.inicio = processos_prioridade_1.fim = NULL; // alta
    FilaProcessos processos_prioridade_2; processos_prioridade_2.inicio = processos_prioridade_2.fim = NULL; // media
    FilaProcessos processos_prioridade_3; processos_prioridade_3.inicio = processos_prioridade_3.fim = NULL; // baixa


    int op;
    do
    {
        op = menu();

        switch (op)
        {
        case 1:
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        case 9:
            break;        
        default:
            break;
        }
    
    }while (op!=0);
    
    return 0;
}

int menu()
{
    int op;
    printf("\n 0 - Sair");
    printf("\n 1 - Inserir processo na fila");
    printf("\n 2 - Escolher processo");
    printf("\n 3 - Mostrar processo das filas");
    printf("\n 4 - Mostrar proximo processo que irá utilizar o processador");
    printf("\n 5 - Mostrar quantos processos tem em cada fila");
    printf("\n 6 - mostrar quanto tempo falta para executar os processos de uma determinada fila ");
    printf("\n 7 - mostrar quanto tempo de processamento ainda falta para chegar em um determinado processo");
    printf("\n 8 - mostrar quanto tempo de processamento ainda falta para chegar em um determinado processo");
    printf("\n 9 - mostrar quanto tempo de processamento ainda restam para terminar cada fila e todas as filas");
    printf("\n\n > ");
    scanf("%d", &op);

    return op;
}

int numeroDeProcessoNaFila(FilaProcessos *fila_processos)
{

}

void inserirProcessoNaFila(FilaProcessos *fila_processos, ProcessoInfo processo_info)
{

}

void removerProcessoDaFila(FilaProcessos *fila_processos)
{

}

void exibirProcessos(FilaProcessos *fila_processos)
{

}