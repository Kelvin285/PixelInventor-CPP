#include "FPSCounter.h"

int FPSCounter::fps;
long FPSCounter::lastFPS;
nanoseconds FPSCounter::currentTime;
nanoseconds FPSCounter::lastTime;
double FPSCounter::delta;
long FPSCounter::totalGameTime = 0;
const long FPSCounter::MIN_DELTA = 1000000 / 20;

nanoseconds FPSCounter::getNanoseconds() {
	nanoseconds ms = duration_cast<nanoseconds>(
		system_clock::now().time_since_epoch()
		);
	return ms;
}

long FPSCounter::getTime() {
	return totalGameTime;
}

void FPSCounter::start() {
	lastFPS = getTime();
}

void FPSCounter::updateFPS() {
	if (getNanoseconds().count() / 1000000 - lastFPS > 1000) {
		//std::cout << fps << std::endl;
		fps = 0;
		lastFPS = getNanoseconds().count() / 1000000;
	}
	fps++;
}

void FPSCounter::startUpdate() {
	currentTime = getNanoseconds();
	delta = (max(currentTime.count() - lastTime.count(), MIN_DELTA) / getNanoseconds().count() / 1000000.0) / 20.0;
	if (delta < 1.5) delta = 1.5;
}

void FPSCounter::endUpdate() {
	lastTime = nanoseconds(currentTime.count());
	totalGameTime += delta;
}

double FPSCounter::getDelta() {
	return delta;
}

int FPSCounter::getFPS() {
	return fps;
}