#include "VOpenGLShader.h"
#include "../../Logger/VLogger.h"
#include <string>
#include <fstream>
#include <sstream>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLShader
    //----------------------------------------------------------------------------------------------------
    VOpenGLShader::VOpenGLShader(const std::string& shader, GLenum shaderType, bool isFromFile)
        :
        VSmartPtr()
    {
        GLuint program = glCreateShader(shaderType);
        if(program != 0)
        {
            const char *code = nullptr;
            if (isFromFile)
            {
                std::ifstream fin(shader.c_str(), std::ios::in | std::ios::binary);
                if(fin.is_open())
                {
                    std::stringstream buffer;
                    buffer << fin.rdbuf();
                    code = buffer.str().c_str();
                    fin.close();
                }
            }
            else
            {
                code = shader.c_str();
            }
            if (!code) { return; }
            glShaderSource(program, 1, (const GLchar**)&code, nullptr);
            glCompileShader(program);
            
            GLint status;
            glGetShaderiv(program, GL_COMPILE_STATUS, &status);
            if (status == GL_FALSE)
            {
                GLint infoLogLength;
                glGetShaderiv(program, GL_INFO_LOG_LENGTH, &infoLogLength);
                char *strInfoLog = new char[infoLogLength + 1];
                glGetShaderInfoLog(program, infoLogLength, NULL, strInfoLog);
                VLogger::Info("Compile failure in shader\n%s", strInfoLog);
                delete[] strInfoLog;
                
                glDeleteShader(program);
                program = 0;
            }
            else
            {
                VSmartPtr::SetValue(new VOpenGLShaderData(program));
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
    GLuint VOpenGLShader::Program()
    {
        if (m_value)
        {
            return m_value->program;
        }
        return 0;
    }
}
