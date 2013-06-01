#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

bool random_if(int p) {
	//srand(time(NULL));
	int r = rand() % 100;
	//printf("Value of r:%d\n",r);
	return (r < p);
}
