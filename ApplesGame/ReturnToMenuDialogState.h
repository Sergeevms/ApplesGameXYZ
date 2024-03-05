#pragma once
#include "GameStateBase.h"
#include "ReturnToMenuDialogStateUI.h"

namespace ApplesGame
{
    class Game;

    class ReturnToMenuDialogState :
        public GameStateBase
    {
        Game* game;
        sf::Font textFont;
        ReturnToMenuDialogStateUI stateUI;
    public:
        ReturnToMenuDialogState(Game* currentGame);
        GameState GetGameState() const override { return GameState::Starting; };
        void Update(const float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        ~ReturnToMenuDialogState() = default;
    };
}