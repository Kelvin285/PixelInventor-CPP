#pragma once
#include "Shader.h"
#include "ArrayList.h"
namespace PixelInventor {
	class Shaders {
	public:
		static Shader DEFAULT;
		static void addShader(Shader* shader);
		static void dispose();
		static void init();
	private:
		static ArrayList<Shader> shaders;
	};
}