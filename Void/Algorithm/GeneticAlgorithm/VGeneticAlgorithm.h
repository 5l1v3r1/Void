#pragma once
#ifndef _V_GENETICALGORITHM_H_
#define _V_GENETICALGORITHM_H_

#include "../RouletteWheel/VRouletteWheel.h"
#include "../../Structure/Any/VAny.h"
#include "../../Memory/SmartPointer/VSmartPointer.h"
#include <string>
#include <map>
#include <vector>
#include <functional>


//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VChromosome
    //----------------------------------------------------------------------------------------------------
    struct VChromosome
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VChromosome(const std::vector<std::string>& _genes)
            :
            genes(_genes),
            fitness(0.f)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline VChromosome(const VChromosome& _chromosome)
        :
        genes(_chromosome.genes),
        fitness(_chromosome.fitness)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline bool operator!= (const VChromosome& _chromosome)
        {
            return genes != _chromosome.genes;
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        std::vector<std::string> genes; // bits
        float fitness; // 0.f - 1.f
    };
    typedef VSharePointer<VChromosome> VChromosomePtr;
    
    // VGeneController
    //----------------------------------------------------------------------------------------------------
    class VGeneController
    {
    public:
        VGeneController(const std::function<float(std::vector<VAny>)>& _fitnessFunc, int _maxPopulationSize = 2000,float _crossoverRate = 0.7,float _mutationRate = 0.1);
        virtual ~VGeneController();
        
        virtual bool Epoch();
        virtual bool AddSample(const std::vector<std::string>& _genes);
        virtual void AddTranslation(std::string _gene, VAny _meaning);
        
    protected:
        bool CalculateFitness(VChromosomePtr& _chromosome);
        void Crossover();
        bool Mutate(VChromosomePtr& _chromosome);
        
    protected:
        int m_maxPopulationSize;
        float m_crossoverRate;
        float m_mutationRate;
        std::map<std::string, VAny> m_geneTranslation;
        std::function<float(std::vector<VAny>)> m_fitnessFunc;
        // Todo: crossover func, mutation func
        
        // runtime
        VRouletteWheel<VChromosomePtr> m_chromosomes;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VGeneticAlgorithmTest();
}

#endif
