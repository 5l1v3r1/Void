#pragma once
#ifndef _VOID_DISABLE_OPENGL_
#ifndef _V_OPENGLPROGRAM_H_
#define _V_OPENGLPROGRAM_H_
#include "../Shader/VOpenGLShader.h"
#include "../../../Memory/SmartPtr/VSmartPtr.h"
#define GLFW_INCLUDE_GLCOREARB
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdocumentation"
#include <GLFW/glfw3.h>
#pragma clang diagnostic pop
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLProgramData
    //----------------------------------------------------------------------------------------------------
    class VOpenGLProgramData
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VOpenGLProgramData()
            :
            program(0)
        {
        }
        
        inline VOpenGLProgramData(const GLuint& _program)
            :
            program(_program)
        {
        }
        
        virtual ~VOpenGLProgramData()
        {
            if (program)
            {
                glDeleteProgram(program);
                program = 0;
            }
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        GLuint program;
    };
    
    // VOpenGLProgram
    //----------------------------------------------------------------------------------------------------
    class VOpenGLProgram : public VSmartPtr<VOpenGLProgramData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VOpenGLProgram();
        VOpenGLProgram(std::vector<VOpenGLShader>& _shaders);
        VOpenGLProgram(const VOpenGLProgram& _program);
        virtual ~VOpenGLProgram();
        
        //----------------------------------------------------------------------------------------------------
        GLuint Program();
        GLuint Attrib(const GLchar* attribName);
        GLuint Uniform(const GLchar* uniformName);
    };
}

#endif
#endif
