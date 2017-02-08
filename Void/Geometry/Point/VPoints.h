#pragma once
#ifndef _V_POINTS_H_
#define _V_POINTS_H_
#include "../../Structure/Angle/VAngle.h"
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
        inline VPointVertex(float _x, float _y=0, float _z=0)
            :
            VVector(_x, _y, _z)
        {
        }
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
        
        //----------------------------------------------------------------------------------------------------
        void AddPoint(const VPointVertex& _point);
        void AddPoints(const std::vector<VPointVertex>& _points);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool m_isPointsDirty;
        std::vector<VPointVertex> m_points;
        
        GLuint m_vertexArray;
        GLuint m_vertexBuffer;
    };
    
    //----------------------------------------------------------------------------------------------------
    std::vector<VPointVertex> VPointsEllipse(const VVector<float, 2>& _position, float _a, float _b, float _start=0.f, float _end=V_ANGLE_2PI);
}

#endif
