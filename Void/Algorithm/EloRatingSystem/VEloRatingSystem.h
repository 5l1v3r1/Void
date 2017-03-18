#pragma once
#ifndef _V_ELORATINGSYSTEM_H_
#define _V_ELORATINGSYSTEM_H_

#include "../IntervalTree/VIntervalTree.h"
#include <vector>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VEloPlayer
    //----------------------------------------------------------------------------------------------------
    struct VEloPlayer
    {
    public:
        //----------------------------------------------------------------------------------------------------
        inline VEloPlayer()
            :
            rating(0),
            kFactor(0),
            rounds(0)
        {
        }
        
        //----------------------------------------------------------------------------------------------------
        inline VEloPlayer(float _rating)
            :
            rating(_rating),
            kFactor(0),
            rounds(0)
        {
        }
        
    public:
        //----------------------------------------------------------------------------------------------------
        float rating;
        float kFactor;
        int rounds;
    };
    
    // VEloRatingSystem
    //----------------------------------------------------------------------------------------------------
    class VEloRatingSystem
    {
    public:
        //----------------------------------------------------------------------------------------------------
        VEloRatingSystem();
        ~VEloRatingSystem();
        
        //----------------------------------------------------------------------------------------------------
        VEloPlayer NewPlayer();
        void Win(VEloPlayer& _player, VEloPlayer& _opponent);
        void Draw(VEloPlayer& _player, VEloPlayer& _opponent);
        void Lose(VEloPlayer& _player, VEloPlayer& _opponent);
        
    protected:
        //----------------------------------------------------------------------------------------------------
        float Expectation(const VEloPlayer& _player, const VEloPlayer& _opponent);
        void Versus(VEloPlayer& _player, VEloPlayer& _opponent, float _result);
        void UpdateKFactor(VEloPlayer& _player);
        
    public:
        //----------------------------------------------------------------------------------------------------
        float defaultRating;
        float defaultKFactor;
        VIntervalTree<float, float> ratingBoundaryForKFactor;
        float logisticFactor;
    };
    
    // Test
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystemTest();
}

#endif
