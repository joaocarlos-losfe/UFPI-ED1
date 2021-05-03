//por João Carlos de Sousa Fé. 01/04/2021

#include <stdio.h>
#include <stdlib.h>

char * alteraNome()
{
	char *temp_nome = (char *) malloc(10 * sizeof(char));
	printf("\nNovo nome: ");
	scanf("%s", temp_nome);
	
	return temp_nome;
}

int main(int argc, char** argv)
{
	char *nome = (char *) malloc(10 * sizeof(char));
	char *cpf = (char *) malloc(14 * sizeof(char));
	int op = 0;
	
	while(1)
	{
		printf("\n1 - inserir nome e cpf, 2 - alterar nome, 0 - encerrar programa\nOpcao: ");
		scanf("%d", &op);
		
		if(op == 0)
		{
			free(nome);
			exit(1);
		}
		
		else if(op == 1)
		{
			
			printf("\nNome: ");
			scanf("%s", nome);
			printf("\nCPF: ");
			scanf("%s", cpf);
			
			printf("\nEndereco alocado de Nome: %p", nome);
			printf("\nEndereco alocado do CPF: %p", cpf);
			
			printf("\nDados da pessoa: \nNome: %s\nCPF: %s\n", nome, cpf);
			
		}
		else if(op==2)
		{
			
			nome = alteraNome();
			
			printf("\nEndereco alocado de Nome: %p", nome);
			printf("\nEndereco alocado do CPF: %p", cpf);
			
			printf("\nDados da pessoa: \nNome: %s\nCPF: %s\n", nome, cpf);
		}
	}

	return 0;
}
