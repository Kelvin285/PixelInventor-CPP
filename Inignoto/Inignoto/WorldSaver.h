#pragma once
#include <string>
class World;
class WorldSaver
{
public:
	WorldSaver(std::string worldname = "", World* world = nullptr, long seed = 0);

	void saveWorld();
	std::string getWorldName();
	World* getWorld();
	long getSeed();
private:
	std::string worldName;
	World* world;
	long seed;
};

