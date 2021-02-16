/*
 *	A program to demonstrate the use of the scanf function
 *	C Programming laboratory 2
 */

/*  This line allows the compiler to understand both the
 *	printf and scanf functions
 */
#include <stdio.h>

int main(void)
{
	/* Declare a variable to store an integer number */
	int number_entered;

	/* Output some text to the user */
	printf("Enter an integer number: ");

	/* Wait for the user to enter a number and hit enter */
	/* Store the number in the number_entered variable */
	scanf("%d", &number_entered);

	/* Display the number that the user entered */
	printf("The number you entered was %d\n", number_entered);

	return 0;
}
