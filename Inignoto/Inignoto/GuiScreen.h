#pragma once

class GuiRenderer;
class GuiScreen
{
protected:
	GuiRenderer* renderer;
public:
	GuiScreen() {};

	const static int ID = 0;
	virtual void tick() {};
	virtual void render() {};
	virtual void close() {};
};

