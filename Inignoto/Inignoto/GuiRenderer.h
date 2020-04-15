#pragma once
#include "Utils.h"
#include <vector>
#include <set>
#include "glm/glm.hpp"
#include "VBO.h"
#include "Textures.h"

class GuiRenderer
{
public:
	GuiRenderer();
	void render();
	void closeScreen();
	void init();
private:
	VBO createVBO(std::string texture);
	VBO FP_CURSOR;
	VBO HOTBAR;
};

