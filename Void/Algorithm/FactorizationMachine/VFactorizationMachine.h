#pragma once
#ifndef _V_FACTORIZATIONMACHINE_H_
#define _V_FACTORIZATIONMACHINE_H_

#include "../../Structure/SparseMatrix/VSparseMatrix.h"
#include "../../Structure/DynamicMatrix/VDynamicMatrix.h"
#include "./FactorizationMachineLearning/VFactorizationMachineLearningSGD.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VFactorizationMachine
    // Degree: 2
    // Auxiliary Vectors: V = [v11 v12 ... v1k] = [v1]
    //                      = [v21 v22 ... v2k]   [v2]
    //                      = [...            ]   [v3]
    //                      = [vn1 vn2 ... vnk]   [v4]
    // W(i, j) = (V * VT)(i, j) = <vi, vj> = wij
    // Model: y = b + ∑(wi * xi) + ∑∑(wij * xi * xj), where i != j and uniq(i, j)
    //          = b + ∑(wi * xi) + ∑∑(<vi, vj> * xi * xj), where i != j and uniq(i, j)
    //          = b + ∑(wi * xi) + ∑∑(<vi, vj> * xi * xj) / 2 - ∑(<vi, vi> * xi * xi) / 2
    //          = b + ∑(wi * xi) + (∑∑∑((vik * vjk) * xi * xj) - ∑∑(vik^2 * xi^2)) / 2
    //          = b + ∑(wi * xi) + ∑(∑(vik * xi) * ∑(vjk * vjk) - ∑((vik * xi)^2)) / 2
    //          = b + ∑(wi * xi) + ∑(∑(vik * xi)^2 - ∑((vik * xi)^2)) / 2
    //          = gθ(x) + θ * hθ(x), θ ∈ Θ
    //        Θ = (b, w1, ..., wn, v11, v12, ..., vnk)
    //        ∂y/∂θ = 1, where θ = b
    //              = xi, where θ = wi
    //              = xi * ∑(vjk * xj), where θ = vik && i != j
    //              = xi * (∑(vjk * xj) - vik * xi), where θ = vik
    // Loss Function - The least square error (Regression)
    //                 L(y(x), y) = (y(x) - y)^2 / 2
    //                 ∂L/∂θ = (y(x) - y) * ∂y/∂θ
    //               - Logit loss (Binary Classification)
    //                 L(y(x), y) = -ln(σ(y(x) * y))
    //                 σ(x) = 1 / (1 - e^(-x))
    //                 ∂L/∂θ = -1 / (σ(y(x) * y)) * σ(y(x) * y) * (1 - σ(y(x) * y)) * y * ∂y/∂θ
    //                       = (σ(y(x) * y) - 1) * y * ∂y/∂θ
    //               - Hinge loss: (Binary Classification)
    // Goal: Θ = arg(min(∑(L(y(x), y))))
    //       ΘL2 = arg(min(∑(L(y(x), y) + ∑(λθ * θ^2))))
    // Method - Stochastic Gradient Descent
    //        - Adaptive SGD
    //        - Alternating Least-Squares
    //        - Markov Chain Monte Carlo
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VFactorizationMachineType _Type=VFactorizationMachineType::Classification, VFactorizationMachineLearningType _Learning=VFactorizationMachineLearningType::StochasticGradientDescent>
    class VFactorizationMachine : public VFactorizationMachineLearningSGD<_T, _Type>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFactorizationMachine(unsigned int _dimension, unsigned int _k)
            :
            VFactorizationMachineLearningSGD<_T, _Type>(_dimension, _k)
        {
        }
    };
    
    //----------------------------------------------------------------------------------------------------
    template<typename _T, VFactorizationMachineType _Type>
    class VFactorizationMachine<_T, _Type, VFactorizationMachineLearningType::StochasticGradientDescent> : public VFactorizationMachineLearningSGD<_T, _Type>
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VFactorizationMachine(unsigned int _dimension, unsigned int _k)
            :
            VFactorizationMachineLearningSGD<_T, _Type>(_dimension, _k)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        virtual ~VFactorizationMachine()
        {
        }
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VFactorizationMachineTest();
}

#endif
