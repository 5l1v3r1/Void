#pragma once
#ifndef _VOID_DISABLE_OPENGL_
#ifndef _V_OPENGLTEXTURE_H_
#define _V_OPENGLTEXTURE_H_
#include "../../../Graphics/Image/VImage.h"
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
    class VOpenGLTexture : protected VSmartPtr<VOpenGLTextureData>
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
