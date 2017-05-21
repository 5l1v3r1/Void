#include "VOpenGLShader.h"
#ifndef _VOID_DISABLE_OPENGL_
#include "../../../Utility/Logger/VLogger.h"
#include <string>
#include <fstream>
#include <sstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    VOpenGLShader::VOpenGLShader(const std::string& _shader, GLenum _shaderType, bool _isFromFile)
        :
        VSmartPtr()
    {
        GLuint shader = glCreateShader(_shaderType);
        if(shader != 0)
        {
            const char *code = nullptr;
            if (_isFromFile)
            {
                std::ifstream fin(_shader.c_str(), std::ios::in);
                if(fin.is_open())
                {
                    std::stringstream buffer;
                    buffer << fin.rdbuf();
                    fin.close();
					std::string bufferString = buffer.str();
                    code = bufferString.c_str();
                    if (!code) { return; }
                    glShaderSource(shader, 1, (const GLchar**)&code, nullptr);
                    code = nullptr; // Wild pointer
                }
            }
            else
            {
                code = _shader.c_str();
                if (!code) { return; }
                glShaderSource(shader, 1, (const GLchar**)&code, nullptr);
            }
            glCompileShader(shader);
            
            GLint status;
            glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLogLength);
                char *strInfoLog = new char[infoLogLength + 1];
                glGetShaderInfoLog(shader, infoLogLength, NULL, strInfoLog);
                VLogger::Info("Compile failure in shader: %s", strInfoLog);
                delete[] strInfoLog;
                
                glDeleteShader(shader);
                shader = 0;
            }
            else
            {
                VSmartPtr::SetValue(new VOpenGLShaderData(shader));
            }
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLShader::VOpenGLShader(const VOpenGLShader& _shader)
        :
        VSmartPtr(_shader)
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VOpenGLShader::~VOpenGLShader()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    GLuint VOpenGLShader::Shader()
    {
        if (m_value)
        {
            return m_value->shader;
        }
        return 0;
    }
}

#endif
