#include "VWindow.h"
#include "../../Utility/Logger/VLogger.h"
#ifndef _VOID_DISABLE_OPENGL_
#define GLFW_INCLUDE_GLCOREARB
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop
#endif

//----------------------------------------------------------------------------------------------------
namespace Void
{
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VWindowTest()
    {
        #ifndef _VOID_DISABLE_OPENGL_
        GLFWwindow *window;
        glfwSetErrorCallback([](int error, const char* description)
                             {
                                 VLogger::Info("code %d", error);
                                 VLogger::Info("%s", description);
                             });
        if (!glfwInit()) { return; }
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        window = glfwCreateWindow(640, 480, "Void Test", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return;
        }
        
        glfwMakeContextCurrent(window);
        glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
                           {
                               if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) { glfwSetWindowShouldClose(window, GL_TRUE); }
                           });
        glfwSwapInterval(1);
        while (!glfwWindowShouldClose(window))
        {
            float ratio;
            int width, height;
            glfwGetFramebufferSize(window, &width, &height);
            ratio = width / (float) height;
            glViewport(0, 0, width, height);
            glClear(GL_COLOR_BUFFER_BIT);
            
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            glDrawArrays(GL_TRIANGLES, 0, 3);
            glFlush();
            
            glfwSwapBuffers(window);
            glfwPollEvents();
        }
        
        glfwDestroyWindow(window);
        glfwTerminate();
        #endif
    }
}
