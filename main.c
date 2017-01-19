#include <stdio.h>
#include <stdlib.h>
int* initdoors();
int opendoors(int*);

int main(int argc, char** argv) {
	int reps = 1, i = 0, limit, infinite = 0;
	double wins, fails;
	if(argc > 1) sscanf(argv[1], "%d", &limit);
	else limit = 1;
	if(limit == 0) infinite = 1;

	while(i != limit-1) {
		if(!infinite) ++i;

		if(opendoors(initdoors())) ++wins;
		else ++fails;
		
		system("clear");
		++reps;
		printf("Times complete: %d\nWins: %f (%f%%)\nFails: %f (%f%%)\n", reps, wins, (wins / reps) * 100, fails, (fails / reps) * 100);
	}

	putchar('\n');
	return 0;
}
