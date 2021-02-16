/*
 *	A program to demonstrate memory allocation
 *	C Programming laboratory 8
 */

#include <stdlib.h>
#include <stdio.h>

int main(void)
{
	/* Declare a pointer we will use as an array */
	int *my_array;
	int i;

	/* Allocate memory for the array */
	my_array = malloc(sizeof(int) * 4);

	/* Check to see if malloc gave us the memory we asked for */
	if (my_array == NULL)
	{
		printf("There was an error: insufficient memory available\n");
		return 0;
	}

	/* This is only an example: use the array in some way */
	for (i = 0; i < 4; i++)
	{
		my_array[i] = (i + 1) * (i + 1);
	}

	for (i = 0; i < 4; i++)
	{
		printf("my_array[%d] = %d\n", i, my_array[i]);
	}

	/* We have finished with the array, free the memory */
	free(my_array);

	return 0;
}
