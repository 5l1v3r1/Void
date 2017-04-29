#include "VGeneticAlgorithm.h"
#include "../../Utility/Logger/VLogger.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VGeneController
    //----------------------------------------------------------------------------------------------------
    VGeneController::VGeneController(const std::function<float(std::vector<VAny>)>& _fitnessFunc, int _maxPopulationSize, float _crossoverRate, float _mutationRate)
        :
        m_maxPopulationSize(_maxPopulationSize),
        m_crossoverRate(_crossoverRate),
        m_mutationRate(_mutationRate),
        m_geneTranslation(),
        m_fitnessFunc(_fitnessFunc),
        m_chromosomes()
    {
        srand((unsigned int)time(0));
    }
    
    //----------------------------------------------------------------------------------------------------
    VGeneController::~VGeneController()
    {
        
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeneController::Epoch()
    {
        if (m_maxPopulationSize > 0)
        {
            while ((unsigned int)m_maxPopulationSize < m_chromosomes.Size())
                m_chromosomes.PopFront();
        }
        
        Crossover();
        
        if (m_chromosomes.begin() != m_chromosomes.end())
        {
            if (m_chromosomes.Back()->fitness == 1.f)
                return false;
            else
                return true;
        }
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeneController::AddSample(const std::vector<std::string>& _genes)
    {
        VChromosomePtr sample(new VChromosome(_genes));
        
        if (CalculateFitness(sample))
        {
            m_chromosomes.Insert(sample->fitness, sample);
            return true;
        }
        
        return false;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VGeneController::AddTranslation(std::string _gene, VAny _meaning)
    {
        m_geneTranslation[_gene] = _meaning;
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeneController::CalculateFitness(VChromosomePtr& _chromosome)
    {
        std::vector<VAny> meanings;
        for (auto& gene : _chromosome->genes)
        {
            if (m_geneTranslation.find(gene) != m_geneTranslation.end())
                meanings.push_back(m_geneTranslation[gene]);
            else
                return false;
        }
        
        _chromosome->fitness = m_fitnessFunc(meanings);
        
        return _chromosome->fitness > 0;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VGeneController::Crossover()
    {
        VChromosomePtr dad, mom; // Todo: selfing X
        if (!m_chromosomes.RandomSelect(dad) || !m_chromosomes.RandomSelect(mom))
            return;
        
        VChromosomePtr son(new VChromosome(*dad)), daughter(new VChromosome(*mom));
        if (((float)rand() / (float)RAND_MAX) <= m_crossoverRate)
        {
            for (unsigned int i = 0; i < son->genes.size(); ++i)
            {
                if (((float)rand() / (float)RAND_MAX) <= 0.5f)
                {
                    std::string tmp = son->genes[i];
                    son->genes[i] = daughter->genes[i];
                    daughter->genes[i] = tmp;
                }
            }
        }
        
        Mutate(son);
        Mutate(daughter);
        if (CalculateFitness(son))
            m_chromosomes.Insert(son->fitness, son);
        if (CalculateFitness(daughter))
            m_chromosomes.Insert(daughter->fitness, daughter);
    }
    
    //----------------------------------------------------------------------------------------------------
    bool VGeneController::Mutate(VChromosomePtr& _chromosome)
    {
        float geneMutationRate = float(1 - pow(1 - m_mutationRate, 1.0 / (double)_chromosome->genes.size()));
        for (auto& gene : _chromosome->genes)
        {
            if (((float)rand() / (float)RAND_MAX) <= geneMutationRate)
            {
                for (unsigned int i = 0; i < gene.size(); ++i)
                {
                    if (((float)rand() / (float)RAND_MAX) <= 0.5f)
                    {
                        gene[i] = gene[i] == '0' ? '1' : '0';
                    }
                }
            }
        }
        
        return true;
    }
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VGeneticAlgorithmTest()
    {
        VGeneController geneController(
                                        [](std::vector<VAny> _meanings) -> float
                                        {
                                            if (!_meanings.size())
                                                return 0.f;
                                            
                                            bool isInitialized = false;
                                            bool isFuncLoaded = false;
                                            bool isNumLoaded = false;
                                            int left = 0;
                                            int right = 0;
                                            std::function<int(int, int)> operateFunc;
                                            for (unsigned int i = 0; i < _meanings.size(); ++i)
                                            {
                                                if (_meanings[i].Type() == typeid(int))
                                                {
                                                    if (isNumLoaded)
                                                    {
                                                        right *= 10;
                                                        right += VAnyCast<int>(_meanings[i]);
                                                    }
                                                    else
                                                    {
                                                        right = VAnyCast<int>(_meanings[i]);
                                                        isNumLoaded = true;
                                                    }
                                                }
                                                else if (_meanings[i].Type() == typeid(std::function<int(int, int)>))
                                                {
                                                    if (!isInitialized)
                                                    {
                                                        left = right;
                                                        isInitialized = true;
                                                    }
                                                    else if (isNumLoaded && isFuncLoaded)
                                                    {
                                                        VLogger::Info("%d op %d", left, right);
                                                        left = operateFunc(left, right);
                                                        VLogger::Info("result: %d", left);
                                                    }
                                                    
                                                    operateFunc = VAnyCast<std::function<int(int, int)>>(_meanings[i]);
                                                    isNumLoaded = false;
                                                    isFuncLoaded = true;
                                                }
                                            }
                                            if (isNumLoaded && isFuncLoaded)
                                            {
                                                VLogger::Info("%d op %d", left, right);
                                                left = operateFunc(left, right);
                                                VLogger::Info("result: %d", left);
                                            }
                                            
                                            float result = 1.f / (0.05f * abs(left - 100) + 1); // Option: logistic regression function
                                            VLogger::Info("Fitness: %f", result);
                                            return result;
                                        });
        
        geneController.AddTranslation("0000", 0);
        geneController.AddTranslation("0001", 1);
        geneController.AddTranslation("0010", 2);
        geneController.AddTranslation("0011", 3);
        geneController.AddTranslation("0100", 4);
        geneController.AddTranslation("0101", 5);
        geneController.AddTranslation("0110", 6);
        geneController.AddTranslation("0111", 7);
        geneController.AddTranslation("1000", 8);
        geneController.AddTranslation("1001", 9);
        geneController.AddTranslation("00", std::function<int(int, int)>([](int _a, int _b) -> int { return _a + _b; }));
        geneController.AddTranslation("01", std::function<int(int, int)>([](int _a, int _b) -> int { return _a - _b; }));
        geneController.AddTranslation("10", std::function<int(int, int)>([](int _a, int _b) -> int { return _a * _b; }));
        geneController.AddSample({ "0000", "00", "0000", "00", "0000", "00", "0000" });
        geneController.AddSample({ "0000", "01", "0000", "01", "0000", "01", "0000" });
        geneController.AddSample({ "0000", "10", "0000", "10", "0000", "10", "0000" });
        while (geneController.Epoch());
        
        return;
    }
}
