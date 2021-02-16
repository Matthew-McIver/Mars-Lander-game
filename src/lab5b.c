/*
 *	A program to demonstrate strings
 *	C Programming laboratory 5
 */

#include <stdio.h>

/*
 * Program starts here
 */
int main(void)
{
	/* Declare a character array to store the string in */
	char string_data[20];

	/* Ask the user for a string */
	printf("Enter a word: ");
	scanf("%19s", string_data);

	/* Show them the string */
	printf("The word you entered is: %s\n", string_data);

	/* Tell them what the first character was */
	printf("The first character of the word is %c\n", string_data[0]);

	return 0;
}
