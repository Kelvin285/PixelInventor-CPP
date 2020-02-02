#include "Shaders.h"
#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "FileManager.h"

namespace PixelInventor {
	ArrayList<Shader> Shaders::shaders;
	Shader Shaders::DEFAULT("res/pixelinventor/shaders/basic.vert.glsl", "res/pixelinventor/shaders/basic.frag.glsl");

	void Shaders::init() {
		for (unsigned int i = 0; i < shaders.size(); i++) {
			shaders.get(i).init();
		}
	}

	void Shaders::dispose() {
		for (unsigned int i = 0; i < shaders.size(); i++) {
			shaders.get(i).dispose();
		}
		shaders.clear();
	}

	void Shaders::addShader(Shader* shader) {
		shaders.add(*shader);
	}

}