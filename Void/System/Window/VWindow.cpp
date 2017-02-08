#include "VWindow.h"
#include "../../Utility/Logger/VLogger.h"
#include "../../Geometry/VGeometry.h"
#include "../../Camera/VCamera.h"
#ifndef _VOID_DISABLE_OPENGL_
#define GLFW_INCLUDE_GLCOREARB
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop
#endif
#include <iostream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VWindow
    //----------------------------------------------------------------------------------------------------
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VWindowTest()
    {
        #ifndef _VOID_DISABLE_OPENGL_
        GLFWwindow *window;
        glfwSetErrorCallback([](int error, const char* description)
                             {
                                 VLogger::Info("Error code %d, %s", error, description);
                             });
        if (!glfwInit()) { return; }
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
        glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
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
        VLogger::Info("OpenGL version: %s", glGetString(GL_VERSION));
        VLogger::Info("GLSL version: %s", glGetString(GL_SHADING_LANGUAGE_VERSION));
        VLogger::Info("Vendor: %s", glGetString(GL_VENDOR));
        VLogger::Info("Renderer: %s", glGetString(GL_RENDERER));
        
        VCamera camera;
        camera.SetOrthogonaLens(640.f, 480.f, 0, 100.f, false);
        VPoints points;
        points.SetCamera(camera);
        points.SetColor(VColor<>(1.f, 1.f, 1.f, 1.f));
        points.AddPoint(VPointVertex(100, 200, 0));
        points.AddPoints(VPointsEllipse(VVector<float, 2>(100.f, 200.f), 100.f, 50.f));
        VTriangle triangle;
        triangle.SetColor(VColor<>(0.5, 0.5, 1.0, 1.0));
        VRectangle rectangle(VVector<float, 3>(300.f, 200.f, 0), 100.f, 100.f);
        rectangle.SetCamera(camera);
        rectangle.SetColor(VColor<>(1.f, 1.f, 1.f, 1.f));
        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClearColor(0, 0, 0, 1); // Black
            glClear(GL_COLOR_BUFFER_BIT);
            
            points.Process();
            //triangle.Process();
            rectangle.Process();
            
            glfwSwapBuffers(window);
        }
        
        glfwDestroyWindow(window);
        glfwTerminate();
        #endif
    }
}
