#include "GuiRenderer.h"
#include "Inignoto.h"

GuiRenderer::GuiRenderer() {

}

void GuiRenderer::init() {
	FP_CURSOR = createVBO("Inignoto:fp_cursor");
	Inignoto::game->addVBO(&FP_CURSOR);

	FP_CURSOR.scale = glm::vec3(32, 32, 1);
	FP_CURSOR.position = glm::vec3(50, 0.5f, 0);

	HOTBAR = createVBO("Inignoto:hotbar");
	Inignoto::game->addVBO(&HOTBAR);

	HOTBAR.scale = glm::vec3(382 * 3, 10 * 2, 1);
}

void GuiRenderer::render() {
	
}

VBO GuiRenderer::createVBO(std::string texture) {
	VBO vbo;
	TextureSpace* space = Textures::getSpaceFor(texture);
	if (space == nullptr) {
		std::cout << "Texture " << texture << " does not exist!" << std::endl;
	}
	std::array<glm::vec2, 4> texCoords = space->getTextureCoords(Textures::IMAGE_WIDTH, Textures::IMAGE_HEIGHT, 0, 0, 1, 1);
	std::vector<Vertex> vertices = {
		{{-1, -1, 0}, {1, 1, 1}, texCoords[2]}, {{-1, 1, 0}, {1, 1, 1}, texCoords[3]}, {{1, 1, 0}, {1, 1, 1}, texCoords[0]}, {{1, -1, 0}, {1, 1, 1}, texCoords[1]}
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

}