#pragma once
#include "GuiScreen.h"
class IngameMenuScreen :
	public GuiScreen
{
public:
	const static int ID = 1;
	IngameMenuScreen(GuiRenderer* renderer);
	void tick();
	void render();
	void close();
};

