/* The scully programming language.
 *
 * Copyright (c) Peter Dahlberg, Markus Hauschild and Florian Sattler, 2013.
 * Licensed under the GNU GPL v2.
 */

#include <time.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
int put_char(int c) {
	printf("%c", c);
	return 0;
}

bool random_if(int p) {
	//srand(time(NULL));
	int r = rand() % 100;
	return (r < p);
}

int time_seed() {
	srand(time(NULL));
	return 0;
}
