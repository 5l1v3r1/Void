#include "VOpenGLProgram.h"
#include "../../Logger/VLogger.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::VOpenGLProgram()
        :
        VSmartPtr(nullptr)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::VOpenGLProgram(std::vector<VOpenGLShader>& _shaders)
        :
        VSmartPtr(nullptr)
    {
        GLuint program = glCreateProgram();
        if(program != 0)
        {
            for (int i = 0; i < _shaders.size(); ++i)
            {
                GLuint shader = _shaders[i].Shader();
                if (shader) { glAttachShader(program, shader); }
            }
            glLinkProgram(program);
            for (int i = 0; i < _shaders.size(); ++i)
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
                VSmartPtr::SetValue(new VOpenGLProgramData(program));
            }
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::VOpenGLProgram(const VOpenGLProgram& _program)
        :
        VSmartPtr(_program)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLProgram::~VOpenGLProgram()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLProgram::Program()
    {
        if (m_value)
        {
            return m_value->program;
        }
        return 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLProgram::Attrib(const GLchar* attribName)
    {
        if(!m_value || !attribName) { return -1; }
        
        GLint attrib = glGetAttribLocation(m_value->program, attribName);
        return attrib;
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLProgram::Uniform(const GLchar* uniformName)
    {
        if(!m_value || !uniformName) { return -1; }
        
        GLint uniform = glGetUniformLocation(m_value->program, uniformName);
        return uniform;
    }
}
