#pragma once
#ifndef _V_COMMITMENTSCHEME_H_
#define _V_COMMITMENTSCHEME_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VCommitmentScheme
    //----------------------------------------------------------------------------------------------------
    class VCommitmentScheme
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VCommitmentScheme();
        VCommitmentScheme(const VCommitmentScheme& _commitment);
        virtual ~VCommitmentScheme();
        
        //----------------------------------------------------------------------------------------------------
        
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VCommitmentSchemeTest();
}

#endif
