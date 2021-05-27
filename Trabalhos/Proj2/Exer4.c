#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define TRUE  1;
#define FALSE 0;

const int MAXCOLS = 80;

typedef struct PILHA
{
	char   valor;
	struct PILHA *next;
	
} pilha;

pilha *topo;

void inicializa()
{
	topo = (struct PILHA *) malloc(sizeof(struct PILHA));
	topo->next = NULL ;
}

void insira(char v)
{
	struct PILHA *novo = (struct PILHA *) malloc(sizeof(struct PILHA));
	novo->valor = v;
	novo->next = topo->next;
	topo->next = novo;
}

int ehPilhaVazia()
{
	int saida = FALSE;
	if (topo->next == NULL) saida = TRUE;
	return saida;
}

char retire()
{
	if (topo->next == NULL)
	{
		return 27;
	}
	else
	{
		struct PILHA *novo = (struct PILHA *) malloc(sizeof(struct PILHA));
		novo = topo->next;
		topo = topo->next;
		return novo->valor;
	}
}

int ehOperador(char s)
{
	int saida = FALSE;
	if (
		(s == '+') || (s == '*') || (s == '/') || (s == '-') || (s == '$')
		|| (s == ')') || (s == '(')
	)
		saida = TRUE;
	return saida;
}

char quemEstahNoTopo()
{
	if (topo->next == NULL)
	{
		return 27;
	}
	else
	{
		struct PILHA *novo = (struct PILHA *) malloc(sizeof(struct PILHA));
		novo = topo->next;
		return novo->valor;
	}
}

int precedencia(char op1, char op2)
{
	int saida = FALSE;
	if  ( ((op1 == '*') || (op1 == '/') || (op1 == '$'))
			&& (op2 != '$')) saida = TRUE;
	if (op1 == op2) saida = TRUE;
	if (op2 == 27) saida = TRUE;
	if (op1 == '(') saida = TRUE;
	return saida;
}
void inToPosFix(char infix[MAXCOLS], char postr[MAXCOLS])
{
	int pos = 0;
	char v;
	char _v = '\0';
	int i = 0;
	for (i = 0; i < strlen(infix); i++)
	{
		if  (ehOperador(infix[i]))
		{
			/***/
			if (infix[i] != ')')
			{
				if (precedencia(infix[i], quemEstahNoTopo()))
				{
					insira(infix[i]);
					if (!( postr[pos - 1] == ' ')) postr[pos++] = ' ';
				}
				else
				{
					v = retire();
					if ( (v != ')') && (v != '(') )
					{
						if (!( postr[pos - 1] == ' ')) postr[pos++] = ' ';
						postr[pos++] = v;
					}
					insira(infix[i]);
				}
			}
			else
			{
				v = retire();
				if ( (v != ')') && (v != '(') )
				{
					if (!( postr[pos - 1] == ' ')) postr[pos++] = ' ';
					postr[pos++] = v;
				}
				v = retire();
				if (v != '(') insira(v);
			}
		}/***/
		else
		{
			if ((infix[i] == ' ') && ( postr[pos - 1] == ' ')) {}
			else
			{
				if (!( postr[pos - 1] == ' ')) postr[pos++] = ' ';
				postr[pos++] = infix[i];
			}
		}
	}

////////////////////////////////////////////////////////
	while (!ehPilhaVazia())
	{
		v = retire();
		if ( (v != ')') && (v != '(') && (v != 27))
		{
			if (!( postr[pos - 1] == ' ')) postr[pos++] = ' ';
			postr[pos++] = v;
		}
	}
	postr[pos] = '\0';
}

int main()
{
	char infix[MAXCOLS];
	char postr[MAXCOLS];
	int pos = 0;
	inicializa();

	printf("\nDigite expressao INFIXA conversao POSFIXA:>");
	while ((infix[pos++] = getchar()) != '\n');
	infix[--pos] = '\0';
	inToPosFix(infix, postr);
	printf("\na expressao infixa original eh: %s", infix);
	printf("\na expressao posfixa eh: %s", postr);
}


//Sugestao de expressoes :
//   ((1 - ( 2+3)) * 4)$(5 + 6)  => 1 2 3 + - 4 * 5 6 + $
//   (1+2) * 3                   => 1 2 + 3 *
//   1+(2*3 + 4
