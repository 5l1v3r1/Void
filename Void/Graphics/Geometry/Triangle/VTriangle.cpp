#include "VTriangle.h"
#ifndef _VOID_DISABLE_OPENGL_
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#if defined(_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop
#endif
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTriangle
    //----------------------------------------------------------------------------------------------------
    bool VTriangle::Initialize()
    {
        if (!s_isInitialized)
        {
            s_isInitialized = true;
            std::vector<VOpenGLShader> shaders;
            shaders.push_back(VOpenGLShader("Graphics/Geometry/Triangle/Shader/VVertex.glsl", GL_VERTEX_SHADER, true));
            shaders.push_back(VOpenGLShader("Graphics/Geometry/Triangle/Shader/VFragment.glsl", GL_FRAGMENT_SHADER, true));
            s_program = VOpenGLProgram(shaders);
            return true;
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VTriangle::s_isInitialized(false);
    VOpenGLProgram VTriangle::s_program;
    
    //----------------------------------------------------------------------------------------------------
    VTriangle::VTriangle()
    :
    m_vertexArray(0),
    m_vertexBuffer(0)
    {
        VTriangle::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VTriangle::VTriangle(const VTriangle& _triangle)
    {
        VTriangle::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VTriangle::~VTriangle()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VTriangle::Update()
    {
        if (m_vertexArray == 0 || m_vertexBuffer == 0)
        {
            const GLfloat vertexBufferData[] =
            {
                0.0f, 0.2f, 0.0f,
                -0.2f, -0.2f, 0.0f,
                0.2f, -0.2f, 0.0f,
            };
            
            glGenVertexArrays(1, &m_vertexArray);
            glBindVertexArray(m_vertexArray);
            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
            
            GLuint position = s_program.Attrib("position");
            glEnableVertexAttribArray(position);
            glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, sizeof(VTriangleVertex), (const GLvoid*)0);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VTriangle::Render()
    {
        glUseProgram(s_program.Program());
        glBindVertexArray(m_vertexArray);
        s_program.BindUniform("projection", m_camera.Projection());
        if (m_color)
        {
            s_program.BindUniform("color", *m_color);
        }
        
        // Draw
        glDrawArrays(GL_TRIANGLES, 0, 3);
        
        glBindVertexArray(0);
        glUseProgram(0);
        return true;
    }
}
