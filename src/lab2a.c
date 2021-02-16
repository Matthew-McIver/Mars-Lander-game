/*
 *	A program to demonstrate the use of the switch statement
 *	C Programming laboratory 2
 */

#include <stdio.h>

int main(void)
{
	/* Declare a variable to store an integer number */
	int number_entered;

	/* Output some text to the user */
	printf("Enter an integer number between 1 and 9: ");

	/* Wait for the user to enter a number and hit enter */
	/* Store the number in the number_entered variable */
	scanf("%d", &number_entered);

	/* Display the number that the user entered */
	/* But display it as English text */
	printf("The number you entered was ");

	/* This switch statement decides between lots of options */
	switch (number_entered)
	{
	case 1:
		printf("one\n");
		break;

	case 2:
		printf("two\n");
		break;

	case 3:
		printf("three\n");
		break;

	case 4:
		printf("four\n");
		break;

	case 5:
		printf("five\n");
		break;

	case 6:
		printf("six\n");
		break;

	case 7:
		printf("seven\n");
		break;

	case 8:
		printf("eight\n");
		break;

	case 9:
		printf("nine\n");
		break;

	default:
		printf("not between one and nine\n");
	}

	return 0;
}