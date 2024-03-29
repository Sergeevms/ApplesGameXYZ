#pragma once
#include "GameStateBase.h"
#include "GeneralMenu.h"

namespace ApplesGame
{
    class Game;
    
    struct PauseMenu : public GeneralMenu
    {
        MenuNode root;
        MenuNode continueGame;
        MenuNode toMainMenu;

        PauseMenu();
    };

    class ReturnToMenuDialogState :
        public GameStateBase
    {
        Game* game;
        PauseMenu menu;
        sf::RectangleShape background;
    public:
        ReturnToMenuDialogState(Game* currentGame);
        GameState GetGameState() const override { return GameState::ReturnToMenuDialog; };
        void Update(const float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        ~ReturnToMenuDialogState() = default;
    };
}