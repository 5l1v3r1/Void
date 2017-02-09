#pragma once
#ifndef _V_TRIANGLE_H_
#define _V_TRIANGLE_H_
#include "../../Structure/Vector/VVector.h"
#include "../../Utility/OpenGL/VOpenGL.h"
#include "../VGeometryBase.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VTriangleVertex
    //----------------------------------------------------------------------------------------------------
    struct VTriangleVertex : public VVector<float, 3>
    {
    };
    
    // VTriangle
    //----------------------------------------------------------------------------------------------------
    class VTriangle : public VGeometryBase
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
        VTriangle();
        VTriangle(const VTriangle& _triangle);
        virtual ~VTriangle();
        
        //----------------------------------------------------------------------------------------------------
        virtual bool Update();
        virtual bool Render();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool m_isTriangleDirty;
        VVertexPosition m_rectangle[3];
        
        std::vector<unsigned char> m_vertexData;
        GLuint m_vertexArray;
        GLuint m_vertexBuffer;
    };

}

#endif
