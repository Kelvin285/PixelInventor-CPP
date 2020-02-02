#pragma once
#include "Shader.h"
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
namespace PixelInventor {
    class SpriteRenderer
    {
    public:
        SpriteRenderer();
        SpriteRenderer(Shader& shader);
        ~SpriteRenderer();
        
        void DrawSprite(const unsigned int texture, const unsigned int temp, const unsigned int overlay, glm::vec2 position,
            glm::vec2 size, GLfloat rotate,
            glm::vec3 color, glm::vec4 uv, glm::vec4 tempUV, glm::vec4 overlayUV);
    private:
        Shader shader;
        GLuint quadVAO;

        void initRenderData();
    };
}