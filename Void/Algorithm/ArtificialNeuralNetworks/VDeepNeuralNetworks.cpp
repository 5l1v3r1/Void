#include "VDeepNeuralNetworks.h"

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
        
        // Ouput
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
        // Prepare
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
        
        // Ouput
        std::vector<double> ouputs;
        ouputs.reserve(mOutputs.size());
        for (auto& neuron : mOutputs)
        {
            ouputs.push_back(neuron->Stimulus());
            neuron->Clear();
        }
        return ouputs;
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
            return true;
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
        auto ouputs = networks.Stimulate({1, 0, 1});
        
        return;
    }
    
}
