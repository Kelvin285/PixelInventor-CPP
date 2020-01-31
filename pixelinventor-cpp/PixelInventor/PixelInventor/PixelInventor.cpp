#include "PixelInventor.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
using namespace std;
namespace PixelInventor {

    PixelInventor* PixelInventor::GAME = nullptr;

	PixelInventor::PixelInventor() {
        GAME = this;
        
        start();
	}
	PixelInventor::~PixelInventor() {
        world.~World();
	}

	void PixelInventor::start() {
        GLFWwindow* window;

        /* Initialize the library */
        if (!glfwInit())
            std::exit(1);

       

        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(640, 480, "PixelInventor", NULL, NULL);
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
}