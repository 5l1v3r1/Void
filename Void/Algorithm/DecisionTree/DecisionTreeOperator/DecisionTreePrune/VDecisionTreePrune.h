#pragma once
#ifndef _V_DECISIONTREEPRUNE_H_
#define _V_DECISIONTREEPRUNE_H_

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VDecisionTreePrune
    //----------------------------------------------------------------------------------------------------
    enum class VDecisionTreePrune
    {
        PessimisticErrorPruning = 0,
        MinimumErrorPruning,
        CostComplexityPruning,
        CriticalValuePruning,
        OptimalPruning,
        CostSensitiveDecisionTreePruning,
        ReducedErrorPruning,
        ErrorBasedPruning
    };

}

#endif
