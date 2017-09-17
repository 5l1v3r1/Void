#include "VOpenGLProgram.h"
#ifndef _VOID_DISABLE_OPENGL_
#include "../../../Utility/Logger/VLogger.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::VOpenGLProgram()
        :
        VSharePointer(nullptr)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::VOpenGLProgram(std::vector<VOpenGLShader>& _shaders)
        :
        VSharePointer(nullptr)
    {
        GLuint program = glCreateProgram();
        if(program != 0)
        {
            for (unsigned int i = 0; i < _shaders.size(); ++i)
            {
                GLuint shader = _shaders[i].Shader();
                if (shader) { glAttachShader(program, shader); }
            }
            glLinkProgram(program);
            for (unsigned int i = 0; i < _shaders.size(); ++i)
            {
                GLuint shader = _shaders[i].Shader();
                if (shader) { glDetachShader(program, shader); }
            }
            
            GLint status;
            glGetProgramiv(program, GL_LINK_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
                char *strInfoLog = new char[infoLogLength + 1];
                glGetProgramInfoLog(program, infoLogLength, NULL, strInfoLog);
                VLogger::Info("Program linking failure: %s", strInfoLog);
                delete[] strInfoLog;
                
                glDeleteProgram(program);
                program = 0;
            }
            else
            {
                VSharePointer::SetValue(new VOpenGLProgramData(program));
            }
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::VOpenGLProgram(const VOpenGLProgram& _program)
        :
        VSharePointer(_program)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::~VOpenGLProgram()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLProgram::Program()
    {
        if (mValue)
        {
            return mValue->program;
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLProgram::Attrib(const GLchar* attribName)
    {
        if(!mValue || !attribName) { return -1; }
        
        GLint attrib = glGetAttribLocation(mValue->program, attribName);
        return attrib;
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLProgram::Uniform(const GLchar* uniformName)
    {
        if(!mValue || !uniformName) { return -1; }
        
        GLint uniform = glGetUniformLocation(mValue->program, uniformName);
        return uniform;
    }
}

#endif
