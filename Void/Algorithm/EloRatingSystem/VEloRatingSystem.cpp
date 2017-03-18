#include "VEloRatingSystem.h"
#include <math.h>

//----------------------------------------------------------------------------------------------------
namespace Void
{
    // VEloRatingSystem
    //----------------------------------------------------------------------------------------------------
    VEloRatingSystem::VEloRatingSystem()
        :
        defaultRating(500.f),
        defaultKFactor(15.f),
        ratingBoundaryForKFactor(),
        logisticFactor(400.f)
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VEloRatingSystem::~VEloRatingSystem()
    {
    }
    
    //----------------------------------------------------------------------------------------------------
    VEloPlayer VEloRatingSystem::NewPlayer()
    {
        VEloPlayer player(defaultRating);
        UpdateKFactor(player);
        return player;
    }
    
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystem::Win(VEloPlayer& _player, VEloPlayer& _opponent)
    {
        Versus(_player, _opponent, 1.f);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystem::Draw(VEloPlayer& _player, VEloPlayer& _opponent)
    {
        Versus(_player, _opponent, 0.5f);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystem::Lose(VEloPlayer& _player, VEloPlayer& _opponent)
    {
        Versus(_player, _opponent, 0.0f);
    }
    
    //----------------------------------------------------------------------------------------------------
    float VEloRatingSystem::Expectation(const VEloPlayer& _player, const VEloPlayer& _opponent)
    {
        return 1.0f / (1.0 + powf(10.f, -(_player.rating - _opponent.rating) / logisticFactor));
    }
    
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystem::Versus(VEloPlayer& _player, VEloPlayer& _opponent, float result)
    {
        float expectation = Expectation(_player, _opponent);
        _player.rating += _player.kFactor * (result - expectation);
        _player.rounds += 1;
        _opponent.rating += _opponent.kFactor * ((1 - result) - (1 - expectation));
        _opponent.rounds += 1;
        UpdateKFactor(_player);
        UpdateKFactor(_opponent);
    }
    
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystem::UpdateKFactor(VEloPlayer& _player)
    {
        std::vector<float> kFactors;
        ratingBoundaryForKFactor.FindData(_player.rating, _player.rating, kFactors);
        if (!kFactors.empty())
        {
            _player.kFactor = kFactors[0];
        }
        else
        {
            _player.kFactor = defaultKFactor;
        }
    }
        
    // Test
    //----------------------------------------------------------------------------------------------------
    void VEloRatingSystemTest()
    {
        VEloRatingSystem system;
        VEloPlayer bob = system.NewPlayer();
        VEloPlayer jane = system.NewPlayer();
        system.Win(bob, jane);
        system.Lose(bob, jane);
        system.Draw(bob, jane);
        
        return;
    }
    
}
