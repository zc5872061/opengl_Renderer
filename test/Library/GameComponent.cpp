#include "GameComponent.h"

namespace Library
{
    GameComponent::GameComponent()
    : mGame(nullptr), mEnabled(true),mDrawAble(true)
    {
    }
    
    GameComponent::GameComponent(Game* game)
    : mGame(game), mEnabled(true)
    {
    }
    
    GameComponent::~GameComponent()
    {
    }
    
    Game* GameComponent::GetGame()
    {
        return mGame;
    }
    
    void GameComponent::SetGame(Game* game)
    {
        mGame = game;
    }
    
    bool GameComponent::Enabled() const
    {
        return mEnabled;
    }
    
    void GameComponent::SetEnabled(bool enabled)
    {
        mEnabled = enabled;
    }
    
    void GameComponent::Initialize()
    {
    }
    
    void GameComponent::Update()
    {
    }
}
