/*
 * Takes the address to the doors as argument
 * returns 1 if the door was right
 * returns 0 if it wasn't
 */
#include <stdlib.h>

int opendoors(int* door) {
	//de1 and de2 contain door 0, df contains door 1.
	int de1 = 3, de2=3, df, i;
	for(i = 0; i < 3; ++i) {
		if(door[i]) df = 1;
		else {
			if(de1 == 3) de1 = i;
			else de2 = i;
		}

	}

	//pick a door and open one of the empty ones
	int pick = random() % 3;
	int opened;

	if(pick == de1) opened = de2;
	if(pick == de2) opened = de1;
	if(pick == df) opened = (random() % 2) ? de1 : de2;

	door[opened] = 2;
	door[pick] = 2;

	//find the door to open and return its value
	//if it's right, 1 will be returned
	//if it's wrong, 0 will be returned
	i = 0;
	while(door[i++] == 2);
	return door[i - 1];
}
