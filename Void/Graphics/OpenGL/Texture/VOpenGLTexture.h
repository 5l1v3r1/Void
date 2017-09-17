#pragma once
#ifndef _V_OPENGLTEXTURE_H_
#define _V_OPENGLTEXTURE_H_

#include "../../../VDefine.h"
#ifndef _VOID_DISABLE_OPENGL_
#include "../../Image/VImage.h"
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
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VOpenGLTextureData
    //----------------------------------------------------------------------------------------------------
    class VOpenGLTextureData
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VOpenGLTextureData()
            :
            texture(0)
        {
        }
        
        inline VOpenGLTextureData(const GLuint& _texture)
            :
            texture(_texture)
        {
        }
        
        virtual ~VOpenGLTextureData()
        {
            if (texture)
            {
                glDeleteTextures(1, &texture);
                texture = 0;
            }
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        GLuint texture;
    };
    
    // VOpenGLTexture
    //----------------------------------------------------------------------------------------------------
    class VOpenGLTexture : protected VSharePointer<VOpenGLTextureData>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        static GLenum TextureFormatForVColorFormat(VColorFormat _format);
        
    public:
        //----------------------------------------------------------------------------------------------------
        VOpenGLTexture();
        VOpenGLTexture(const VImage& _image, GLint _minMagFiler=GL_LINEAR, GLint _wrapMode=GL_CLAMP_TO_EDGE);
        VOpenGLTexture(const VOpenGLTexture& _texture);
        virtual ~VOpenGLTexture();
        
        //----------------------------------------------------------------------------------------------------
        GLuint Texture();
        bool SetTexture(const VImage& _image, GLint _minMagFiler=GL_LINEAR, GLint _wrapMode=GL_CLAMP_TO_EDGE);
    };
}

#endif
#endif
