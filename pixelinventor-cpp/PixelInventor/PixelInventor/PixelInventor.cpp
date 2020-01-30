#include "PixelInventor.h"
#include "Settings.h"
#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

using namespace std;
namespace PixelInventor {

    PixelInventor* PixelInventor::GAME = nullptr;

	PixelInventor::PixelInventor() {
        GAME = this;
        
        start();
	}
	PixelInventor::~PixelInventor() {
		
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
        
        std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
        
        
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

    }
}