#include "Mouse.h"

float Mouse::x;
float Mouse::y;
float Mouse::lastX;
float Mouse::lastY;
bool Mouse::locked = false;

void Mouse::update() {
	lastX = x;
	lastY = y;
}