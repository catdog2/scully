#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

int put_char(int c) {
	printf("%c", c);
	return 0;
}

bool random_if(int p) {
	//srand(time(NULL));
	int r = rand() % 100;
	return (r < p);
}
