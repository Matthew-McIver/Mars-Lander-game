/*
 *	A program to demonstrate the use of the while statement
 *	C Programming laboratory 3
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

	/* Display all the numbers from the one entered */
	/* up to (and including) the number 10 */
	while (number_entered <= 10)
	{
		printf("%d\n", number_entered);
		number_entered = number_entered + 1;
	}

	return 0;
}