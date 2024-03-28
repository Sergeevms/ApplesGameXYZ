#pragma once
#include "GameStateBase.h"
#include "ReturnToMenuDialogStateUI.h"
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
        //sf::Font textFont;
        PauseMenu menu;
        sf::RectangleShape background;
        //ReturnToMenuDialogStateUI stateUI;
    public:
        ReturnToMenuDialogState(Game* currentGame);
        GameState GetGameState() const override { return GameState::ReturnToMenuDialog; };
        void Update(const float deltaTime) override;
        void Draw(sf::RenderWindow& window) override;
        ~ReturnToMenuDialogState() = default;
    };
}