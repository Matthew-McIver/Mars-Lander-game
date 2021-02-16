/*
 *	A program to demonstrate passing by value
 *	C Programming laboratory 7
 */

#include <stdio.h>

void change(int i)
{
	printf("The number is now %d\n", i);
	
	i = 20;

	printf("The number is now %d\n", i);
}

int main(void)
{
	int j;

	j = 5;

	printf("The number is %d\n", j);

	change(j);

	printf("The number is now %d\n", j);

	return 0;
}