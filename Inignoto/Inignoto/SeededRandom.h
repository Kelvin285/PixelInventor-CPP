#pragma once

#include <stdlib.h>
#include <time.h>
class SeededRandom {
private:
	time_t seed;
public:
	SeededRandom(time_t seed = time(NULL));

	int nextInt(int i);
};