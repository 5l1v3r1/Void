#include "VSynapse.h"
#include "./VNeuron.h"

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VSynapseCore
    //----------------------------------------------------------------------------------------------------
    VSynapseCore::VSynapseCore()
        :
        source(nullptr),
        weight(0),
        bias(0),
        target(nullptr)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VSynapseCore::VSynapseCore(VNeuronWeak _source, double _weight, VNeuronWeak _target)
        :
        source(_source),
        weight(_weight),
        bias(0),
        target(_target)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VSynapseCore::~VSynapseCore()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    void VSynapseCore::Transmit(double _activity)
    {
        target->Stimulate(_activity * weight + bias);
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VSynapseTest()
    {
        
        return;
    }
    
}
