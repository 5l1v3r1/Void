#pragma once
#ifndef _V_OPENGLSHADER_H_
#define _V_OPENGLSHADER_H_

#include "../../../VDefine.h"
#ifndef _VOID_DISABLE_OPENGL_
#include "../../../Memory/SmartPointer/VSmartPointer.h"
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#if defined(_WIN32) || defined(_WIN64)
#include <GL/glew.h>
#else
#define GLFW_INCLUDE_GLCOREARB
#endif
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLShaderData
    //----------------------------------------------------------------------------------------------------
    class VOpenGLShaderData
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VOpenGLShaderData()
            :
            shader(0)
        {
        }
        
        inline VOpenGLShaderData(const GLuint& _shader)
            :
            shader(_shader)
        {
        }
        
        virtual ~VOpenGLShaderData()
        {
            if (shader)
            {
                glDeleteShader(shader);
                shader = 0;
            }
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        GLuint shader;
    };
    
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    class VOpenGLShader : protected VSmartPointer<VOpenGLShaderData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VOpenGLShader(const std::string& _shader, GLenum _shaderType, bool _isFromFile=false);
        VOpenGLShader(const VOpenGLShader& _shader);
        virtual ~VOpenGLShader();
        
        //----------------------------------------------------------------------------------------------------
        GLuint Shader();
    };
}

#endif
#endif
