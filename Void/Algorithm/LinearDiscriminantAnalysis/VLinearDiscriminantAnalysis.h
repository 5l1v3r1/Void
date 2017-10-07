#pragma once
#ifndef _V_LINEARDISCRIMINANTANALYSIS_H_
#define _V_LINEARDISCRIMINANTANALYSIS_H_

#include "../../Structure/DynamicMatrix/VDynamicMatrix.h"
#include <map>
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VLinearDiscriminantAnalysisType
    //----------------------------------------------------------------------------------------------------
    enum class VLinearDiscriminantAnalysisType
    {
        BinaryClassifier = 0,
        MultipleClassifier,
    };
    
    // VLinearDiscriminantAnalysis
    //----------------------------------------------------------------------------------------------------
    // Degree: 2
    // Model: u(x) = ∑(x) / n
    //        s(x) = ∑((x - u(x))T * (x - u(x)))
    //        y = w * xT
    //        u(y) = ∑(w * xT) / n = w * ∑(x)T / n = w * u(x)T
    //        s(y) = ∑((y - u(y))^2) = ∑((w * xT - w * u(x)T)^2) = w * ∑((x - u(x))T * (x - u(x))) * wT = w * s(x) * wT
    // Goal: max(J(w))
    //       J(w) = (u(y1) - u(y2))^2 / (s(y1) + s(y2))
    //            = w * ((u(x1) - u(x2))T * (u(x1) - u(x2))) * wT / (w * (s(x1) + s(x2)) * wT)
    //            = w * sb * wT / (w * sw * wT)
    //       J'(w) = w * sw * wT * (w * sb * wT)' - w * sb * wT * (w * sw * wT)' / (w * sw * wT)^2 = 0
    //                                   w * sw * wT * (2 * sb * wT) - w * sb * wT * (2 * sw * wT) = 0
    //                          w * sw * wT * (2 * sb * wT) / (w * sw * wT) - J(w) * (2 * sw * wT) = 0
    //                                                                (sb * wT) - J(w) * (sw * wT) = 0
    //                                                                    sb * wT - J(w) * sw * wT = 0
    //                                                                           (sw^-1 * sb) * wT = J(w) * wT
    //                                                                                          w* = Eigenvector(sw^-1 * sb) of max(Eigenvalue)
    //                                                               sw^-1 * (u(x1) - u(x2))T * λw = J(w) * wT
    //                                                                                          w* = sw^-1 * (u(x1) - u(x2))T
    //----------------------------------------------------------------------------------------------------
    // Degree: *
    // Model: y = W * xT
    // Goal: max(J(W))
    //       J(W) = W * sb * WT / (W * sw * WT)
    //       sb = ∑(ni * (u(xi) - u(x))T * (u(xi) - u(x)))
    //       sw = ∑(s(xi))
    //       W* = Eigenvector(sw^-1 * sb) of topn(Eigenvalue)
    //----------------------------------------------------------------------------------------------------
    template<typename _Feature, typename _Label>
    class VLinearDiscriminantAnalysis
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VLinearDiscriminantAnalysis()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VLinearDiscriminantAnalysis()
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Push(const std::vector<_Feature>& _features, const _Label& _label)
        {
            auto it = mSamples.find(_label);
            if (it != mSamples.end())
            {
                it->second.ConcatenateRight(_features);
            }
            else
            {
                mSamples[_label] = VDynamicMatrix<_Feature>().ConcatenateRight(_features);
            }
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void ClearSamples()
        {
            mSamples.clear();
        }
        
        //----------------------------------------------------------------------------------------------------
        inline void Build()
        {
            if (mSamples.empty())
            {
                return;
            }
            
            // Prepare
            std::map<_Label, VDynamicMatrix<_Feature>> means;
            std::map<_Label, VDynamicMatrix<_Feature>> scatterMatrices;
            for (auto& samples : mSamples)
            {
                means[samples.first] = samples.second.RowMeans();
                scatterMatrices[samples.first] = samples.second.WithinClassScatterMatrix();
            }
            // Sw
            auto iterator = scatterMatrices.begin();
            VDynamicMatrix<_Feature> withinClassScatterMatrix = iterator->second;
            for (++iterator; iterator != scatterMatrices.end(); ++iterator)
            {
                withinClassScatterMatrix += iterator->second;
            }
            // Sb
            iterator = means.begin();
            VDynamicMatrix<_Feature> betweenClassScatter = iterator->second;
            for (++iterator; iterator != means.end(); ++iterator)
            {
                betweenClassScatter -= iterator->second;
            }
            VDynamicMatrix<_Feature> result = withinClassScatterMatrix.Inverse() * (betweenClassScatter);
            
            ClearSamples();
        }
        
        // wT * x - wT * u < 0
        //----------------------------------------------------------------------------------------------------
        _Label Perceive() const
        {
            
            return false;
        }
        
    protected:
        //----------------------------------------------------------------------------------------------------
        std::vector<_Feature> mWeights;
        std::map<_Label, VDynamicMatrix<_Feature>> mSamples;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VLinearDiscriminantAnalysisTest();
}

#endif
