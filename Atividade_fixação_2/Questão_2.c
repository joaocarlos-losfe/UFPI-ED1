//por João Carlos de Sousa Fé. 01/04/2021

#include <stdio.h>
#include <stdlib.h>

void altera1(int *a)
{
	*a = *a + 50;
}

void altera2(int *p)
{
	*p = *p + 300;
}

int main(int argc, char** argv)
{
	int *px = (int*) malloc(sizeof(int));
	int *py = (int*) malloc(sizeof(int));
	
	*px = 500;
	*py = *px + 200;
	
	printf("x = %d, End. x = %p, px = %p, y = %d \n", *px, px, px, *py);
	*px = *py;
	altera1(py);
	printf("x = %d, End. x = %p, px = %p, y = %d \n\n", *px, px, px, *py);
	
	printf("y = %d, End. y = %p, py = %p, x = %d \n", *py, py, py, *px);
		
	altera2(px);
	
	printf("y = %d, End. y = %p, py = %p, x = %d \n", *py, py, py, *px);
	
	return 0;
}