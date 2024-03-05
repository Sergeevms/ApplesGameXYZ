#pragma once
#include "GameStateBase.h"
#include "GameOveredStateUI.h"

namespace ApplesGame
{
    class Game;

    class GameOveredState :
        public GameStateBase
    {
        float gameStateTimer{ 0.f };
        Game* game;
        sf::Font textFont;
        GameOveredStateUI stateUI;
    public:
        GameOveredState(Game* currentGame);
        GameState GetGameState() const override { return GameState::Overed; };
        void Update(const float deltaTime) override;
        ~GameOveredState() = default;
        void Draw(sf::RenderWindow& window) override;
    };
}
