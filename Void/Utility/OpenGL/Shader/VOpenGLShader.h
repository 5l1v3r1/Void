#pragma once
#ifndef _VOID_DISABLE_OPENGL_
#ifndef _V_OPENGLSHADER_H_
#define _V_OPENGLSHADER_H_
#include "../../../Memory/SmartPtr/VSmartPtr.h"
#define GLFW_INCLUDE_GLCOREARB
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
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
            program(0)
        {
        }
        
        inline VOpenGLShaderData(const GLuint& _program)
            :
            program(_program)
        {
        }
        
        virtual ~VOpenGLShaderData()
        {
            if (program)
            {
                glDeleteShader(program);
                program = 0;
            }
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        GLuint program;
    };
    
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    class VOpenGLShader : public VSmartPtr<VOpenGLShaderData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VOpenGLShader(const std::string& shader, GLenum shaderType, bool isFromFile=false);
        VOpenGLShader(const VOpenGLShader& _shader);
        virtual ~VOpenGLShader();
        
        //----------------------------------------------------------------------------------------------------
        GLuint Program();
    };
}

#endif
#endif
