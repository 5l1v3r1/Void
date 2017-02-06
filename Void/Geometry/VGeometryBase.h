#pragma once
#ifndef _V_GEOMETRYBASE_H_
#define _V_GEOMETRYBASE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VGeometryBase
    //----------------------------------------------------------------------------------------------------
    class VGeometryBase
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VGeometryBase();
        VGeometryBase(const VGeometryBase& _geometry);
        virtual ~VGeometryBase();
        
        virtual bool Update() = 0;
        virtual bool Render() = 0;
        virtual bool Process();
    };
}

#endif
