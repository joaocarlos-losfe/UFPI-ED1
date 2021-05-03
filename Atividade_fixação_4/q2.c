#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int string_em_numero(char *str, int len_str)
{
	if(len_str == 1)
	{
		return *str - '0';
	}
	
	return (10 * string_em_numero(str, len_str - 1) + str[len_str-1] - '0');
}

int main(int argc, char** argv)
{
	char string[15];
	printf("\nEntre com a string numerica: ");
	scanf("%14[^\n]s", string);
	
	int str_numero = string_em_numero(string, strlen(string));
	
	printf("\nstring em numero: %d", str_numero);
	
	return 0;
}