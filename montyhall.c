#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

short int* initdoors();
int opendoors(short int*,int);
short int initflags(int argc, char** argv, char* optstring, int* limit);

int main(int argc, char** argv) {
	int reps = 0, i = 0, limit = 1;
	double wins, fails;

	// handle flags
	char* optstring = "v i c n:";
	short int flags = initflags(argc, argv, optstring, &limit);

	// set variables using initflags() results
	int vflag = flags & 1;
	int infinite = (flags >> 1) & 1; 
	int clear = (flags >> 2) & 1;

	while (i <= limit - 1) {
		if (!infinite) ++i;
		++reps;
		if (clear) system("clear");
		else if (i != 1) putchar('\n');

		if (opendoors(initdoors(), vflag ? 1 : 0)) ++wins;
		else ++fails;
		
		printf("Times complete: %d\nWins: %.0f (%3.2f%%)\nFails: %.0f (%3.2f%%)\n", reps, wins, (wins / reps) * 100, fails, (fails / reps) * 100);
	}

	return 0;
}

short int initflags(int argc, char** argv, char* optstring, int *limit) {
	int opt;
	short int flagret = 0;
	extern char* optarg;

	while((opt = getopt(argc, argv, optstring)) != EOF) {
		switch(opt) {
			case 'v': // verbose
				flagret |= 1;
				break;
			case 'i': // infinite loop
				flagret |= 1 << 1;
				break;
			case 'c':
				flagret |= 1 << 2;
				break;
			case 'n': // number of loops
				sscanf(optarg, "%d", limit);
				break;
			default:
				break;
		}
	}

	return flagret;
}

/*
 * returns an array of 3 ints
 * puts a 1 behind 1 door at random
 * puts 0's behind the 2 other doors
 */
short int* initdoors() {
	static short int door[3];
	int i;
	door[0] = door[1] = door[2] = 0;
	door[random() % 3] = 1;
	return door;
}

/*
 * Takes the address to the doors as argument
 * returns 1 if the door was right
 * returns 0 if it wasn't
 */
int opendoors(short int* door, int vflag) {
	// de1 and de2 contain door 0, df contains door 1.
	int de1 = 3, de2=3, df, i;
	for (i = 0; i < 3; ++i) {
		if(door[i]) df = 1;
		else {
			if(de1 == 3) de1 = i;
			else de2 = i;
		}

	}

	// pick a door and open one of the empty ones
	int pick = random() % 3;
	int opened;

	if (pick == de1) opened = de2;
	if (pick == de2) opened = de1;
	if (pick == df) opened = (random() % 2) ? de1 : de2;

	door[opened] = 2;
	door[pick] = 2;

	// find the door to open and return its value
	// if it's right, 1 will be returned
	// if it's wrong, 0 will be returned
	i = 0;
	while (door[i++] == 2);
	if (vflag) {
		printf("Participant first chose door %d\nShow host opened door %d, revealing nothing\nParticipant changed his mind and picked door %d\nThe right door was door %d\n", pick, opened, i-1, df);
		if(door[i-1]) printf("Participant won.");
		else printf("Participant lost.");
		putchar('\n');
		putchar('\n');
	}
	return door[i - 1];
}
