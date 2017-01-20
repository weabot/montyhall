#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

short int* initdoors();
int opendoors(short int*,int);
short int initflags(int argc, char** argv, char* optstring, int* limit);

int main(int argc, char** argv) {
	int reps = 0, i = 0, limit = 1;
	double wins, fails;

	//handle flags
	char* optstring = "v i c n:";
	short int flags = initflags(argc, argv, optstring, &limit);

	//set variables using initflags() results
	int vflag = flags & 1;
	int infinite = (flags >> 1) & 1; 
	int clear = (flags >> 2) & 1;

	while(i <= limit-1) {
		if(!infinite) ++i;
		++reps;
		if(clear) system("clear");
		else if(i != 1) putchar('\n');

		if(opendoors(initdoors(), vflag ? 1 : 0)) ++wins;
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
			case 'v': //make it verbose
				flagret |= 1;
				break;
			case 'i': //infinite loop
				flagret |= 1 << 1;
				break;
			case 'c':
				flagret |= 1 << 2;
				break;
			case 'n': //number of loops
				sscanf(optarg, "%d", limit);
				break;
			default:
				break;
		}
	}

	return flagret;
}
