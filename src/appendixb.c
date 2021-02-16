/*
 * A Program to Demonstrate File Handling
 * appendixb
 */

#include <stdio.h>

int main(void)
{
	FILE* file_handle;
	int number;

	/* Ask the user for a number */
	printf("Please enter an integer number: ");
	scanf("%d", &number);

    /* Get access to the file by opening it */
    file_handle = fopen("number.txt", "w");

    /* Write a single number to the file */
    fprintf(file_handle, "%d", number);

	/* We're done with the file, close it */
	fclose(file_handle);

	return 0;
}
