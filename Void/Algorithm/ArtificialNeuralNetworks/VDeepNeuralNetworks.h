#pragma once
#ifndef _V_DEEPNEURALNETWORKS_H_
#define _V_DEEPNEURALNETWORKS_H_

#include "./VSynapse.h"
#include "./VNeuron.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDeepNeuralNetworks
    //----------------------------------------------------------------------------------------------------
    //           Input                     Hidden                           Output
    //----------------------------------------------------------------------------------------------------
    // Inputs -> Neuron -> | Full     | -> Neuron -> | Full     | -> ... -> Neuron
    //        -> Neuron -> | Synapses | -> Neuron -> | Synapses | -> ... -> Neuron
    //        -> Neuron -> |          | -> Neuron -> |          | -> ... -> Neuron
    //        ...                       ...                       ...    ...
    //----------------------------------------------------------------------------------------------------
    class VDeepNeuralNetworks
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VDeepNeuralNetworks();
        virtual ~VDeepNeuralNetworks();
        
    public:
        //----------------------------------------------------------------------------------------------------
        bool Generate(const unsigned long& _inputLevel, const std::vector<const unsigned long>& _hiddenLevels, const unsigned long& _outputLevel);
        std::vector<double> Stimulate(const std::vector<double>& _inputs);
        
        // Learning
        //----------------------------------------------------------------------------------------------------
        bool BPTrain(const std::vector<double>& _inputs, const std::vector<double>& _outputs); // Back Propagation
        
    protected:
        //----------------------------------------------------------------------------------------------------
        bool Link(VNeuron _source, double _weight, VNeuron _target);
        bool Unlink(VNeuron _source, VNeuron _target);
        void ClearStimulus();
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<VNeuron> mInputs;
        std::vector<std::vector<VNeuron>> mHiddenLevels;
        std::vector<VNeuron> mOutputs;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDeepNeuralNetworksTest();
}

#endif
