#include "InventoryScreen.h"
#include "GuiRenderer.h"
#include "Inignoto.h"

InventoryScreen::InventoryScreen(GuiRenderer* renderer) {
	this->renderer = renderer;
	inventory = renderer->createVBO("Inignoto:inventory", 1920 / 2.0 - 264 * 1.5, 1080 / 2.0 - 108 * 1.5, 264 * 3, 108 * 3);

	Inignoto::game->addVBO(&inventory);
}

void InventoryScreen::tick() {

}

void InventoryScreen::render() {

}

void InventoryScreen::close() {
	Inignoto::game->removeVBO(&inventory);
}
