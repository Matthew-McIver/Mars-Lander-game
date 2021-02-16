/*
 *	A program to demonstrate simple mathematical operations
 *	C Programming laboratory 1
 */

/*
 * The main function - the program starts executing here
 */
int main(void)
{
	/* Declare some variables for the calculations */
	int distance_to_tokyo, distance_to_airport;
	int speed_of_plane, speed_of_car;
	int time_to_fly, time_to_drive, time_to_tokyo;
	int average_speed;

	/* Set the values of some of the variables */

	/* Set distances in kilometres */
	distance_to_tokyo = 9720;
	distance_to_airport = 120;

	/* Set speeds in kilometres per hour */
	speed_of_plane = 1200;
	speed_of_car = 100;

	/* Calculate time taken to get to Tokyo */

	time_to_fly = (distance_to_tokyo - distance_to_airport) / speed_of_plane;

	time_to_drive = distance_to_airport / speed_of_car;

	time_to_tokyo = time_to_fly + time_to_drive;

	/* Calculate the average speed */

	average_speed = distance_to_tokyo / time_to_tokyo;

	return 0;
}





