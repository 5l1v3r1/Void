#include "VDeepNeuralNetworks.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDeepNeuralNetworks
    //----------------------------------------------------------------------------------------------------
    VDeepNeuralNetworks::VDeepNeuralNetworks()
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    VDeepNeuralNetworks::~VDeepNeuralNetworks()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDeepNeuralNetworks::Generate(const unsigned long& _inputLevel, const std::vector<const unsigned long>& _hiddenLevels, const unsigned long& _outputLevel)
    {
        // Input
        mInputs.clear();
        mInputs.reserve(_inputLevel);
        for (unsigned long i = 0; i < _inputLevel; ++i)
        {
            mInputs.push_back(new VNeuronCore());
        }
        
        // Hidden
        std::vector<VNeuron> lowerLevel = mInputs;
        std::vector<VNeuron> higherLevel;
        for (auto level : _hiddenLevels)
        {
            higherLevel.reserve(level);
            for (unsigned long i = 0; i < level; ++i)
            {
                VNeuron newNeuron(new VNeuronCore());
                double weight = 1.0 / lowerLevel.size(); // Todo: random
                for (auto neuron : lowerLevel)
                {
                    Link(neuron, weight, newNeuron);
                }
                higherLevel.push_back(newNeuron);
            }
            std::swap(lowerLevel, higherLevel);
            higherLevel.clear();
            mHiddenLevels.push_back(lowerLevel);
        }
        
        // Output
        mOutputs.clear();
        mOutputs.reserve(_outputLevel);
        for (unsigned long i = 0; i < _outputLevel; ++i)
        {
            VNeuron newNeuron(new VNeuronCore());
            double weight = 1.0 / lowerLevel.size();
            for (auto neuron : lowerLevel)
            {
                Link(neuron, weight, newNeuron);
            }
            mOutputs.push_back(newNeuron);
        }
        return true;
    }
    
    //----------------------------------------------------------------------------------------------------
    std::vector<double> VDeepNeuralNetworks::Stimulate(const std::vector<double>& _inputs)
    {
        // Prepare (useless)
        ClearStimulus();
        
        // Process
        unsigned long size = _inputs.size() < mInputs.size() ? _inputs.size() : mInputs.size();
        for (unsigned long i = 0; i < size; ++i)
        {
            mInputs[i]->Stimulate(_inputs[i]);
            mInputs[i]->Activate();
        }
        for (auto& neurons : mHiddenLevels)
        {
            for (auto& neuron : neurons)
            {
                neuron->Activate();
            }
        }
        
        // Output
        std::vector<double> outputs;
        outputs.reserve(mOutputs.size());
        for (auto& neuron : mOutputs)
        {
            outputs.push_back(neuron->Stimulus());
            neuron->Clear();
        }
        return outputs;
    }
    
    // Cost = MSE = ∑((target - output)^2) / n
    //----------------------------------------------------------------------------------------------------
    // Output level: ∂Loss/∂Output = -2 * (target - output) / n = 2 * (output - target) / n
    //               ∂Output/∂Neuron = (sigmoid)' = sigmoid * (1 - sigmoid) = output * (1 - output)
    //               ∂Neuron/∂Weight = (weight * previousOutput)' = previousOutput
    //----------------------------------------------------------------------------------------------------
    // Previous level: ∂Loss/∂PreviousOutput = ∑(∂Loss/∂Output * ∂Output/∂Neuron * ∂Neuron/∂PreviousOutput)
    //                 ∂PreviousOutput/∂PreviousNeuron = previousNeuron * (1 - previousNeuron)
    //                 ∂PreviousNeuron/∂PreviousWeight = (previousWeight * previousPreviousOutput)' = previousPreviousOutput
    //----------------------------------------------------------------------------------------------------
    // Weight <- Weight - (Learning Rate) * ∂Loss/∂Weight
    //----------------------------------------------------------------------------------------------------
    bool VDeepNeuralNetworks::BPTrain(const std::vector<double>& _inputs, const std::vector<double>& _outputs)
    {
        if (_outputs.size() != mOutputs.size())
        {
            return false;
        }
        
        // Loss
        std::vector<double> fakeOutputs = Stimulate(_inputs);
        double meanSquareError = 0;
        for (unsigned long i = 0; i < _outputs.size(); ++i)
        {
            meanSquareError += std::pow(_outputs[i] - fakeOutputs[i], 2);
        }
        meanSquareError /= fakeOutputs.size();
        // ∂Loss/∂Output
        std::vector<double> outputDerivatives;
        outputDerivatives.reserve(fakeOutputs.size());
        for (unsigned long i = 0; i < _outputs.size(); ++i)
        {
            outputDerivatives.push_back(2.0 * (fakeOutputs[i] - _outputs[i]) / fakeOutputs.size());
        }
        // ∂Output/∂Neuron
        
        
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDeepNeuralNetworks::Link(VNeuron _source, double _weight, VNeuron _target)
    {
        if (_source && _target)
        {
            VSynapse synapse(new VSynapseCore(_source, _weight, _target));
            _source->AddAxon(synapse);
            _target->AddDendrite(synapse);
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VDeepNeuralNetworks::Unlink(VNeuron _source, VNeuron _target)
    {
        if (_source && _target)
        {
            return _source->RemoveAxon(_target) && _target->RemoveDendrite(_source);
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VDeepNeuralNetworks::ClearStimulus()
    {
        for (auto& neuron : mInputs)
        {
            neuron->DeepClear();
        }
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VDeepNeuralNetworksTest()
    {
        VDeepNeuralNetworks networks;
        networks.Generate(3, {4, 5, 4}, 3);
        auto outputs = networks.Stimulate({1, 0, 1});
        networks.BPTrain({1, 1, 1}, {0, 0, 0});
        
        return;
    }
    
}
