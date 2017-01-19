/*
 * returns an array of 3 ints
 * puts a 1 behind 1 door at random
 * puts 0's behind the 2 other doors
 */

#include <stdlib.h>

int* initdoors() {
	static int door[3];
	int i;
	door[0] = door[1] = door[2] = 0;
	door[random() % 3] = 1;
	return door;
}
