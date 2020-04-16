#include "GuiRenderer.h"
#include "Inignoto.h"

GuiRenderer::GuiRenderer() {

}

void GuiRenderer::init() {
	FP_CURSOR = createVBO("Inignoto:fp_cursor", 1920 / 2.0 - 16, 1080 / 2.0 - 16, 32, 32);
	Inignoto::game->addVBO(&FP_CURSOR);

	HOTBAR = createVBO("Inignoto:hotbar", 1920 / 2.0 - 382 * 1.5, 0, 382 * 3.0, 35 * 3.0);
	Inignoto::game->addVBO(&HOTBAR);
	
}

void GuiRenderer::render() {
	if (currentScreen != nullptr) {
		glfwSetInputMode(Utils::window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		Mouse::locked = false;
		currentScreen->tick();
		currentScreen->render();
	}
}

VBO GuiRenderer::createVBO(std::string texture, int x, int y, int width, int height) {
	VBO vbo;
	TextureSpace* space = Textures::getSpaceFor(texture);
	if (space == nullptr) {
		std::cout << "Texture " << texture << " does not exist!" << std::endl;
	}
	std::array<glm::vec2, 4> texCoords = space->getTextureCoords(Textures::IMAGE_WIDTH, Textures::IMAGE_HEIGHT, 0, 0, 1, 1);

	std::vector<glm::vec2> verts;
	verts.resize(4);
	verts[0] = { x, y };
	verts[1] = { x, y + height };
	verts[2] = { x + width, y + height };
	verts[3] = { x + width, y };

	for (size_t i = 0; i < 4; i++) {
		verts[i].x *= 2.0;
		verts[i].y *= 2.0;
		verts[i].x -= 1920;
		verts[i].y -= 1080;
		verts[i] /= glm::vec2(1920, 1080);
	}


	std::vector<Vertex> vertices = {
		{glm::vec3(verts[0], 0.0) , {1, 1, 1}, texCoords[2]}, {glm::vec3(verts[1], 0.0), {1, 1, 1}, texCoords[3]}, {glm::vec3(verts[2], 0.0), {1, 1, 1}, texCoords[0]}, {glm::vec3(verts[3], 0.0), {1, 1, 1}, texCoords[1]}
	};
	
	std::vector<uint32_t> indices = {
	0, 1, 2, 2, 3, 0
	};

	vbo.vertices = vertices;
	vbo.indices = indices;
	vbo.orthographic = true;
	vbo.createVertexBuffer();
	vbo.created = true;
	return vbo;
}

void GuiRenderer::closeScreen() {
	if (currentScreen != nullptr) {
		currentScreen->close();
		currentScreen = nullptr;
		glfwSetInputMode(Utils::window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		Mouse::locked = true;
		FP_CURSOR.visible = true;
	}
}

void GuiRenderer::openScreen(GuiScreen* screen) {
	if (screen == nullptr) return;
	closeScreen();
	currentScreen = screen;
	FP_CURSOR.visible = false;
}

GuiScreen* GuiRenderer::getOpenScreen() {
	return currentScreen;
}