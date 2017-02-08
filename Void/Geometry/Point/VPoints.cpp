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
        if (m_isPointsDirty == true || m_vertexArray == 0 || m_vertexBuffer == 0)
        {
            m_isPointsDirty = false;
            
            glGenVertexArrays(1, &m_vertexArray);
            glBindVertexArray(m_vertexArray);
            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            glBufferData(GL_ARRAY_BUFFER, sizeof(VPointVertex) * m_points.size(), m_points.data(), GL_STATIC_DRAW);
            
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
        s_program.BindUniform("projection", m_camera.Projection());
        if (m_color)
        {
            s_program.BindUniform("color", *m_color);
        }
        
        // Draw
        glDrawArrays(GL_POINTS, 0, (GLsizei)m_points.size());
        
        glBindVertexArray(0);
        glUseProgram(0);
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VPoints::AddPoint(const VPointVertex& _point)
    {
        m_points.push_back(_point);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VPoints::AddPoints(const std::vector<VPointVertex>& _points)
    {
        m_points.insert(m_points.end(), _points.begin(), _points.end());
    }
    
    
    // x = a * cost, y = b * sint
    //----------------------------------------------------------------------------------------------------
    std::vector<VPointVertex> VPointsEllipse(const VVector<float, 2>& _position, float _a, float _b, float _start, float _end)
    {
        float delta = V_ANGLE_PI / 360.f;
        std::vector<VPointVertex> result;
        while (_start <= _end)
        {
            VVector<float, 2> position = _position + VVector<float, 2>(_a * cos(_start), _b * sin(_start));
            result.push_back(VPointVertex(position[0], position[1], 0));
            _start += delta;
        }
        
        return result;
    }
}
