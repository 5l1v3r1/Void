#include "VPoints.h"
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
    // VPoint
    //----------------------------------------------------------------------------------------------------
    bool VPoints::Initialize()
    {
        if (!s_isInitialized)
        {
            s_isInitialized = true;
            std::vector<VOpenGLShader> shaders;
            shaders.push_back(VOpenGLShader("Geometry/Point/Shader/VVertex.glsl", GL_VERTEX_SHADER, true));
            shaders.push_back(VOpenGLShader("Geometry/Point/Shader/VFragment.glsl", GL_FRAGMENT_SHADER, true));
            s_program = VOpenGLProgram(shaders);
            return true;
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VPoints::s_isInitialized(false);
    VOpenGLProgram VPoints::s_program;
    
    //----------------------------------------------------------------------------------------------------
    VPoints::VPoints()
        :
        m_vertexArray(0),
        m_vertexBuffer(0)
    {
        VPoints::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VPoints::VPoints(const VPoints& _points)
    {
        VPoints::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VPoints::~VPoints()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VPoints::Update()
    {
        if (m_vertexArray == 0 || m_vertexBuffer == 0)
        {
            const GLfloat vertexBufferData[] =
            {
                0.0f, 0.9f, 0.0f,
                -0.9f, -0.9f, 0.0f,
                0.9f, -0.9f, 0.0f,
            };
            
            glGenVertexArrays(1, &m_vertexArray);
            glBindVertexArray(m_vertexArray);
            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertexBufferData), vertexBufferData, GL_STATIC_DRAW);
            
            GLuint position = s_program.Attrib("position");
            glEnableVertexAttribArray(position);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
            
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VPoints::Render()
    {
        glUseProgram(s_program.Program());
        glBindVertexArray(m_vertexArray);
        
        // Draw
        glDrawArrays(GL_POINTS, 0, 3);
        
        glBindVertexArray(0);
        glUseProgram(0);
        return true;
    }
}
