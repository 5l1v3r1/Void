#include "VViterbiAlgorithm.h"
#include "../../Utility/Logger/VLogger.h"
#include <string>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // Test
    //----------------------------------------------------------------------------------------------------
    void VViterbiAlgorithmTest()
    {
        std::vector<std::string> states;
        states.push_back("Healthy");
        states.push_back("Fever");
        std::vector<std::string> observations;
        observations.push_back("Normal");
        observations.push_back("Cold");
        observations.push_back("Dizzy");
        std::map<std::string, float> startProbability;
        startProbability["Healthy"] = 0.6;
        startProbability["Fever"] = 0.4;
        std::map<std::string, std::map<std::string, float>> transitionProbability;
        std::map<std::string, float> healthyTransition;
        healthyTransition["Healthy"] = 0.7;
        healthyTransition["Fever"] = 0.3;
        transitionProbability["Healthy"] = healthyTransition;
        std::map<std::string, float> feverTransition;
        feverTransition["Healthy"] = 0.4;
        feverTransition["Fever"] = 0.6;
        transitionProbability["Fever"] = feverTransition;
        std::map<std::string, std::map<std::string, float>> emissionProbability;
        std::map<std::string, float> healthyEmission;
        healthyEmission["Normal"] = 0.5;
        healthyEmission["Cold"] = 0.4;
        healthyEmission["Dizzy"] = 0.1;
        emissionProbability["Healthy"] = healthyEmission;
        std::map<std::string, float> feverEmission;
        feverEmission["Normal"] = 0.1;
        feverEmission["Cold"] = 0.3;
        feverEmission["Dizzy"] = 0.6;
        emissionProbability["Fever"] = feverEmission;
        
        VViterbiAlgorithm<std::string, std::string> viterbi(states, observations, startProbability, transitionProbability, emissionProbability);
        std::vector<std::string> question;
        question.push_back("Normal");
        question.push_back("Cold");
        question.push_back("Dizzy");
        question.push_back("Cold");
        question.push_back("Normal");
        auto result = viterbi.Calculate(question);
        
        return;
    }
}
