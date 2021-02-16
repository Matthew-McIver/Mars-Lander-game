/*
 *	A program to demonstrate multidimensional arrays
 *	C Programming laboratory 5
 */

#include <stdio.h>

/* Function prototype */
void display_options(void);

/*
 * Program starts here
 */
int main(void)
{
	/* You will need to declare a suitable 2D array here */

	/* These variable hold th indices of the start and */
	/* end cities of the journey */
	int start_city, end_city;

	/* Display travel options */
	display_options();

	/* Get the index of the starting city */
	printf("Enter the index of the city where you want to start: ");
	scanf("%d", &start_city);

	/* Get the index of the end city */
	printf("Enter the index of the city where you want to end: ");
	scanf("%d", &end_city);

	/* Lookup the distance in the array */

	/* Display the distance */

	return 0;
}

/*
 * Displays the city options
 */
void display_options(void)
{

	printf("Distance Calculator\n\n");
	printf("You will need to enter the indices of the cities you want\n");
	printf("to travel between from the following list\n\n");
	printf("[1] Cape Town\n");
	printf("[2] Hong Kong\n");
	printf("[3] London\n");
	printf("[4] New York\n");
	printf("[5] Rio de Janeiro\n");
	printf("[6] Tokyo\n\n");
}