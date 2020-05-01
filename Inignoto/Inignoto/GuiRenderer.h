#pragma once
#include "Utils.h"
#include <vector>
#include <set>
#include "glm/glm.hpp"
#include "VBO.h"
#include "Textures.h"
#include "GuiScreen.h"
#include "GLFW/glfw3.h"
#include "Mouse.h"

class GuiRenderer
{
public:
	GuiScreen* currentScreen = nullptr;
	GuiRenderer();
	void render();
	void closeScreen();
	GuiScreen* getOpenScreen();
	void openScreen(GuiScreen* screen);
	void init();
	int createVBO(std::string texture, int x, int y, int width, int height);
private:
	int FP_CURSOR;
	int HOTBAR;
	int VIGINETTE;
};

