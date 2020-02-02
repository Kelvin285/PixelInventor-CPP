#include "Shader.h"
#include <iostream>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "FileManager.h"
#include "Shaders.h"
#include <glm/gtc/type_ptr.hpp>
namespace PixelInventor {
	void createShader(GLuint& shader, const char* filename, GLenum shaderType);
	const char* v;
	const char* f;

	GLuint vertShader;
	GLuint fragShader;
	GLuint program;

	Shader::Shader() {

	}

	Shader::Shader(const char* vert, const char* frag) {
		v = vert;
		f = frag;
		Shaders::addShader(this);
	}
	Shader::~Shader() {
		
	}

	void Shader::setMat4(const char* name, glm::mat4 mat) {
		unsigned int transformLoc = glGetUniformLocation(program, name);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(mat));
	}

	void Shader::setVec3f(const char* name, glm::vec3 model) {
		glUseProgram(program);
		glUniform3f(glGetUniformLocation(program, name), model.x, model.y, model.z);
	}

	void Shader::setVec4f(const char* name, glm::vec4 model) {
		glUseProgram(program);
		glUniform4f(glGetUniformLocation(program, name), model.x, model.y, model.z, model.w);
	}

	void Shader::setInt(const char* name, unsigned int i) {
		glUseProgram(program);
		glUniform1i(glGetUniformLocation(program, name), i);
	}

	void Shader::init() {
		std::cout << "INIT" << std::endl;
		createShader(vertShader, v, GL_VERTEX_SHADER);
		createShader(fragShader, f, GL_FRAGMENT_SHADER);

		program = glCreateProgram();
		if (program == 0) {
			std::cerr << "Error creating program object." << std::endl;
			exit(EXIT_FAILURE);
		}

		glAttachShader(program, vertShader);
		glAttachShader(program, fragShader);

		glLinkProgram(program);
		GLint status;
		glGetProgramiv(program, GL_LINK_STATUS, &status);
		if (status == GL_FALSE) {
			std::cerr << "Failed to link shader program!" << std::endl;
			GLint logLen;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0) {
				std::string log(logLen, ' ');
				GLsizei written;
				glGetProgramInfoLog(program, logLen, &written, &log[0]);
				std::cerr << "Program log: " << std::endl << log;
			}
		}
		else {
			glUseProgram(program);
		}
			

		glDetachShader(program, vertShader);
		glDetachShader(program, fragShader);
		glDeleteShader(vertShader);
		glDeleteShader(vertShader);

	}

	void Shader::bind() {
		glUseProgram(program);
	}

	void Shader::unbind() {
		glUseProgram(0);
	}

	void Shader::dispose() {
		glDeleteProgram(program);
	}

	void createShader(GLuint& shader, const char* filename, GLenum shaderType) {
		shader = glCreateShader(shaderType);
		if (shader == 0) {
			std::cerr << "Error creating vertex shader" << std::endl;
			exit(EXIT_FAILURE);
		}
		std::string shaderCode;
		shaderCode = FileManager::read(filename);
		const GLchar* codeArray[] = { shaderCode.c_str() };
		glShaderSource(shader, 1, codeArray, NULL);
		glCompileShader(shader);

		GLint result;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &result);
		if (result == GL_FALSE) {
			std::cerr << "Vertex shader compilation failed!" << std::endl;
			GLint logLen;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &logLen);
			if (logLen > 0) {
				std::string log(logLen, ' ');
				GLsizei written;
				glGetShaderInfoLog(shader, logLen, &written, &log[0]);
				std::cerr << "Shader log: " << std::endl << log;
			}
		}

	}
}