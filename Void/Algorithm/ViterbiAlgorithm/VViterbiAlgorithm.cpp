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
        startProbability["Healthy"] = 0.6f;
        startProbability["Fever"] = 0.4f;
        std::map<std::string, std::map<std::string, float>> transitionProbability;
        std::map<std::string, float> healthyTransition;
        healthyTransition["Healthy"] = 0.7f;
        healthyTransition["Fever"] = 0.3f;
        transitionProbability["Healthy"] = healthyTransition;
        std::map<std::string, float> feverTransition;
        feverTransition["Healthy"] = 0.4f;
        feverTransition["Fever"] = 0.6f;
        transitionProbability["Fever"] = feverTransition;
        std::map<std::string, std::map<std::string, float>> emissionProbability;
        std::map<std::string, float> healthyEmission;
        healthyEmission["Normal"] = 0.5f;
        healthyEmission["Cold"] = 0.4f;
        healthyEmission["Dizzy"] = 0.1f;
        emissionProbability["Healthy"] = healthyEmission;
        std::map<std::string, float> feverEmission;
        feverEmission["Normal"] = 0.1f;
        feverEmission["Cold"] = 0.3f;
        feverEmission["Dizzy"] = 0.6f;
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
