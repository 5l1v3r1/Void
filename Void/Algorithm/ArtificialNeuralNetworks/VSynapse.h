#pragma once
#ifndef _V_SYNAPSE_H_
#define _V_SYNAPSE_H_

#include "../../Memory/SmartPointer/VSmartPointer.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VNeuron
    //----------------------------------------------------------------------------------------------------
    class VNeuronCore;
    typedef VSharePointer<VNeuronCore> VNeuron;
    typedef VWeakPointer<VNeuronCore> VNeuronWeak;
    
    // VSynapseCore
    // Process: (neuron) -> transmit -> weight && bias -> stimulate -> (neuron)
    // Option: synapse matrix
    //----------------------------------------------------------------------------------------------------
    struct VSynapseCore
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VSynapseCore();
        VSynapseCore(VNeuronWeak _source, double _weight, VNeuronWeak _target);
        virtual ~VSynapseCore();
        
        //----------------------------------------------------------------------------------------------------
         virtual void Transmit(double _activity);
        
    public:
        //----------------------------------------------------------------------------------------------------
        VNeuronWeak source;
        double weight;
        double bias;
        VNeuronWeak target;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSynapseTest();
}

#endif
