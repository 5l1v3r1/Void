#pragma once
#ifndef _V_NEURALNETWORKS_H_
#define _V_NEURALNETWORKS_H_

#include "./VSynapse.h"
#include "./VNeuron.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VNeuralNetworks
    //----------------------------------------------------------------------------------------------------
    class VNeuralNetworks
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VNeuralNetworks();
        VNeuralNetworks(const VNeuralNetworks& _networks);
        virtual ~VNeuralNetworks();
        
        //----------------------------------------------------------------------------------------------------
        bool Generate(const unsigned long& _inputLevel, const std::vector<const unsigned long>& _neuronLevel, const unsigned long& _outputLevel);
        std::vector<float> Stimulate(const std::vector<double>& _inputs);
        
        // Learning
        //----------------------------------------------------------------------------------------------------
        bool BPTrain(const std::vector<double>& _inputs, const std::vector<double>& _outputs); // Back Propagation
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<VNeuron> mInputs;
        std::vector<VNeuron> mOutputs;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VNeuralNetworksTest();
}

#endif
