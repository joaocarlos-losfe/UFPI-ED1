#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <malloc.h>
#include <stdbool.h>

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
bool removerProcessoDaFila(FilaProcessos *fila_processos);
void exibirProcessos(FilaProcessos *fila_processos);

int menu();

int main()
{
    setlocale(LC_ALL, "Portuguese");

    FilaProcessos processos_prioridade_1; processos_prioridade_1.inicio = processos_prioridade_1.fim = NULL; // alta
    FilaProcessos processos_prioridade_2; processos_prioridade_2.inicio = processos_prioridade_2.fim = NULL; // media
    FilaProcessos processos_prioridade_3; processos_prioridade_3.inicio = processos_prioridade_3.fim = NULL; // baixa

    ProcessoInfo processo;

    //dados para debug 

    // fila de processos 1
    processo.numero_processo = 1;
    processo.tempo_processamento = 5;
    processo.prioridade = alta;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_1, processo);

    processo.numero_processo = 2;
    processo.tempo_processamento = 2;
    processo.prioridade = alta;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_1, processo);

    processo.numero_processo = 3;
    processo.tempo_processamento = 3;
    processo.prioridade = alta;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_1, processo);


    // fila de processos 2
    processo.numero_processo = 11;
    processo.tempo_processamento = 4;
    processo.prioridade = media;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_2, processo);

    processo.numero_processo = 22;
    processo.tempo_processamento = 1;
    processo.prioridade = media;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_2, processo);

    processo.numero_processo = 33;
    processo.tempo_processamento = 2;
    processo.prioridade = media;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_2, processo);

    // fila de processos 3
    processo.numero_processo = 1111;
    processo.tempo_processamento = 5;
    processo.prioridade = baixa;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_3, processo);

    processo.numero_processo = 2222;
    processo.tempo_processamento = 2;
    processo.prioridade = baixa;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_3, processo);

    processo.numero_processo = 3333;
    processo.tempo_processamento = 3;
    processo.prioridade = baixa;
    processo.qtd_vezes_passou_na_fila = 0;

    inserirProcessoNaFila(&processos_prioridade_3, processo);

    //exibindos os processos

    printf("\nFila processos 1 (alta)\n");
    exibirProcessos(&processos_prioridade_1);

    printf("\nFila processos 2 (media)\n");
    exibirProcessos(&processos_prioridade_2);

    printf("\nFila processos 3 (baixa)\n");
    exibirProcessos(&processos_prioridade_3);

    
    /*

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

    */
    
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
    printf("\n 6 - Mostrar quanto tempo falta para executar os processos de uma determinada fila ");
    printf("\n 7 - Mostrar quanto tempo de processamento ainda falta para chegar em um determinado processo");
    printf("\n 8 - Mostrar quanto tempo de processamento ainda falta para chegar em um determinado processo");
    printf("\n 9 - Mostrar quanto tempo de processamento ainda restam para terminar cada fila e todas as filas");
    printf("\n\n > ");
    scanf("%d", &op);

    return op;
}

int numeroDeProcessoNaFila(FilaProcessos *fila_processos)
{
    DadosProcesso end = fila_processos->inicio;
    int contador = 0;

    while (end != NULL)
    {
        contador+=1;

        end = end->proximo_processo;
    }
    
    return contador;
}

void inserirProcessoNaFila(FilaProcessos *fila_processos, ProcessoInfo processo_info)
{
    DadosProcesso novo_processo = (DadosProcesso) malloc(sizeof(Processo));
    novo_processo->processo = processo_info;
    novo_processo->proximo_processo = NULL;

    if(fila_processos->inicio == NULL)
        fila_processos->inicio = novo_processo;
    else
        fila_processos ->fim->proximo_processo = novo_processo;
    
    fila_processos ->fim = novo_processo;
}

bool removerProcessoDaFila(FilaProcessos *fila_processos)
{
    if(fila_processos->inicio == NULL)
        return false; // fila vazia
    DadosProcesso apagar_processo = fila_processos ->inicio;

    fila_processos->inicio = fila_processos->inicio->proximo_processo;

    free(apagar_processo);

    if(fila_processos->inicio == NULL) 
        fila_processos->fim = NULL;
    
    return true; // processo removido do inicio da fila com sucesso
}

void exibirProcessos(FilaProcessos *fila_processos)
{   
                //edereço  do primeiro elemento da fila
    DadosProcesso end = fila_processos->inicio;

    int n_processo = 1;

    while (end != NULL)
    {
        printf("\nprocesso %d: \n", n_processo);

        printf("\nNumero: %d", end->processo.numero_processo);
        printf("\nTempo: %d", end->processo.tempo_processamento);
        printf("\nPrioridade: %d ", end->processo.prioridade);
        if(end->processo.prioridade == alta)
            printf("(alta)");
        else if (end->processo.prioridade == media)
            printf("(media)");
        else if (end->processo.prioridade == baixa)
            printf("(baixa)");

        printf("\nquantidade de vezes que passou na fila: %d\n", end->processo.qtd_vezes_passou_na_fila);
      
        end = end->proximo_processo;
        n_processo++;
    }
    
}