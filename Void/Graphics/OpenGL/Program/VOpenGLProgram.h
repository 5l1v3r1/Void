#pragma once
#ifndef _V_OPENGLPROGRAM_H_
#define _V_OPENGLPROGRAM_H_

#include "../../../VDefine.h"
#ifndef _VOID_DISABLE_OPENGL_
#include "../../../Structure/Vector/VVector.h"
#include "../../../Structure/Matrix/VMatrix.h"
#include "../Shader/VOpenGLShader.h"
#include "../../../Memory/SmartPtr/VSmartPtr.h"
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
    class VOpenGLProgram : protected VSmartPtr<VOpenGLProgramData>
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
        
        //----------------------------------------------------------------------------------------------------
        template <size_t _S>
        bool BindUniform(const GLchar* uniformName, const VVector<int, _S>& _vector)
        {
            switch (_S)
            {
                case 1:
                    glUniform1i(Uniform(uniformName), _vector[0]);
                    return true;
                case 2:
                    glUniform2i(Uniform(uniformName), _vector[0], _vector[1]);
                    return true;
                case 3:
                    glUniform3i(Uniform(uniformName), _vector[0], _vector[1], _vector[2]);
                    return true;
                case 4:
                    glUniform4i(Uniform(uniformName), _vector[0], _vector[1], _vector[2], _vector[3]);
                    return true;
            }
            return false;
        }
        
        template <size_t _S>
        bool BindUniform(const GLchar* uniformName, const VVector<float, _S>& _vector)
        {
            switch (_S)
            {
                case 1:
                    glUniform1f(Uniform(uniformName), _vector[0]);
                    return true;
                case 2:
                    glUniform2f(Uniform(uniformName), _vector[0], _vector[1]);
                    return true;
                case 3:
                    glUniform3f(Uniform(uniformName), _vector[0], _vector[1], _vector[2]);
                    return true;
                case 4:
                    glUniform4f(Uniform(uniformName), _vector[0], _vector[1], _vector[2], _vector[3]);
                    return true;
            }
            return false;
        }
        
        template <size_t _S>
        bool BindUniform(const GLchar* uniformName, const VMatrix<float, _S, _S>& _matrix)
        {
            switch (_S)
            {
                case 2:
                    glUniformMatrix2fv(Uniform(uniformName), 1, GL_FALSE,  (const GLfloat*)&_matrix);
                    return true;
                case 3:
                    glUniformMatrix3fv(Uniform(uniformName), 1, GL_FALSE,  (const GLfloat*)&_matrix);
                    return true;
                case 4:
                    glUniformMatrix4fv(Uniform(uniformName), 1, GL_FALSE,  (const GLfloat*)&_matrix);
                    return true;
            }
            return false;
        }
    };
}

#endif
#endif
