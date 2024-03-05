#pragma once
#include <SFML/Graphics.hpp>
#include "GameStateBase.h"
#include "GameStartingStateUI.h"

namespace ApplesGame
{
    class Game;

    class GameStartingState :
        public GameStateBase
    {
        Game* game;
        sf::Font textFont;
        GameStartingStateUI stateUI;
    public:
        GameStartingState(Game* currentGame);
        GameState GetGameState() const override { return GameState::Starting; };
        void Update(const float deltaTime) override;
        void Draw(sf::RenderWindow& window);
        ~GameStartingState() = default;
    };
}

