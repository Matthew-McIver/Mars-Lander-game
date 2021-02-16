/*
 *	A simple program to demonstrate structures
 *	C Programming laboratory 6
 */

#include <stdio.h>



int main(void)
{
    /* Declare a template for a structure */
    struct student_type
    {
        char family_name[40];
        char given_name[40];
        int year_of_birth;
        int course_code;
    };

	/* Declare a variable which uses the structure template */
	struct student_type student;

	/* Ask the user to enter details for this student */
	printf("Please enter the student details\n\n");

	printf("Family name\t: ");
	scanf("%39s", student.family_name);

	printf("Given name\t: ");
	scanf("%39s", student.given_name);

	printf("Year of birth\t: ");
	scanf("%d", &student.year_of_birth);

	printf("Course code\t: ");
	scanf("%d", &student.course_code);

	/* Repeat the details back to the user */
	printf("\nThe student %s %s was born in %d and is registered on course %d\n\n",
		student.given_name, student.family_name, student.year_of_birth, student.course_code);

	return 0;
}
