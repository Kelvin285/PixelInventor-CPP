#include "SeededRandom.h"

SeededRandom::SeededRandom(time_t seed)
{
	this->seed = seed;
}

int SeededRandom::nextInt(int i) {
	srand(seed);
	return rand() % i;
}
