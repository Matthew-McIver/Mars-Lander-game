/*
 *	A program to demonstrate arrays
 *	C Programming laboratory 5
 */

#include <stdio.h>

/* Function prototypes */
void welcome_message(void);
double mean(double values[], int num_values);

/*
 * Program starts here
 */
int main(void)
{
	/* Declare an array which can store up to 10 doubles */
	double data_values[10];

	/* Keep track of the number of items we have here */
	int num_data_values;

	/* Some other useful variables */
	int curr_data_value, done;
	double mean_height;

	/* Set initial conditions */
	num_data_values = 0;
	done = 0;

	/* Display message to user */
	welcome_message();

	/* Loop to get all data values, stop when we have 10 values */
	/* Or when the user enters a zero height */
	for (curr_data_value = 0; (curr_data_value < 10) && (done == 0); curr_data_value++)
	{
		/* Get the data into the array */
		printf("Please enter the height for person %d (or 0 if done): ", curr_data_value + 1);
		scanf("%lf", &data_values[curr_data_value]);

		/* If the data was non-zero we have another height */
		/* If not, we are done */
		if (data_values[curr_data_value] != 0)
			num_data_values++;
		else
			done = 1;
	}

	/* Calculate the mean height */
	mean_height = mean(data_values, num_data_values);

	/* Display it */
	printf("\nThe mean height is %lf\n", mean_height);

	return 0;
}

/*
 * Displays welcome message
 */
void welcome_message(void)
{
	printf("Mean Height Calculator\n");
	printf("Enter the height of each person when prompted\n");
	printf("Enter 0 when you are done. You can enter up to 10 values\n\n");
}

/*
 * Calculates the mean of a set of values
 */
double mean(double values[], int num_values)
{
	double mean;
	int current_value;

	/* Initialise the mean to zero */
	mean = 0;

	/* Calculate the sum of all of the values */
	for (current_value = 0; current_value < num_values; current_value++)
	{
		mean += values[current_value];
	}

	/* Divide by the number of values, if there are any */
	if (num_values > 0)
		mean /= num_values;

	return mean;
}
