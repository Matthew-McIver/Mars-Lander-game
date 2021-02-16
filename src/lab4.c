/*
 *	A program to demonstrate function creation
 *	C Programming laboratory 4
 */

#include <stdio.h>

/*
 * display_welcome function - displays a welcome message
 *
 * The display_welcome function takes no parameters and
 * does not return anything.
 */
void display_welcome(void)
{
	printf("Welcome to the squaring numbers program\n\n");
}

/*
 * square function - squares an integer number
 *
 * The square function takes a single integer
 * parameter.  It returns an integer which is the square
 * of the value of the parameter it was given.
 */
int square(int value)
{
	int squared_value;

	squared_value = value * value;

	return squared_value;
}

/*
 * The main function - the program starts executing here
 *
 * The main function takes no parameters and returns an
 * integer.
 */
int main(void)
{
	int num_placeholders_matched;
	int number_entered, squared_number;

	/* Call the display_welcome function */
	/* This will display a welcome message */
	display_welcome();

	/* Obtain a number from the user */
	printf("Please enter an integer number: ");

	/* Loop for as long as the user gives us values */
	/* that aren't integers */
	do
	{
		/* Call scanf and use the return value to find out */
		/* how many placeholders were matched */
		num_placeholders_matched = scanf("%d", &number_entered);

		/* The integer placeholder was not matched */
		if (num_placeholders_matched < 1)
		{
			/* Clear out whatever the user typed */
			fflush(stdin);

			/* Tell the user to try again, loop will go again */
			printf("That was not an integer. Please try again: ");
		}
	}
	while (num_placeholders_matched < 1);

	/* Square the number using the square function */
	squared_number = square(number_entered);

	/* Display the result */
	printf("%d squared is %d\n", number_entered, squared_number);

	return 0;
}
