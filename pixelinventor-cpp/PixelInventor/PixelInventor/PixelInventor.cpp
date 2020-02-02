#include "PixelInventor.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Shaders.h"
#include "Textures.h"
#include "Constants.h"
#include "Settings.h"
#include "SpriteRenderer.h"
using namespace std;
namespace PixelInventor {
    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
    GLFWwindow* window;

	PixelInventor::PixelInventor() {       
        start();
	}
	PixelInventor::~PixelInventor() {
        world.~World();
        Shaders::dispose();
        Textures::dispose();
        delete Constants::spriteRenderer;
	}

    void PixelInventor::initGL() {
        Textures::load();
        Shaders::init();
        glm::mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH, (float)SCREEN_HEIGHT, 0.0f, -1.0f, 1.0f);
        Shaders::DEFAULT.setMat4("projection", projection);
        Shaders::DEFAULT.setInt("uTex", 0);
        Shaders::DEFAULT.setInt("templateTex", 1);
        Shaders::DEFAULT.setInt("overlay", 2);
        Constants::spriteRenderer = new SpriteRenderer(Shaders::DEFAULT);
        glfwSetKeyCallback(window, key_callback);
    }
	void PixelInventor::start() {
        
        
        /* Initialize the library */
        if (!glfwInit())
            std::exit(1);

       

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "PixelInventor", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            std::exit(1);
        }

        /* Make the window's context current */
        glfwMakeContextCurrent(window);

        if (glewInit() != GLEW_OK)
            std::cout << "Error in initializing glew!" << std::endl;
        
        const GLubyte* renderer = glGetString(GL_RENDERER);
        const GLubyte* vendor = glGetString(GL_VENDOR);
        const GLubyte* version = glGetString(GL_VERSION);
        const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);
        GLint major, minor;
        glGetIntegerv(GL_MAJOR_VERSION, &major);
        glGetIntegerv(GL_MINOR_VERSION, &minor);
        GLint nExtensions;
        glGetIntegerv(GL_EXTENSIONS, &nExtensions);

        printf("GL Vendor    : %s\n", vendor);
        printf("GL Renderer  : %s\n", renderer);
        printf("GL Version (string)  : %s\n", version);
        printf("GL Version (integer)  : %d.%d\n", major, minor);
        printf("GLSL Version  : %s\n", glslVersion);
        //for (int i = 0; i < nExtensions; i++)
        //    printf("%s\n", glGetStringi(GL_EXTENSIONS, i));
        
        initGL();

        /* Loop until the user closes the window */
        while (!glfwWindowShouldClose(window))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);

            /* Swap front and back buffers */

            update();
            render();
            glfwSwapBuffers(window);
            
            /* Poll for and process events */
            glfwPollEvents();
        }

        glfwTerminate();
	}

    void PixelInventor::update() {
        world.update();
    }

    void PixelInventor::render() {

        int width, height;
        glfwGetWindowSize(window, &width, &height);
        
        glm::mat4 projection = glm::ortho(0.0f, (float)SCREEN_WIDTH * (float)((float)SCREEN_WIDTH / (float)width), 0.0f, (float)SCREEN_HEIGHT * (float)((float)SCREEN_HEIGHT / (float)height), -1.0f, 1.0f);
        Shaders::DEFAULT.setMat4("projection", projection);
        static int i = 0;
        static double x = 0;
        i++;
        if (i % Settings::frameSkip != 0) return;

        glClear(GL_COLOR_BUFFER_BIT);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glLoadIdentity();
        
        //begin drawing
        world.render();
    }

    void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        if (action == GLFW_PRESS) {
            Settings::buttons[key] = true;
        }
        if (action == GLFW_RELEASE) {
            Settings::buttons[key] = false;
        }
    }
}