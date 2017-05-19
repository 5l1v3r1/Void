#include "VRectangle.h"
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
    // VRectangle
    //----------------------------------------------------------------------------------------------------
    bool VRectangle::Initialize()
    {
        if (!s_isInitialized)
        {
            s_isInitialized = true;
            std::vector<VOpenGLShader> shaders;
            shaders.push_back(VOpenGLShader("Graphics/Geometry/Rectangle/Shader/VVertex.glsl", GL_VERTEX_SHADER, true));
            shaders.push_back(VOpenGLShader("Graphics/Geometry/Rectangle/Shader/VFragment.glsl", GL_FRAGMENT_SHADER, true));
            s_program = VOpenGLProgram(shaders);
            return true;
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VRectangle::s_isInitialized(false);
    VOpenGLProgram VRectangle::s_program;
    
    //----------------------------------------------------------------------------------------------------
    VRectangle::VRectangle()
        :
        m_vertexArray(0),
        m_vertexBuffer(0)
    {
        VRectangle::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VRectangle::VRectangle(const VVector<float, 3>& _position, float _width, float _height)
        :
        m_position(_position),
        m_width(_width),
        m_height(_height)
    {
        VRectangle::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VRectangle::VRectangle(const VRectangle& _points)
    {
        VRectangle::Initialize();
    }
    
    //----------------------------------------------------------------------------------------------------
    VRectangle::~VRectangle()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VRectangle::Update()
    {
        if (m_isRectangleDirty == true || m_vertexArray == 0 || m_vertexBuffer == 0)
        {
            m_isRectangleDirty = false;
            
            glGenVertexArrays(1, &m_vertexArray);
            glBindVertexArray(m_vertexArray);
            glGenBuffers(1, &m_vertexBuffer);
            glBindBuffer(GL_ARRAY_BUFFER, m_vertexBuffer);
            
            size_t vertexSize = 0;
            size_t bufferSize = 0;
            m_vertexData.clear();
            
            // Position
            float halfWidth = m_width / 2;
            float halfHeight = m_height / 2;
            m_rectangle[0].postion = VVector<float, 3>(m_position.x + halfWidth, m_position.y - halfHeight, m_position.z);
            m_rectangle[1].postion = VVector<float, 3>(m_position.x - halfWidth, m_position.y - halfHeight, m_position.z);
            m_rectangle[2].postion = VVector<float, 3>(m_position.x + halfWidth, m_position.y + halfHeight, m_position.z);
            m_rectangle[3].postion = VVector<float, 3>(m_position.x - halfWidth, m_position.y + halfHeight, m_position.z);
            GLuint position = s_program.Attrib("position");
            glEnableVertexAttribArray(position);
            glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, (GLsizei)sizeof(VVertexPosition), (const GLvoid*)bufferSize);
            vertexSize += sizeof(VVertexPosition);
            bufferSize += sizeof(VVertexPosition) * 4;
            m_vertexData.insert(m_vertexData.end(), (unsigned char*)m_rectangle, (unsigned char*)(m_rectangle + 4));
            
            // TextureCoord
            m_textureCoord.SetValue(new std::vector<VVertexTextureCoord>(4));
            (*m_textureCoord)[0].textureCoord = VVector<float, 2>(1.f, 1.f);
            (*m_textureCoord)[1].textureCoord = VVector<float, 2>(0.f, 1.f);
            (*m_textureCoord)[2].textureCoord = VVector<float, 2>(1.f, 0.f);
            (*m_textureCoord)[3].textureCoord = VVector<float, 2>(0.f, 0.f);
            GLuint textureCoord = s_program.Attrib("textureCoord");
            glEnableVertexAttribArray(textureCoord);
            glVertexAttribPointer(textureCoord, 2, GL_FLOAT, GL_TRUE, (GLsizei)sizeof(VVertexTextureCoord), (const GLvoid*)bufferSize);
            vertexSize += sizeof(VVertexTextureCoord);
            bufferSize += sizeof(VVertexTextureCoord) * m_textureCoord->size();
            m_vertexData.insert(m_vertexData.end(), (unsigned char*)(*m_textureCoord).data(), (unsigned char*)((*m_textureCoord).data() + 4));
            
            // Image
            if (m_image.Data())
            {
                m_texture.SetTexture(m_image);
            }
            
            glBufferData(GL_ARRAY_BUFFER, m_vertexData.size(), m_vertexData.data(), GL_STATIC_DRAW);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glBindVertexArray(0);
        }
        
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VRectangle::Render()
    {
        glUseProgram(s_program.Program());
        glBindVertexArray(m_vertexArray);
        s_program.BindUniform("projection", m_camera.Projection());
        if (m_color)
        {
            s_program.BindUniform("color", *m_color);
        }
        if (m_texture.Texture())
        {
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, m_texture.Texture());
            s_program.BindUniform("image", VVector<int, 1>(0));
        }
        
        // Draw
        glDrawArrays(GL_TRIANGLE_STRIP, 0, (GLsizei)4);
        
        glBindVertexArray(0);
        glUseProgram(0);
        return true;
    }
}
