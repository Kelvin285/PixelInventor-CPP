#include "WorldSaver.h"

WorldSaver::WorldSaver(std::string worldname, World* world, long seed) {
	this->worldName = worldname;
	this->world = world;
	this->seed = seed;
}

void WorldSaver::saveWorld() {

}

std::string WorldSaver::getWorldName() {
	return this->worldName;
}

World* WorldSaver::getWorld() {
	return this->world;
}

long WorldSaver::getSeed() {
	return this->seed;
}