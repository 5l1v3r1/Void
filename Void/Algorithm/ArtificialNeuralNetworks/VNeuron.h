#pragma once
#ifndef _V_NEURON_H_
#define _V_NEURON_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"
#include <map>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSynapse
    //----------------------------------------------------------------------------------------------------
    struct VSynapseCore;
    typedef VSharePointer<VSynapseCore> VSynapse;
    
    // VNeuron
    //----------------------------------------------------------------------------------------------------
    class VNeuronCore;
    typedef VSharePointer<VNeuronCore> VNeuron;
    typedef VWeakPointer<VNeuronCore> VNeuronWeak;
    
    // VNeuronCore
    // Process: (synapse) -> stimulate -> add stimulus -> activate -> transmit -> (synapse)
    //----------------------------------------------------------------------------------------------------
    class VNeuronCore
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VNeuronCore();
        VNeuronCore(const VNeuronCore& _core);
        virtual ~VNeuronCore();
        
        //----------------------------------------------------------------------------------------------------
        double Stimulus();
        void AddDendrite(VSynapse _dendrite);
        void AddAxon(VSynapse _axon);
        bool RemoveDendrite(VNeuronWeak _dendrite);
        bool RemoveAxon(VNeuron _axon);
        void Stimulate(double _transmitters);
        bool Clear();
        void DeepClear();
        
        //----------------------------------------------------------------------------------------------------
        virtual double Activate();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::map<VNeuronWeak, VSynapse> mDendrites; // Inputs
        std::map<VNeuron, VSynapse> mAxons; // Outputs
        double mLearningRate;
        double mStimulus;
        bool mIsNeuronDirty;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VNeuronTest();
}

#endif
