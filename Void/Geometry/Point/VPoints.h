#pragma once
#ifndef _V_POINTS_H_
#define _V_POINTS_H_
#include "../../Structure/Vector/VVector.h"
#include "../../Utility/OpenGL/VOpenGL.h"
#include "../VGeometryBase.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VPointVertex
    //----------------------------------------------------------------------------------------------------
    struct VPointVertex : public VVector<float, 3>
    {
    };
    
    // VPoints
    //----------------------------------------------------------------------------------------------------
    class VPoints : public VGeometryBase
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
        VPoints();
        VPoints(const VPoints& _points);
        virtual ~VPoints();
        
        //----------------------------------------------------------------------------------------------------
        virtual bool Update();
        virtual bool Render();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool m_isPointsDirty;
        std::vector<VPointVertex> m_points;
        
        GLuint m_vertexArray;
        GLuint m_vertexBuffer;
    };
}

#endif
