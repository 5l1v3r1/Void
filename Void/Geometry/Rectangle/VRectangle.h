#pragma once
#ifndef _V_RECTANGLE_H_
#define _V_RECTANGLE_H_
#include "../../Structure/Angle/VAngle.h"
#include "../../Structure/Vector/VVector.h"
#include "../../Utility/OpenGL/VOpenGL.h"
#include "../VGeometryBase.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VRectangle
    //----------------------------------------------------------------------------------------------------
    class VRectangle : public VGeometryBase
    {
    protected:
        //----------------------------------------------------------------------------------------------------
        static bool Initialize();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        static bool s_isInitialized;
        static VOpenGLProgram s_program;
        
    public:
        //----------------------------------------------------------------------------------------------------
        VRectangle();
        VRectangle(const VVector<float, 3>& _position, float _width, float _height);
        VRectangle(const VRectangle& _rectangle);
        virtual ~VRectangle();
        
        //----------------------------------------------------------------------------------------------------
        virtual bool Update();
        virtual bool Render();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool m_isRectangleDirty;
        VVector<float, 3> m_position;
        float m_width;
        float m_height;
        VVertexPosition m_rectangle[4];
        VSmartPtr<std::vector<VVertexTextureCoord>> m_textureCoord;
        
        std::vector<unsigned char> m_vertexData;
        VOpenGLTexture m_texture;
        GLuint m_vertexArray;
        GLuint m_vertexBuffer;
    };
}

#endif
