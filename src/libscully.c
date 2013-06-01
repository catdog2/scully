#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

bool random_if(int p) {
	srand(time(NULL));
	int r = rand() % 100;

	return (r < p);
}
