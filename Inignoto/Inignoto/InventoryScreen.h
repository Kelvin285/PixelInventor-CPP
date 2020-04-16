#pragma once
#include "GuiScreen.h"
#include "VBO.h"
#include "glm/glm.hpp"
class InventoryScreen :
	public GuiScreen
{

public:
	const static int ID = 0;

	InventoryScreen(GuiRenderer* renderer);

	void tick() override;
	void render() override;
	void close() override;
private:
	VBO inventory;
};

