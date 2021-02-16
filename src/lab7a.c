/*
 *	A program to demonstrate pointer operators
 *	C Programming laboratory 7
 */

#include <stdio.h>

int main(void)
{
    int my_integer;
    int *ref_my_integer;

    ref_my_integer = &my_integer;

    my_integer = 20;
    printf("my_integer is %d\n", my_integer);

    *ref_my_integer = 5;
    printf("my_integer is now %d\n", my_integer);

    return 0;
}
