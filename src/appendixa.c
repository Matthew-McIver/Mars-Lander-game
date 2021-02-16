/*
 *	A program to demonstrate the use of the #define directive
 *	C Programming laboratory appendixa
 */

/*  These lines allow the compiler to understand the
 *	printf and getch functions
 */
#include <stdio.h>
#include <conio.h>

/* An example use of the #define directive */
/* The preprocessor will replace HELLO_STRING, */
/* wherever it appears, with "Hello, World!\n" */
#define HELLO_MESSAGE "Hello, World!\n"

/* A numeric example, wherever PI appears */
/* it will be replaced by 3.14159265 */
#define PI 3.14159265

int main(void)
{
	/* Print a message to the screen */
	printf(HELLO_MESSAGE);

	/* Display pi */
	printf("Pi = %lf (roughly)\n", PI);

	/* Wait for a key press */
	getch();

	return 0;
}
