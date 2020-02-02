#pragma once
#include <glm/glm.hpp>
namespace PixelInventor {
	class Shader {
	public:
		Shader();
		Shader(const char* vert, const char* frag);
		~Shader();
		void bind();
		void unbind();
		void dispose();
		void init();
	
		void setMat4(const char* name, glm::mat4 model);
		void setVec3f(const char* name, glm::vec3 model);
		void setVec4f(const char* name, glm::vec4 model);
		void setInt(const char* name, unsigned int i);
	};
}