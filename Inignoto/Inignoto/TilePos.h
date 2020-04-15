#pragma once
#include <string>
#include <corecrt_math.h>

class TilePos
{
public:
	int x, y, z;
	TilePos(int x, int y, int z);

	TilePos(double x, double y, double z);

	void setPosition(int x, int y, int z);

	void setPosition(double x, double y, double z);

	TilePos add(int i, int j, int k);

	TilePos add(double i, double j, double k);

	std::string toString();
};

