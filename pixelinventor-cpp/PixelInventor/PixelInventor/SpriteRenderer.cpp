#include "SpriteRenderer.h"
#include "glm/gtc/matrix_transform.hpp"
#include <glm/glm.hpp>
#include <iostream>
namespace PixelInventor {
    SpriteRenderer::SpriteRenderer() {

    }
	SpriteRenderer::SpriteRenderer(Shader& shader) {
		this->shader = shader;
        this->initRenderData();
	}

	SpriteRenderer::~SpriteRenderer() {
		shader.dispose();
        glDeleteVertexArrays(1, &this->quadVAO);
	}

	void SpriteRenderer::DrawSprite(const unsigned int texture, const unsigned int temp, const unsigned int overlay, glm::vec2 position,
		glm::vec2 size, GLfloat rotate,
		glm::vec3 color, glm::vec4 uv, glm::vec4 tempUV, glm::vec4 overlayUV) {
        // Prepare transformations
        this->shader.bind();
        glm::mat4 model = glm::mat4();
        model[0][0] = 1;
        model[1][1] = 1;
        model[2][2] = 1;
        model[3][3] = 1;
        model = glm::translate(model, glm::vec3(position, 0));
        //model = glm::rotate(model, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));

        model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
        model = glm::rotate(model, rotate, glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

        model = glm::scale(model, glm::vec3(size, 1.0f));
        this->shader.setMat4("model", model);
        this->shader.setVec3f("spriteColor", color);
        this->shader.setVec4f("uv", uv);
        this->shader.setVec4f("overlayUv", overlayUV);
        this->shader.setVec4f("tempUv", tempUV);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);
        glActiveTexture(GL_TEXTURE1);
        glBindTexture(GL_TEXTURE_2D, temp);
        glActiveTexture(GL_TEXTURE2);
        glBindTexture(GL_TEXTURE_2D, overlay);
        
        glBindVertexArray(this->quadVAO);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);
	}

	void SpriteRenderer::initRenderData() {
        // Configure VAO/VBO
        GLuint VBO;
        GLfloat vertices[] = {
            // Pos      // Tex
           0.0f, 0.0f, 0.0f, 0.0f,
           0.0f, 1.0f, 0.0f, 1.0f,
           1.0f, 1.0f, 1.0f, 1.0f,
           
           1.0f, 1.0f, 1.0f, 1.0f,
           1.0f, 0.0f, 1.0f, 0.0f,
           0.0f, 0.0f, 0.0f, 0.0f
        };

        glGenVertexArrays(1, &this->quadVAO);
        glGenBuffers(1, &VBO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindVertexArray(this->quadVAO);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);
	}
}