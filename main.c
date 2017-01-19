#include <stdio.h>
#include <stdlib.h>

int* initdoors();
int opendoors(int*);

int main(int argc, char** argv) {
	int reps = 0, i = 0, infinite = 0, limit;
	double wins, fails;

	//scans the first argument and sets the limit to it or to 1 if no argument was given
	if(argc > 1) sscanf(argv[1], "%d", &limit);
	else limit = 1;

	//sets up the infinite loop
	if(limit == 0) {
		infinite = 1;
		limit=1;
	}

	while(i <= limit-1) {
		if(!infinite) ++i;
		++reps;

		if(opendoors(initdoors())) ++wins;
		else ++fails;
		
		system("clear");
		printf("Times complete: %d\nWins: %.0f (%3.2f%%)\nFails: %.0f (%3.2f%%)\n", reps, wins, (wins / reps) * 100, fails, (fails / reps) * 100);
	}

	return 0;
}
