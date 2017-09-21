#include "VNeuron.h"
#include "./VSynapse.h"
#include <cmath>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VNeuronCore
    //----------------------------------------------------------------------------------------------------
    VNeuronCore::VNeuronCore()
        :
        mDendrites(),
        mAxons(),
        mLearningRate(0.1),
        mStimulus(0),
        mIsNeuronDirty(false)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VNeuronCore::VNeuronCore(const VNeuronCore& _core)
        :
        mDendrites(_core.mDendrites),
        mAxons(_core.mAxons),
        mLearningRate(_core.mLearningRate),
        mStimulus(_core.mStimulus),
        mIsNeuronDirty(_core.mIsNeuronDirty)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VNeuronCore::~VNeuronCore()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    double VNeuronCore::Stimulus()
    {
        return mStimulus;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VNeuronCore::AddDendrite(VSynapse _dendrite)
    {
        mDendrites[_dendrite->source] = _dendrite;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VNeuronCore::AddAxon(VSynapse _axon)
    {
        mAxons[_axon->target] = _axon;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VNeuronCore::RemoveDendrite(VNeuronWeak _dendrite)
    {
        auto it = mDendrites.find(_dendrite);
        if (it != mDendrites.end())
        {
            mDendrites.erase(it);
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VNeuronCore::RemoveAxon(VNeuron _axon)
    {
        auto it = mAxons.find(_axon);
        if (it != mAxons.end())
        {
            mAxons.erase(it);
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VNeuronCore::Stimulate(double _transmitters)
    {
        mStimulus += _transmitters;
        if (!mIsNeuronDirty)
        {
            mIsNeuronDirty = true;
        }
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VNeuronCore::Clear()
    {
        if (mIsNeuronDirty)
        {
            mStimulus = 0;
            mIsNeuronDirty = false;
            return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VNeuronCore::DeepClear()
    {
        if (Clear())
        {
            for (auto& axon : mAxons)
            {
                VNeuron neuron = axon.first;
                neuron->DeepClear();
            }
        }
    }
    
    // Activation functions: sigmoid
    //----------------------------------------------------------------------------------------------------
    double VNeuronCore::Activate()
    {
        double activity = 1 / (1 + std::exp(-1 * mStimulus));
        for (auto& axon : mAxons)
        {
            axon.second->Transmit(activity);
        }
        Clear();
        return activity;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VNeuronTest()
    {
        
        return;
    }
    
}
